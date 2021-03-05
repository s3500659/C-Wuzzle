/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include <ctype.h>
#include <time.h>
#include "player.h"
#include "rules-b.h"
#include "game.h"
#include "board.h"
#include "score_list.h"

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
    if (!theplayer->hand)
    {
        perror("Error: malloc failed when allocating for theplayer->hand inside player_init()\n");
    }
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

    return TRUE;
}

#define DEF_FILENAME "OUTPUT"
/**
 * play a move for this player. please see the assignment specification for the
 * details of this.
 **/
enum move_result player_turn(struct player *theplayer, struct word_list *wordlist)
{
    char new_word[MAXLETTER + EXTRACHARS] = "";
    char new_location[MAXLOCATIONLEN + EXTRACHARS] = "";
    char new_orientation[ORIENTATIONLEN + EXTRACHARS] = "";
    enum input_result result;
    struct coord *coords = malloc(sizeof(struct coord));
    enum orientation orient;
    char *token, *end;
    int i = 0;
    char chr;

    if (!coords)
    {
        perror("Error: malloc failed when allocating for struct coord inside player_turn()\n");
    }

    print_board(theplayer);
    printf("it is %s's turn and their colour is %s%s%s, and their score is %d.\n", theplayer->name,
           color_strings[theplayer->color], get_color_name(theplayer->color), color_strings[COL_RESET], theplayer->score);
    print_player_hand(theplayer);

    do
    {
        /* end the game? */
        printf("To end the game please input cltr+d\n");
        /* get new word from player */
        result = get_new_word(theplayer, new_word);
        if (IR_EOF == result)
        {
            save_to_file(wordlist, DEF_FILENAME);
            return MOVE_QUIT;
        }
        if (IR_FAILURE == result)
        {
            return MOVE_SKIP;
        }
        /* convert word to uppercase */
        while (new_word[i])
        {
            chr = toupper(new_word[i]);
            new_word[i] = chr;
            i++;
        }
        i = 0;
    } while (is_command(new_word, wordlist));

    /* check word exist in dictionary */
    if (!is_in_dictionary(wordlist, new_word))
    {
        fprintf(stderr, "Error: the word does not exist in the dictionary!\n");
        return MOVE_SKIP;
    }

    /* get coordinates for the word */
    result = get_word_location(new_location);
    if (IR_EOF == result)
    {
        save_to_file(wordlist, DEF_FILENAME);
        return MOVE_QUIT;
    }
    if (IR_FAILURE == result)
    {
        return MOVE_SKIP;
    }
    /* get orientation */
    result = get_orientation(new_orientation);
    if (IR_EOF == result)
    {
        save_to_file(wordlist, DEF_FILENAME);
        return MOVE_QUIT;
    }
    if (IR_FAILURE == result)
    {
        return MOVE_SKIP;
    }
    /* convert coord string to struct */
    token = strtok(new_location, ",");
    coords->x = (int)strtol(token, &end, BASE10);
    token = strtok(NULL, ",");
    coords->y = (int)strtol(token, &end, BASE10);

    /* convert orient string to enum */
    if (strcmp(new_orientation, "h") == 0)
    {
        orient = HORIZ;
    }
    else
    {
        orient = VERT;
    }
    validate_move(theplayer, new_word, coords, orient);

    return MOVE_SUCCESS;
}

#define CMD_TRIGGER ':'
#define CMD_DELIM ": "
#define HELP_CMD "HELP"
#define ADD_CMD "ADD"
#define DEL_CMD "DELETE"
#define SAVE_CMD "SAVE"
/* checks wether the input word contains a command, relating args. 
If there is a valid command then the appropriate function will be executed */
BOOLEAN is_command(const char *command, struct word_list *wordlist)
{
    char *cmd = strdup(command);
    char *token;
    int i = 0;
    BOOLEAN has_command = FALSE;
    clock_t start, end;

    for (i = 0; i < strlen(command); i++)
    {
        if (*(command + i) == CMD_TRIGGER)
        {
            has_command = TRUE;
        }
    }
    if (has_command)
    {
        token = strtok(cmd, CMD_DELIM);
        while (token != NULL)
        {
            if (strcmp(token, HELP_CMD) == 0)
            {
                printf("==== Help Command ====\n"
                       "Add: You can add a new word to the dictionary by using the add command (:add patatoes).\n"
                       "Delete: You can delete a word from the dictionary by using the delete command (:delete potatoes)\n"
                       "Save: You can save save the word dictionary to a file by using the save command (:save filename)\n");
                return TRUE;
            }
            if (strcmp(token, ADD_CMD) == 0)
            {
                start = clock();
                token = strtok(NULL, CMD_DELIM);
                /* check the args contain letters from the English alphabet */
                i = 0;
                while (token[i])
                {
                    if (isalpha(token[i]) == 0)
                    {
                        fprintf(stderr, "Error: You can only add words in the English alphabet!\n");
                        return FALSE;
                    }
                    i++;
                }
                /* insert word into dictionary */
                if (!list_add(wordlist, token))
                {
                    fprintf(stderr, "Error: failed adding word to dictionary inside is_command()\n");
                    return FALSE;
                }
                printf("'%s' added to the dictionary!\n", token);
                end = clock();
                printf("It took %f seconds to insert a new word into the dictionary\n", ((double)(end - start)/CLOCKS_PER_SEC));
                return TRUE;
            }
            if (strcmp(token, DEL_CMD) == 0)
            {
                start = clock();
                token = strtok(NULL, CMD_DELIM);
                /* check the args contain letters from the English alphabet */
                i = 0;
                while (token[i])
                {
                    if (isalpha(token[i]) == 0)
                    {
                        fprintf(stderr, "Error: You can only delete words in the English alphabet!\n");
                        return FALSE;
                    }
                    i++;
                }
                /* delete word from dictionary */
                if (!list_del(wordlist, token))
                {
                    fprintf(stderr, "Error: failed deleting word from dictionary inside is_command()\n");
                    return FALSE;
                }
                printf("'%s' deleted from the dictionary!\n", token);
                end = clock();
                printf("it took %f seconds to delete a word from the dictionary\n", ((double)(end - start)/CLOCKS_PER_SEC));
                return TRUE;
            }
            if (strcmp(token, SAVE_CMD) == 0)
            {
                start = clock();
                token = strtok(NULL, CMD_DELIM);
                /* check the args contain letters from the English alphabet */
                i = 0;
                while (token[i])
                {
                    if (isalpha(token[i]) == 0)
                    {
                        fprintf(stderr, "Error: Filename must only contain letters from the English alphabet!\n");
                        return FALSE;
                    }
                    i++;
                }
                /* save linked list to file */
                if (!save_to_file(wordlist, token))
                {
                    fprintf(stderr, "Error: saving to file has failed inside is_command()\n");
                }
                end = clock();
                printf("The word dictionary took %f seconds to save to file\n", ((double)(end - start)/CLOCKS_PER_SEC));
                
                return TRUE;
            }
            token = strtok(NULL, CMD_DELIM);
            

        }
    }

    return FALSE;
}



/* get the orientation for the new word */
enum input_result get_orientation(char *ori)
{
    enum input_result result;
    printf("Please enter orientation for the world - h for horizontal and v for vertical:\n");
    result = get_user_input(ori, ORIENTATIONLEN + EXTRACHARS);

    return result;
}

/* get location for new word */
enum input_result get_word_location(char *new_location)
{
    enum input_result result;
    printf("Please enter the new location of this wordd (x,y):\n");
    result = get_user_input(new_location, MAXLOCATIONLEN + EXTRACHARS);

    return result;
}

/* get a new word from player */
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
            if (letter == EOF || letter == 0)
            {
                printf("     |");
            }
            else
            {
                printf("  %s%c%s  |", color_strings[theplayer->curgame->theboard->matrix[i][j].owner->color],
                       letter, color_strings[COL_RESET]);
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
