#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>

//#define NDEGBUG
#define ERROR -1

typedef struct RLEList_t{
    int numberOfCharacters;
    char character;
    struct RLEList_t* next;
} RLEList_t;


RLEList RLEListCreate()
{
    RLEList list = malloc(sizeof(*list));
    if(!list){
        return NULL;
    }
    list->numberOfCharacters = 0;
    list->character = 0;
    list->next = NULL;
    return list;
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
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList current = list;

    while (current->next != NULL){
        current = current->next;
    }

    if (current->character == value){
        current->numberOfCharacters++;
        return RLE_LIST_SUCCESS;
    }

    current->next = RLEListCreate();
    if (!current->next){
        return RLE_LIST_OUT_OF_MEMORY;
    }
    current->next->character = value;
    current->next->numberOfCharacters = 1;
    return RLE_LIST_SUCCESS;
}

int RLEListSize(RLEList list)
{
    if (list == NULL){
        return ERROR;
    }
    int total = 0;
    RLEList current = list;
    while (current != NULL){
        total += current->numberOfCharacters;
        current = current->next;
        printf("%d\n", total);
    }
    return total;
}


