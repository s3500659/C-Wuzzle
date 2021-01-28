/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include "shared.h"
#ifndef BOARD_H
#define BOARD_H
struct player;
struct cell {
    struct player* owner;
    int letter;
};

struct board {
    struct cell** matrix;
    int width;
    int height;
};

struct board* new_board(int, int);
#endif
