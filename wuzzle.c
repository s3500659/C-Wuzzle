/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "game.h"
#include "shared.h"
#include <time.h>

#define REQUIRED_ARGS 3
#define SCORELIST_ARGS 1
#define WORDLIST_ARGS 2
#define LINELEN 300
#define EXTRACHARS 2

#define WORDLISTLEN 460000

FILE *open_file(const char *fname)
{
    FILE *reader;

    reader = fopen(fname, "r");
    if (!reader)
    {
        perror("Error in open_file()");
    }
    return reader;
}

BOOLEAN read_scorelist(FILE *reader, char *array)
{
    char line[LINELEN + EXTRACHARS];

    assert(reader != NULL);

    while (fgets(line, LINELEN + EXTRACHARS, reader) != NULL)
    {

        strcat(array, line);
    }

    return TRUE;
}

void print_wordlist(char *list)
{
    int i;

    for (i = 0; i < WORDLISTLEN; i++)
    {
        printf("%c", list[i]);
    }
}

int main(int argc, char *argv[])
{
    char scorelist[LINELEN + EXTRACHARS] = "";
    char wordlist[WORDLISTLEN] = "";
    FILE *reader;

    clock_t start, end;
    

    if (REQUIRED_ARGS != argc)
    {
        fprintf(stderr, "Error: invalid args provided. "
                        "You need to provide a filename to open!\n");
        return EXIT_FAILURE;
    }
    
    start = clock();
    /* read scorelist */
    reader = open_file(argv[SCORELIST_ARGS]);
    if (!reader)
    {
        perror("Error: problem reading scorelist\n");
        return EXIT_FAILURE;
    }
    if (!read_scorelist(reader, scorelist))
    {
        fclose(reader);
        return EXIT_FAILURE;
    }
    fclose(reader);
    end = clock();
    printf("score_list took %f seconds to load.\n", ((double)(end - start)/CLOCKS_PER_SEC));

    start = clock();
    /* read wordlist */
    reader = open_file(argv[WORDLIST_ARGS]);
    if (!reader)
    {
        perror("Error: problem reading wordlist\n");
        return EXIT_FAILURE;
    }
    if (!read_scorelist(reader, wordlist))
    {
        fclose(reader);
        return EXIT_FAILURE;
    }
    fclose(reader);
    end = clock();
    printf("word_list took %f seconds to load.\n", ((double)(end - start)/CLOCKS_PER_SEC));

    play_game(scorelist, wordlist);

    return EXIT_SUCCESS;
}
