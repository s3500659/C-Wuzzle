/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "shared.h"

#ifndef SCORE_LIST_H
#define SCORE_LIST_H
/**
 * a letter score is a combination of the letter itself, its score and its count
 **/
struct score {
    int letter, score, count;
};
#define NUM_SCORES 26
/**
 * the scores list that contains the scores for all letters and doubles as the
 * 'deck' from which letters are dealt. This is also the structure used by each
 * player to represent their hand.
 **/
#define MAXHAND 5
struct score_list {
    struct score scores[NUM_SCORES];
    int num_scores;
    int total_count;
};

struct score_list *load_scores(const char *);
void deal_letters(struct score_list *, struct score_list *);
char *strdup(const char *orig);
BOOLEAN check_comma_format(char *token);
BOOLEAN init_scorelist(struct score_list *scorelist);
void print_scorelist(struct score_list *newscorelist);
int check_letter_exist(struct score_list *player_hand, struct score_list *score_list, int count, int randomnumber);
#endif
