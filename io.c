#include "io.h"

/* get input for board size */
BOOLEAN get_board_size(int *width, int *height)
{
    enum input_result inputresult;
    char board_width[BOARDSIZELEN + EXTRACHARS], board_height[BOARDSIZELEN + EXTRACHARS];
    char *end;

    printf("Please enter the width of the board:\n");
    inputresult = get_user_input(board_width, BOARDSIZELEN);
    if (inputresult != IR_SUCCESS)
    {
        return FALSE;
    }
    *width = (int)strtol(board_width, &end, BASE10);

    if (*width < MINBOARDSIZE)
    {
        fprintf(stderr, "Error: Width must be equal or greater than %d\n", MINBOARDSIZE);
        return FALSE;
    }

    printf("Please enter the height of the board:\n");
    inputresult = get_user_input(board_height, BOARDSIZELEN);
    if (inputresult != IR_SUCCESS)
    {
        return FALSE;
    }
    *height = (int)strtol(board_height, &end, BASE10);

    if (*height < MINBOARDSIZE)
    {
        fprintf(stderr, "Error: height must be equal or greater than %d\n", MINBOARDSIZE);
        return FALSE;
    }

    return TRUE;
}

enum input_result get_user_input(char *str, int buffer_len)
{
    int len = 0;

    if (fgets(str, buffer_len + EXTRACHARS, stdin) == NULL)
    {
        return IR_EOF;
    }

    if (str[0] == '\n')
    {
        return IR_FAILURE;
    }

    len = strlen(str);
    if (str[len - 1] != '\n')
    {
        fprintf(stderr, "Error: Too many input causing buffer overflow\n");
        clear_buffer();
        return IR_FAILURE;
    }
    else
    {
        str[len - 1] = '\0';
    }

    return IR_SUCCESS;
}

void clear_buffer(void)
{
    int ch;
    while (ch = getc(stdin), ch != EOF && ch != '\n')
        ;
    clearerr(stdin);
}
