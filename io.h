#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shared.h"
#include "word_list.h"


#define EXTRACHARS 2
#define BOARDSIZELEN 4
#define MINBOARDSIZE 5


#ifndef IO_H
#define IO_H
enum input_result
{
    IR_FAILURE,
    IR_SUCCESS,
    IR_EOF = -1
};


enum input_result get_user_input(char *str, int buffer_len);
BOOLEAN get_board_size(int *width, int *height);
void clear_buffer(void);
BOOLEAN save_to_file(struct word_list *thelist, const char *filename);
#endif