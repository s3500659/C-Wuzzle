/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include "board.h"
#include "player.h"
#ifndef GAME_H
#define GAME_H
#define MAX_PLAYERS 2
struct game {
    struct player players[MAX_PLAYERS];
    int curr_player_num;
    struct board* theboard;
    struct letter_list* score_list;
};

BOOLEAN game_init(struct game*);
void play_game(const char*);
#endif
