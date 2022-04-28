#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//#define NDEGBUG

#define ADD_CHARACTER_AND_NEXT_LINE 2

static int findIndex(RLEList list, int index);
static int numberOfDigits(int number);

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
        return RLE_LIST_ERROR;
    }
    int total = 0;
    RLEList current = list->next;
    while (current != NULL){
        total += current->numberOfCharacters;
        current = current->next;
    }
    return total;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if (list == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    if (index >= RLEListSize(list) || index < 0){
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }
    int numberOfNodes = findIndex(list, index);
    int i = 0;
    RLEList current = list;
    while (i < numberOfNodes - 1){
        current = current->next;
        i++;
    }
    if (current->next->numberOfCharacters > 1){
        current->next->numberOfCharacters--;
    }
    else{
        RLEList temp = current->next;
        if (temp->next != NULL && current->character == temp->next->character ){
            current->numberOfCharacters += temp->next->numberOfCharacters;
            RLEList deleteSameCharLink = temp->next;
            current->next = deleteSameCharLink->next;
            free(deleteSameCharLink);
        }
        else{
            current->next = temp->next;
        }
        free(temp);
    }
    return RLE_LIST_SUCCESS;
}

static int findIndex(RLEList list, int index)
{
    RLEList current = list->next;
    int countNodes = 1, count = 0;
    while (count + current->numberOfCharacters <= index){
        count += current->numberOfCharacters;
        current = current->next;
        countNodes++;
    }
    return countNodes;
}


char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if (list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
            return 0;
        }
        return 0;
    }

    if (index >= RLEListSize(list) || index < 0){
        if (result != NULL){
            *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
            return 0;
        }
        return 0;
    }

    int charIndexInList = findIndex(list, index);
    RLEList current = list->next;
    int i = 0;

    while (i < charIndexInList - 1){
        current = current->next;
        i++;
    }
    if (result != NULL){
        *result = RLE_LIST_SUCCESS;
    }
    return current->character;
}


RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (list == NULL || map_function == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList current = list->next;
    while (current != NULL){
        current->character = map_function(current->character);
        current = current->next;
    }
    return RLE_LIST_SUCCESS;
}

char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (list == NULL){
        if (result != NULL){
            *result = RLE_LIST_NULL_ARGUMENT;
        }
        return NULL;
    }
    int stringLength = 0;
    RLEList current = list->next;
    while (current != NULL)
    {
        stringLength += numberOfDigits(current->numberOfCharacters);
        stringLength += ADD_CHARACTER_AND_NEXT_LINE;
        current = current->next;
    }

    char *exportedString = (char*) malloc(sizeof(char) * (stringLength + 1)  ); //+1 is for the '\0'
    if (!exportedString){
        if (result != NULL){
            *result = RLE_LIST_ERROR;
            return NULL;
        }
    }
    current = list->next;
    int index = 0;
    while (current != NULL)
    {
        exportedString[index] = current->character;
        index++;
        sprintf(&exportedString[index], "%d", current->numberOfCharacters);
        index += numberOfDigits(current->numberOfCharacters);
        exportedString[index] = '\n';
        index++;
        current = current->next;
    }
    exportedString[index] = '\0';
    if (result != NULL){
        *result = RLE_LIST_SUCCESS;
        return NULL;
    }
    return exportedString;
}

static int numberOfDigits(int number)
{
    if (number == 0){
        return 1;
    }

    int numberOfDigits = 0;
    while(number > 0)
    {
        number /= 10;
        numberOfDigits++;
    }

    return numberOfDigits;
}