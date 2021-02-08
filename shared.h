/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include <stdlib.h>
#include <time.h>

#define BASE10 10
#define MAXLETTER 5
#define MAXLOCATIONLEN 3
#define ORIENTATIONLEN 1
#define MAX_PLAYERS 2
#define MAXRAND 6
#define PLAYERONE 0
#define PLAYERTWO 1
#define COINFLIP 2

#ifndef SHARED_H
#define SHARED_H
typedef enum { FALSE, TRUE } BOOLEAN;
int gen_randomnumber(int max);

#endif
