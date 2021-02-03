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

    memset(theplayer, 0, sizeof(struct player));
    /* get player name */
    if (!get_player_name(theplayer))
    {
        return FALSE;
    }

    theplayer->hand = (struct score_list *)malloc(sizeof(struct score_list));
    /* assign colour */
    random_number = gen_randomnumber(MAXRAND);
    theplayer->color = get_playercolour(random_number);
    /* assign game to player */
    theplayer->curgame = thegame;

    return TRUE;
}

/* get the name of a player */
BOOLEAN get_player_name(struct player *player)
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
enum move_result player_turn(struct player *theplayer)
{
    char new_word[MAXLETTER + EXTRACHARS] = "";
    enum input_result result;

    print_board(theplayer);
    printf("it is %s's turn and their colour is %s%s%s, and their score is %d.\n", theplayer->name,
           color_strings[theplayer->color], get_color_name(theplayer->color), color_strings[COL_RESET], theplayer->score);
    print_player_hand(theplayer);
    /* get new word from player */
    result = get_new_word(theplayer, new_word);
    if (IR_EOF == result)
    {
        return MOVE_QUIT;
    }
    if (IR_FAILURE == result)
    {
        return MOVE_SKIP;
    }

    return MOVE_QUIT;
}

enum input_result get_new_word(struct player *theplayer, char *new_word)
{
    enum input_result result;
    printf("Please enter a new word for %s:\n", theplayer->name);
    result = get_user_input(new_word, MAXLETTER + EXTRACHARS);

    return result;
}

/* print the players hand */
void print_player_hand(struct player *theplayer)
{
    int i;
    int print_count = 0;
    char dash[] = "---------------------";

    printf("Their hand currently contains:\n");
    printf("%s\n", dash);
    for (i = 0; i < theplayer->hand->total_count; i++)
    {
        if (theplayer->hand->scores[i].count > 1)
        {
            while (print_count != theplayer->hand->scores[i].count)
            {
                if (theplayer->hand->scores[i].letter != 0)
                {
                    printf("| %c ", theplayer->hand->scores[i].letter);
                    print_count++;
                }
            }
        }
        else
        {
            if (theplayer->hand->scores[i].letter != 0)
            {
                printf("| %c ", theplayer->hand->scores[i].letter);
            }
        }
    }
    printf("|");
    printf("\n%s\n", dash);
}

/* display the game board */
void print_board(struct player *theplayer)
{
    int i, j;
    char dash[] = "----------------------------------\n";

    printf("      1  |  2  |  3  |  4  |  5  |\n");
    printf("%s", dash);
    for (i = 0; i < theplayer->curgame->theboard->height; i++)
    {
        printf("%d  |", i + 1);
        for (j = 0; j < theplayer->curgame->theboard->width; j++)
        {
            int letter = theplayer->curgame->theboard->matrix[i][j].letter;
            if (letter == EOF)
            {
                printf("     |");
            }
            else
            {
                printf("%d  |  ", letter);
            }
        }
        printf("\n%s\n", dash);
    }
}

/* name of the color as a string */
char *get_color_name(enum color col)
{
    switch (col)
    {
    case COL_RED:
        return "Red";
        break;
    case COL_GREEN:
        return "Green";
        break;
    case COL_YELLOW:
        return "Yellow";
        break;
    case COL_BLUE:
        return "Blue";
        break;
    case COL_MAGENTA:
        return "Magenta";
        break;
    case COL_CYAN:
        return "Cyan";
        break;
    default:
        return "Color reset";
        break;
    }
}
