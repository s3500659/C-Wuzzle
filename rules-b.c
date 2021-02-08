/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include "rules-b.h"
#include "game.h"
#include "board.h"
#include "score_list.h"
#include "player.h"

/**
 *  validates the current player's move
 **/
BOOLEAN validate_move(struct player *theplayer, const char *word,
                      const struct coord *coords, enum orientation orient)
{
    BOOLEAN isFirstMove = TRUE;

    if (make_move(isFirstMove, theplayer, word, coords, orient))
    {
        isFirstMove = FALSE;
        calculate_score(theplayer);
        return TRUE;
    }

    return FALSE;
}

BOOLEAN make_move(BOOLEAN isFirstMove, struct player *theplayer, const char *word, const struct coord *coords, enum orientation orient)
{
    if (has_letter(word, theplayer))
    {
        /* horizontal */
        if (orient == HORIZ)
        {
            place_letter_horiz(word, theplayer, coords, isFirstMove);
        }
        /* vertical */
        else
        {
            place_letter_vert(word, theplayer, coords, isFirstMove);
        }
    }
    else
    {
        fprintf(stderr, "Error: that was not a valid move: Please try again.\n");
        return FALSE;
    }
    return TRUE;
}

/* place the letter horizontaly on the board and also decrease the letter count*/
void place_letter_horiz(const char *word, struct player *theplayer, const struct coord *coords, BOOLEAN isfirstmove)
{
    int h;
    int i = 0;
    struct board *board = theplayer->curgame->theboard;

    if (isfirstmove)
    {
        for (h = coords->x - 1; h < board->width; h++)
        {
            if (has_letter(word, theplayer))
            {
                board->matrix[coords->y - 1][h].letter = *(word + i);
                board->matrix[coords->y - 1][h].owner = theplayer;
                decrease_letter_count(theplayer, board->matrix[coords->y - 1][h].letter);

                i++;
            }
        }
    }
    else
    {
        for (h = coords->x - 1; h < board->width; h++)
        {
            if (has_letter(word, theplayer))
            {
                if (board->matrix[coords->y - 1][h].letter == *(word + i))
                {
                    board->matrix[coords->y - 1][h].letter = *(word + i);
                    board->matrix[coords->y - 1][h].owner = theplayer;
                    decrease_letter_count(theplayer, board->matrix[coords->y - 1][h].letter);

                    i++;
                }
            }
        }
    }
}
/* place the letter verticaly on the board and also decrease the letter count*/
void place_letter_vert(const char *word, struct player *theplayer, const struct coord *coords, BOOLEAN isfirstmove)
{
    int v;
    int i = 0;
    struct board *board = theplayer->curgame->theboard;

    if (isfirstmove)
    {
        for (v = coords->y - 1; v < board->width; v++)
        {
            if (has_letter(word, theplayer))
            {
                board->matrix[v][coords->x - 1].letter = *(word + i);
                board->matrix[v][coords->x - 1].owner = theplayer;
                decrease_letter_count(theplayer, board->matrix[coords->y - 1][v].letter);

                i++;
            }
        }
    }
    else
    {
        for (v = coords->y - 1; v < board->width; v++)
        {
            if (has_letter(word, theplayer))
            {
                if (board->matrix[v][coords->x - 1].letter == *(word + i))
                {
                    board->matrix[v][coords->x - 1].letter = *(word + i);
                    board->matrix[v][coords->x - 1].owner = theplayer;
                    decrease_letter_count(theplayer, board->matrix[v][coords->x - 1].letter);

                    i++;
                }
            }
        }
    }
}

/* increase the player's score */
void increase_player_score(struct player *theplayer, int letter)
{
    int i;

    for (i = 0; i < theplayer->hand->num_scores; i++)
    {
        if (theplayer->hand->scores[i].letter == letter)
        {
            theplayer->score += theplayer->hand->scores[i].score;
        }
    }
}

/* decrease count of letter that was placed on the board */
void decrease_letter_count(struct player *theplayer, int letter)
{
    int i;
    for (i = 0; i < theplayer->hand->num_scores; i++)
    {
        if (theplayer->hand->scores[i].letter == letter)
        {
            theplayer->hand->scores[i].count--;
            theplayer->hand->total_count--;
            if (theplayer->hand->scores[i].count == 0)
            {
                theplayer->hand->num_scores--;
            }
        }
    }
}

/* check if the player has the letters on hand to make the word */
BOOLEAN has_letter(const char *word, struct player *theplayer)
{
    int i = 0;
    int pos = 0;
    BOOLEAN result = FALSE;

    for (i = 0; i < theplayer->hand->num_scores; i++)
    {
        if (*(word + pos) == theplayer->hand->scores[i].letter || theplayer->hand->scores[i].letter == 0)
        {
            result = TRUE;
            pos++;
        }
    }

    return result;
}

/* check if the word will fit the board horizontaly or vertically */
BOOLEAN check_fit_board(enum orientation orient, const struct coord *coords, struct player *theplayer, const char *word)
{
    int wordLen = strlen(word);
    int h = coords->x - 1, v = coords->y - 1;
    int freeSpace = 0;

    if (orient == HORIZ)
    {
        for (; h < theplayer->curgame->theboard->width; h++)
        {
            if (theplayer->curgame->theboard->matrix[v][h].letter == -1)
            {
                freeSpace++;
            }
        }
    }
    else
    {
        for (; v < theplayer->curgame->theboard->width; v++)
        {
            if (theplayer->curgame->theboard->matrix[v][h].letter == -1)
            {
                freeSpace++;
            }
        }
    }

    if (freeSpace == wordLen)
    {
        return TRUE;
    }
    return FALSE;
}

int calculate_score(struct player *theplayer)
{
    int score = 0;
    int totalScore = 0;
    int currentLetter;
    int i, j;
    struct board *board = theplayer->curgame->theboard;

    for (i = 0; i < board->height; i++)
    {
        for (j = 0; j < board->width; j++)
        {
            if (board->matrix[i][j].owner == theplayer)
            {
                currentLetter = board->matrix[i][j].letter;
                score = get_letter_score(currentLetter, theplayer);
                if (score > 0)
                {
                    totalScore += score;
                }
            }
        }
    }
    theplayer->score = totalScore;
    printf("%s total score is: %d\n", theplayer->name, theplayer->score);
    return totalScore;
}

#define MAXSCORES 26
int get_letter_score(int letter, struct player *theplayer)
{
    int i;

    for (i = 0; i < MAXSCORES; i++)
    {
        if (letter == theplayer->hand->scores[i].letter)
        {
            return theplayer->hand->scores[i].score;
        }
    }
    return 0;
}
