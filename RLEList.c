//
// Created by USER on 13/04/2022.
//
#include "RLEList.h"

typedef struct RLEList_t{
    int numberOfCharachters;
    char character;
    struct RLEList_t* next;
} *RLEList;


RLEList RLEListCreate()
{
    RLEList ptr = malloc(sizeof(*ptr));
    if(!ptr)
    {
        return NULL;
    }
}

void RLEListDestroy(RLEList list)
{
    while (list)
    {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

RLEListResult RLEListAppend(RLEList list, char value)
{
    RLEList current = list;
    while (current->next != NULL)
    {
        current = current->next;
    }
    if (current->character == value)
    {
        current->numberOfCharachters++;
    }
    current->next = malloc(sizeof(RLEList));
    current->next->character = value;
    current->next->numberOfCharachters = 0;
}

int RLEListSize(RLEList list)
{
    int total = 0;
    RLEList current = list;
    while (current->next != NULL)
    {
        total += current->numberOfCharachters;
        current = current->next;
    }
    return total;
}


