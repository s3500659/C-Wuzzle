/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include "game.h"

/**
 * initialise the game. Please see the assignment specification for details of
 * what is required.
 **/
BOOLEAN game_init(struct game *thegame)
{
    struct player playerone;
    struct player playertwo;
    char playerone_name[NAMELEN + EXTRACHARS];
    char playertwo_name[NAMELEN + EXTRACHARS];

    int width, height;
    struct board *newboard = (struct board *)malloc(sizeof(struct board));
    int coinflip_result;

    /* init player one */
    player_init(&playerone, playerone_name, thegame);
    /* init player two */
    player_init(&playertwo, playertwo_name, thegame);
    /* ensure players have are different colours */
    if (!validate_player_colour(&playerone, &playertwo))
    {
        fprintf(stderr, "Error: players cannot have the same colour\n");
        return FALSE;
    }
    /* prompt for board size */
    if (!get_board_size(&width, &height))
    {
        return FALSE;
    }
    /* initialise the board */
    newboard = new_board(width, height);
    /* who goes first? */
    coinflip_result = flip_coin();

    thegame->players[PLAYERONE - 1] = playerone;
    thegame->players[PLAYERTWO - 1] = playertwo;
    thegame->theboard = newboard;
    thegame->curr_player_num = coinflip_result;

    return TRUE;
}

/* flips a coin, result should only be either 0 or 1 */
int flip_coin()
{
    int result = EOF;

    srand(time(NULL));
    result = gen_randomnumber(COINFLIP);
    printf("flip_coin = %d\n", result);

    assert(result > EOF || result < COINFLIP);

    return result;
}

/**
 * the core function for the management of the game.
 *
 * call game_init() to initialise the game and then manage whose player turn
 * it is and handle cleaning up and quitting the program when a player quits the
 * game.
 **/
void play_game(const char *scoresfile)
{
    struct game *thegame = malloc(sizeof(struct game));
    game_init(thegame);
    load_scores(scoresfile);
}
