/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include <stdlib.h>
#include "score_list.h"
/**
 * returns a malloced list of the scores loaded in from disk. As this is file io
 * you need to validate file data to ensure it is valid. Do not however validate
 *the file name.
 **/
#define DELIM "\n"
#define COMMADELIM ","
#define COMMACOUNT 2
#define MAXTOKENS 26
#define MAXSCORE 100

struct score_list *load_scores(const char *filename)
{
    struct score_list *newscorelist = malloc(sizeof(struct score_list));
    char *scorelist = strdup(filename);
    char *token;
    int pos = 0;
    int comma_count = 0;
    char *end;
    int scorelist_count = 0;

    /* get the first token */
    token = strtok(scorelist, DELIM);
    /* get other tokens */
    while (token != NULL)
    {
        struct score newscore;

        /* check first pos is a valid letter */
        if (*(token + pos) < 'A' || *(token + pos) > 'Z')
        {
            fprintf(stderr, "Error: Invalid letter.\n");
            return NULL;
        }
        newscore.letter = *(token + pos);
        pos++;
        if ((*(token + pos) == ','))
        {
            comma_count++;
            if ((*(token + (pos + 1)) == ','))
            {
                fprintf(stderr, "Error: incorrect format.\n");
                return NULL;
            }
        }
        pos++;
        while (*(token + pos) != ',')
        {
            int score = EOF;
            score = strtol((token + pos), &end, BASE10);
            if (score <= 0 || score > MAXSCORE)
            {
                fprintf(stderr, "Error: invalid letter score.\n");
                return NULL;
            }
            if (score >= 10)
            {
                pos++;
            }
            newscore.score = score;
            pos++;
        }
        if (*(token + pos) == ',')
        {
            comma_count++;
        }
        pos++;
        while (*(token + pos) != '\0')
        {
            int count = EOF;
            count = strtol((token + pos), &end, BASE10);
            if (count <= 0 || count > MAXSCORE)
            {
                fprintf(stderr, "Error: invalid letter count.\n");
                return NULL;
            }
            if (count >= 10)
            {
                pos++;
            }
            newscore.count = count;
            pos++;
        }

        newscorelist->scores[scorelist_count++] = newscore;
        newscorelist->num_scores++;
        newscorelist->total_count += newscore.count;

        token = strtok(NULL, DELIM);
        pos = 0;
        comma_count = 0;
    }

    print_scorelist(newscorelist);

    return NULL;
}

void print_scorelist(struct score_list *newscorelist)
{
    int i;
    for (i = 0; i < MAXTOKENS; i++)
    {
        printf("letter=%d, score=%d, count=%d\n", newscorelist->scores[i].letter,
               newscorelist->scores[i].score, newscorelist->scores[i].count);
    }
}

BOOLEAN init_scorelist(struct score_list *scorelist)
{
    if (scorelist == NULL)
    {
        return FALSE;
    }
    scorelist = (struct score_list *)malloc(sizeof(struct score_list));
    scorelist->num_scores = 0;
    scorelist->total_count = 0;
    return TRUE;
}

BOOLEAN check_comma_format(char *token)
{
    int position = 0;
    int comma_count = 0;
    /* check for 2 commas */
    while (*(token + position) != '\0')
    {
        if (*(token + position) == ',')
        {
            if (*(token + (position + 1)) == ',')
            {
                fprintf(stderr, "Error: incorrect comma format.\n");
                return FALSE;
            }
            comma_count++;
        }
        position++;
    }
    if (comma_count != COMMACOUNT)
    {
        fprintf(stderr, "Error: there's not %d comma.\n", COMMACOUNT);
        return FALSE;
    }

    return TRUE;
}

/**
 * deal letters from the score list in random order, so that the player hand has
 *five letters at the end.
 **/
void deal_letters(struct score_list *score_list,
                  struct score_list *player_hand) {}

/**
 * a convenience function we provide to you to make it easier to copy strings.
 * Please note that this does some memory allocation but you are not required
 * to free that memory as that's out of the scope of this assignment.
 **/
char *strdup(const char *orig)
{
    /* make space for the string copy */
    char *copy = malloc(sizeof(char) * (strlen(orig) + 1));
    if (!copy)
    {
        perror("strdup");
        return NULL;
    }
    /* copy the string */
    strcpy(copy, orig);
    return copy;
}
