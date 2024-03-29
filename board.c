/******************************************************************************
 * Student Name    : Vinh D Tran    
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 2, study period 4, 2020.
 *****************************************************************************/
#include "board.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct board *new_board(int width, int height)
{
    struct board *newboard = (struct board *)malloc(sizeof(struct board));
    int i, j;

    newboard->width = width;
    newboard->height = height;

    if (!newboard)
    {
        perror("Error: malloc failed for new board inside new_board()\n");
    }

    /* malloc height */
    newboard->matrix = (struct cell **)malloc(height * sizeof(struct cell *));
    if(!newboard->matrix)
    {
        perror("Error: malloc failled when allocating for newboard->matrix\n");
    }
    /* malloc width */
    for (i = 0; i < height; i++)
    {
        newboard->matrix[i] = (struct cell *)malloc(newboard->width * sizeof(struct cell));
        if (!newboard->matrix[i])
        {
            perror("Error: malloc failed when allocating for new matrix cell\n");
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            newboard->matrix[i][j].owner = NULL;
            newboard->matrix[i][j].letter = EOF;
        }
    }

    return newboard;
}
