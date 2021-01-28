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
    enum input_result inputresult;
    int random_number;

    srand(time(NULL));

    /* get player one name */
    printf("\nPlease enter name for player one\n");
    inputresult = get_user_input(playerone.name, NAMELEN);
    if (inputresult != IR_SUCCESS)
    {
        return FALSE;
    }
    /* assign colour */
    random_number = gen_randomnumber(MAXRAND);
    playerone.color = get_playercolour(random_number);

    /* get player two name*/
    printf("\nPlease enter name for player two\n");
    inputresult = get_user_input(playertwo.name, NAMELEN);
    if (inputresult != IR_SUCCESS)
    {
        return FALSE;
    }
    /* assign colour */
    random_number = gen_randomnumber(MAXRAND);
    playertwo.color = get_playercolour(random_number);

    /* ensure colour are different */
    while (playerone.color == playertwo.color)
    {
        random_number = gen_randomnumber(MAXRAND);
        playertwo.color = get_playercolour(random_number);
    }

    printf("player one name is %s and colour is %d\n", playerone.name, playerone.color);
    printf("player two name is %s and colour is %d\n", playertwo.name, playertwo.color);

    return TRUE;
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
    struct game thegame;

    game_init(&thegame);
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

int gen_randomnumber(int max)
{
    int random_number = RAND_MAX;

    if (random_number > MAXRAND)
    {
        random_number = rand() % MAXRAND;
    }

    return random_number;
}

enum input_result get_user_input(char *str, int buffer_len)
{
    int len = 0;

    if (fgets(str, buffer_len + EXTRACHARS, stdin) == NULL)
    {
        fprintf(stderr, "EOF detected\n");
        return IR_EOF;
    }

    if (str[0] == '\n')
    {
        fprintf(stderr, "No user input detected\n");
        return IR_FAILURE;
    }

    len = strlen(str);
    if (str[len - 1] != '\n')
    {
        fprintf(stderr, "Too many input causing buffer overflow\n");
        clear_buffer();
        return IR_FAILURE;
    }
    else
    {
        str[len - 1] = '\0';
    }

    return IR_SUCCESS;
}

void clear_buffer(void)
{
    int ch;
    while (ch = getc(stdin), ch != EOF && ch != '\n')
        ;
    clearerr(stdin);
}
