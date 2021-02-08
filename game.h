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



#ifndef GAME_H
#define GAME_H

#include "shared.h"
#include "player.h"


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
void declare_winner(struct player *p1, struct player *p2);
void free_memory(struct player *p1, struct player *p2, struct game *thegame, struct score_list *scorelist);





#endif
