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
#include <assert.h>

#include "board.h"
#include "player.h"
#include "score_list.h"
#include "player.h"
#include "io.h"

#ifndef GAME_H
#define GAME_H
#define MAX_PLAYERS 2
#define MAXRAND 6

#define PLAYERONE 1
#define PLAYERTWO 2
#define COINFLIP 2

struct game
{
    struct player players[MAX_PLAYERS];
    int curr_player_num;
    struct board *theboard;
    struct letter_list *score_list;
};

BOOLEAN game_init(struct game *);
void play_game(const char *);



BOOLEAN get_board_size(int *width, int *height);
int flip_coin();





#endif
