/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 23, study period 4, 2020.
 *****************************************************************************/
#include "shared.h"
#ifndef WORDLIST_H
#define WORDLIST_H
struct word_node
{
    struct word_node *next;
    const char *word;
};
struct word_list
{
    struct word_node *head;
    long num_words;
};

/**
 * List function prototypes that will be used for the management of the linked
 * list here.
 **/
BOOLEAN is_in_dictionary(struct word_list *, const char *data);

void list_init(struct word_list *thelist);
struct word_list *new_list(void);
BOOLEAN list_add(struct word_list *thelist, const char *data);
BOOLEAN list_del(struct word_list *thelist, const char *data);
void list_free(struct word_list *thelist);

#endif
