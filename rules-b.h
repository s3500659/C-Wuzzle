/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include "shared.h"




#ifndef RULES_B_H
#define RULES_B_H
struct player;
enum move_result {
    MOVE_QUIT,
    MOVE_SKIP,
    MOVE_SUCCESS,
    MOVE_BOARD_FULL
};
struct coord {
    int x, y;
};

enum orientation {
    HORIZ,
    VERT
};

BOOLEAN validate_move(struct player* theplayer, const char* word,
                      const struct coord* coords, enum orientation orient);
BOOLEAN check_fit_board(enum orientation orient, const struct coord *coords, struct player *theplayer, const char *word);
BOOLEAN make_move(BOOLEAN isFirstMove, struct player *theplayer, const char *word, const struct coord *coords, enum orientation orient);
BOOLEAN has_letter(const char *word, struct player *theplayer);
void place_letter(int letter, struct player *theplayer, const struct coord *coords, BOOLEAN isfirstmove);
void place_letter_horiz(const char *word, struct player *theplayer, const struct coord *coords, BOOLEAN isfirstmove);
void place_letter_vert(const char *word, struct player *theplayer, const struct coord *coords, BOOLEAN isfirstmove);
void decrease_letter_count(struct player *theplayer, int letter);
void increase_player_score(struct player *theplayer, int letter);
int get_letter_score(int letter, struct player *theplayer);
int calculate_score(struct player* theplayer);
#endif
