/******************************************************************************
 * Student Name    : Vinh D Tran
 * RMIT Student ID : S3500659
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * Assignment 3, study period 4, 2020.
 *****************************************************************************/
#include "word_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "helpers.h"

/* initialise a new word list */
void list_init(struct word_list *thelist)
{
    memset(thelist, 0, sizeof(*thelist));
}

/* create and return an initialised word list */
struct word_list *new_list(void)
{
    struct word_list *newlist;
    newlist = (struct word_list *)malloc(sizeof(struct word_list));
    if (!newlist)
    {
        perror("malloc failed in new_list()\n");
        return NULL;
    }
    list_init(newlist);
    return newlist;
}

int word_cmp(const char *first, const char *second)
{
    int cmp;
    cmp = strcmp(first, second);

    return cmp;
}

BOOLEAN list_add(struct word_list *thelist, const char *data)
{
    /* if prev is null then we're at the beginning of the list */
    struct word_node *curr, *prev = NULL;
    /* create new node */
    struct word_node *newnode = (struct word_node *)malloc(sizeof(struct word_node));
    if (!newnode)
    {
        perror("malloc failed in list_add()\n");
        return FALSE;
    }
    newnode->word = data;
    newnode->next = NULL;
    /* if the list is empty then the head will be NULL */
    if (thelist->head == NULL)
    {
        thelist->head = newnode;
        thelist->num_words++;
        return TRUE;
    }

    for (curr = thelist->head; curr != NULL && word_cmp(curr->word, data) < 0;
         prev = curr, curr = curr->next)
        ;
    /* curr or prev must not be NULL */
    assert(curr || prev);
    /* if prev is NULL then we're at the start of the list */
    if (prev == NULL)
    {
        newnode->next = thelist->head;
        thelist->head = newnode;
    }
    /* we're at the end of the list */
    else if (curr == NULL)
    {
        prev->next = newnode;
    }
    else
    {
        newnode->next = curr;
        prev->next = newnode;
    }
    thelist->num_words++;
    return TRUE;
}

BOOLEAN list_del(struct word_list *thelist, const char *data)
{
    struct word_node *curr, *prev = NULL;

    if (thelist->num_words == 0)
    {
        fprintf(stderr, "Error: the list is already empty!\n");
        return FALSE;
    }

    for (curr = thelist->head; curr && strcmp(curr->word, data) != 0;
         curr = curr->next, prev = curr)
        ;

    if (!curr)
    {
        fprintf(stderr, "Error: no match found!\n");
        return FALSE;
    }

    else if (!prev)
    {
        thelist->head = thelist->head->next;
    }
    else
    {
        prev->next = curr->next;
    }
    free((char*)curr->word);
    free(curr);
    return TRUE;
}

void list_free(struct word_list *thelist)
{
    struct word_node *curr;
    curr = thelist->head;
    while (curr)
    {
        struct word_node *next = curr->next;
        free((char*)curr->word);
        free(curr);
        curr->next = next;
    }
}

/**
 * tests whether the word specified is in the word_list and therefore a valid
 * spelling. Please see the assignment specification for further details.
 **/
BOOLEAN is_in_dictionary(struct word_list *thelist, const char *word)
{
    struct word_node *temp = thelist->head;
    while (temp->next != NULL)
    {
        if(strcmp(temp->word, word) == 0)
        {
            printf("word exist in the dictionary!\n");
            return TRUE;
        }

        temp = temp->next;
    }

    return FALSE;
}
