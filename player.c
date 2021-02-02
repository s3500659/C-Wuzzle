/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include "player.h"

#include "game.h"
/* the color_strings array that defines the color codes for the printing
 * out colour in the terminal. The order of the values in this array is the
 * same as the color enum
 **/
char *color_strings[] = {"\033[0;31m", "\033[0;32m", "\033[0;33m", "\033[0;34m",
                         "\033[0;35m", "\033[0;36m", "\033[0m"};
/**
 * prompt the user for their name and deal the letters for the player to start
 * with. Also assign the game pointer so we can access it later.
 **/
BOOLEAN player_init(struct player *theplayer, const char *name,
                    struct game *thegame)
{
    int random_number;

    /* get player name */
    if (!get_player_name(theplayer))
    {
        return FALSE;
    }
    /* assign colour */
    random_number = gen_randomnumber(MAXRAND);
    theplayer->color = get_playercolour(random_number);
    /* assign game to player */
    theplayer->curgame = thegame;

    return TRUE;
}

/* get the name of a player */
BOOLEAN get_player_name(struct player * player)
{
    enum input_result inputresult;
    printf("\nPlease enter player name:\n");
    inputresult = get_user_input(player->name, NAMELEN);
    if (inputresult != IR_SUCCESS)
    {
        return FALSE;
    }

    return TRUE;
}

int gen_randomnumber(int max)
{
    int random_number = RAND_MAX;

    srand(time(NULL));
    if (random_number > max)
    {
        random_number = rand() % max;
    }
    return random_number;
}

enum color get_playercolour(int colournumber)
{
    switch (colournumber)
    {
    case 0:
        return COL_RED;
        break;
    case 1:
        return COL_GREEN;
        break;
    case 2:
        return COL_YELLOW;
        break;
    case 3:
        return COL_BLUE;
        break;
    case 4:
        return COL_MAGENTA;
        break;
    case 5:
        return COL_CYAN;
        break;
    default:
        return COL_RESET;
        break;
    }
}

/* ensure that player colours will not be the same */
BOOLEAN validate_player_colour(struct player *p1, struct player *p2)
{
    int random_number;

    assert(p1 && p2);
    while (p1->color == p2->color)
    {
        random_number = gen_randomnumber(MAXRAND);
        p2->color = get_playercolour(random_number);
    }
    assert(p1->color != p2->color);

    /* delete this */
    printf("colour: p1=%d, p2=%d\n", p1->color, p2->color);

    return TRUE;
}

/**
 * play a move for this player. please see the assignment specification for the
 * details of this.
 **/
enum move_result player_turn(struct player *theplayer) { return MOVE_QUIT; }
