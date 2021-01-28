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

#define REQUIRED_ARGS 2
#define FILEARG 1
#define LINELEN 300
#define EXTRACHARS 2

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

    while (fgets(line, LINELEN + EXTRACHARS, reader) != NULL) {
        
        strcat(array, line);
    }

    return TRUE;
}

int main(int argc, char *argv[])
{
    /* check the command line args and then pass the appropriate arg to
     * play_game()
     **/

    char scorelist[LINELEN + EXTRACHARS] = "";
    FILE *reader;

    if (REQUIRED_ARGS != argc)
    {
        fprintf(stderr, "Error: invalid args provided. "
                        "You need to provide a filename to open!\n");
        return EXIT_FAILURE;
    }

    reader = open_file(argv[FILEARG]);

    if (!reader)
    {
        return EXIT_FAILURE;
    }

    if (!read_scorelist(reader, scorelist))
    {
        fclose(reader);
        return EXIT_FAILURE;
    }
    fclose(reader);

    play_game(scorelist);

    return EXIT_SUCCESS;
}
