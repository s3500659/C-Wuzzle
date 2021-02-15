/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include "game.h"
#include "rules-b.h"
#include "score_list.h"
#include "board.h"
#include "word_list.h"

/**
 * initialise the game. Please see the assignment specification for details of
 * what is required.
 **/
BOOLEAN game_init(struct game *thegame, const char *wordlist)
{
    struct player playerone;
    struct player playertwo;
    char playerone_name[NAMELEN + EXTRACHARS];
    char playertwo_name[NAMELEN + EXTRACHARS];

    int width, height;
    struct board *newboard = (struct board *)malloc(sizeof(struct board));
    int coinflip_result;
    struct word_list *new_wordlist;

    srand(time(NULL));

    /* load wordlist */
    new_wordlist = load_wordlist(wordlist);

    if (!newboard)
    {
        perror("Error: malloc failed when allocating for new board inside game_init()\n");
    }

    /* init player one */
    if (!player_init(&playerone, playerone_name, thegame))
    {
        return FALSE;
    }
    /* init player two */
    if (!player_init(&playertwo, playertwo_name, thegame))
    {
        return FALSE;
    }
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

    thegame->players[PLAYERONE] = playerone;
    thegame->players[PLAYERTWO] = playertwo;
    thegame->theboard = newboard;
    thegame->curr_player_num = coinflip_result;

    return TRUE;
}

#define WORDLISTLEN 65000
#define WORD_DELIM "\n"
/* load the word list into a linked list */
struct word_list *load_wordlist(const char *wordlist)
{
    struct word_list *newlist = new_list();
    char *copy_wordlist = strdup(wordlist);
    char *token;

    token = strtok(copy_wordlist, WORD_DELIM);
    while (token != NULL)
    {
        list_add(newlist, token);

        token = strtok(NULL, WORD_DELIM);
    }

    return newlist;
}

/* flips a coin, result should only be either 0 or 1 */
int flip_coin()
{
    int result = EOF;

    result = gen_randomnumber(COINFLIP);
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
void play_game(const char *scoresfile, const char *wordlist)
{
    struct game *thegame = malloc(sizeof(struct game));
    struct score_list *scorelist;
    enum move_result moveresult;
    int currentplayer = thegame->curr_player_num;

    if (!thegame)
    {
        perror("Error: malloc failed when allocating for struct game inside play_game()\n");
    }

    game_init(thegame, wordlist);
    scorelist = load_scores(scoresfile);

    while (scorelist->total_count > 0)
    {
        if (thegame->players[PLAYERONE].hand->total_count < MAXLETTER)
        {
            /* deal for player 1 */
            deal_letters(scorelist, thegame->players[PLAYERONE].hand);
        }
        if (thegame->players[PLAYERTWO].hand->total_count < MAXLETTER)
        {
            /* deal for player 2 */
            deal_letters(scorelist, thegame->players[PLAYERTWO].hand);
        }
        /* player one's turn */
        if (currentplayer == PLAYERONE)
        {
            moveresult = player_turn(&thegame->players[PLAYERONE]);
            if (moveresult == MOVE_QUIT)
            {
                declare_winner(&thegame->players[PLAYERONE], &thegame->players[PLAYERTWO]);
                free_memory(&thegame->players[PLAYERONE], &thegame->players[PLAYERTWO], thegame, scorelist);
                exit(EXIT_SUCCESS);
            }

            currentplayer = PLAYERTWO;
        }
        /* player two's turn */
        else
        {
            moveresult = player_turn(&thegame->players[PLAYERTWO]);
            if (moveresult == MOVE_QUIT)
            {
                declare_winner(&thegame->players[PLAYERONE], &thegame->players[PLAYERTWO]);
                free_memory(&thegame->players[PLAYERONE], &thegame->players[PLAYERTWO], thegame, scorelist);
                exit(EXIT_SUCCESS);
            }

            currentplayer = PLAYERONE;
        }
    }
}

/* free memory */
void free_memory(struct player *p1, struct player *p2, struct game *thegame, struct score_list *scorelist)
{
    int i;

    for (i = 0; i < thegame->theboard->height; i++)
    {
        free(thegame->theboard->matrix[i]);
    }
    free(thegame->theboard->matrix);
    free(p1->hand);
    free(p2->hand);
    free(scorelist);
}

void declare_winner(struct player *p1, struct player *p2)
{
    if (p1->score > p2->score)
    {
        printf("%s is the winner with %d points!\n", p1->name, p1->score);
    }
    else if (p1->score < p2->score)
    {
        printf("%s is the winner with %d points!\n", p2->name, p2->score);
    }
    else
    {
        printf("It's a draw!\n");
    }
}
