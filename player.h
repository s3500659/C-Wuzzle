/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include "rules-b.h"
#include "io.h"
#include "word_list.h"

/* the maximum length of a player's name */
#define NAMELEN 40


/**
 * enumeration that defines the colours that can be used for players
 **/
enum color {
    COL_RED,
    COL_GREEN,
    COL_YELLOW,
    COL_BLUE,
    COL_MAGENTA,
    COL_CYAN,
    COL_RESET
};
/* global variable that holds the colour codes that can be used for formatting
 * strings */
extern char *color_strings[];

/**
 * definition of the player structure.
 **/
struct player {
    char name[NAMELEN + 1];
    enum color color;
    struct game *curgame;
    struct score_list *hand;
    int score;
};

BOOLEAN player_init(struct player *, const char *, struct game *);
BOOLEAN get_player_name(struct player *player);
int gen_randomnumber(int max);
enum color get_playercolour(int colournumber);
BOOLEAN validate_player_colour(struct player *p1, struct player *p2);
void print_board(struct player *theplayer);
char *get_color_name(enum color col);
enum move_result player_turn(struct player *theplayer, struct word_list *wordlist);
void print_player_hand(struct player *theplayer);
enum input_result get_new_word(struct player *theplayer, char *new_word);
enum input_result get_word_location(char *new_location);
enum input_result get_orientation(char *ori);
BOOLEAN is_command(const char *command, struct word_list *wordlist);
#endif
