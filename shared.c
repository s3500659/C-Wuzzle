#include "shared.h"

int gen_randomnumber(int max)
{
    int random_number = RAND_MAX;

    if (random_number > max)
    {
        random_number = rand() % max;
    }
    return random_number;
}