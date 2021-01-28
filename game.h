/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "board.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H
#define MAX_PLAYERS 2
#define MAXRAND 6
#define EXTRACHARS 2
#define PLAYERONE 1
#define PLAYERTWO 2

struct game
{
    struct player players[MAX_PLAYERS];
    int curr_player_num;
    struct board *theboard;
    struct letter_list *score_list;
};

BOOLEAN game_init(struct game *);
void play_game(const char *);

int gen_randomnumber(int max);
enum color get_playercolour(int colournumber);

enum input_result
{
    IR_FAILURE,
    IR_SUCCESS,
    IR_EOF = -1
};

enum input_result get_user_input(char *str, int buffer_len);
void clear_buffer(void);

#endif
