#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//-----------------------------------//
#define ADD_CHARACTER_AND_NEXT_LINE 2
#define ERROR -1
#define NEXT_LINE '\n'
//-----------------------------------//
static int numberOfDigits(int number);
static int findIndex(RLEList list, int index);
static int exportedStringLength(RLEList list);
static RLEListResult joinTwoAdjacentNodes(RLEList list);
static void exportedStringBuild(RLEList list, char *exportedString);
//-----------------------------------//


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
        if (temp != NULL){
            current->next = temp->next;
        }
        if (temp->next != NULL && current->character == temp->next->character){
            joinTwoAdjacentNodes(current);
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

    current = list->next;
    RLEList nextNode = current;
    while (current != NULL && nextNode != NULL){
        if (current->character == nextNode->character){
            joinTwoAdjacentNodes(current);
            nextNode = current->next;
        }
        else{
            nextNode = nextNode->next;
            current = current->next;
        }
    }
    return RLE_LIST_SUCCESS;
}

//Checking the nodes "before and after" a node has to be removed totally (usually has 1 character)
// and merge them if they contain the same character
static RLEListResult joinTwoAdjacentNodes(RLEList list)
{
    RLEList current = list;
    RLEList nextNode = current->next;
    if (nextNode != NULL && current->character == nextNode->character ){
        current->numberOfCharacters += nextNode->numberOfCharacters;
        RLEList deleteSameCharLink = nextNode;
        current->next = deleteSameCharLink->next;
        free(deleteSameCharLink);
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
    int stringLength = exportedStringLength(list);
    /*
    int stringLength = 0;
    RLEList current = list->next;
    while (current != NULL)
    {
        stringLength += numberOfDigits(current->numberOfCharacters);
        stringLength += ADD_CHARACTER_AND_NEXT_LINE;
        current = current->next;
    }
    */
    char *exportedString = (char*) malloc(sizeof(char) * (stringLength + 1)  ); //+1 is for the '\0'
    if (!exportedString){
        if (result != NULL){
            *result = RLE_LIST_ERROR;
            return NULL;
        }
    }
    exportedStringBuild(list, exportedString);
    /*
    RLEList current = list->next;
    int index = 0;
    while (current != NULL)
    {
        exportedString[index] = current->character;
        index++;
        sprintf(&exportedString[index], "%d", current->numberOfCharacters);
        index += numberOfDigits(current->numberOfCharacters);
        exportedString[index] = NEXT_LINE;
        index++;
        current = current->next;
    }
    exportedString[index] = '\0';
     */

    if (result != NULL){
        *result = RLE_LIST_SUCCESS;
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


static int exportedStringLength(RLEList list)
{
    int stringLength = 0;
    RLEList current = list->next;
    while (current != NULL){
    stringLength += numberOfDigits(current->numberOfCharacters);
    stringLength += ADD_CHARACTER_AND_NEXT_LINE;
    current = current->next;
    }

    return stringLength;
}


static void exportedStringBuild(RLEList list, char *exportedString)
{
    RLEList current = list->next;
    int index = 0;
    while (current != NULL)
    {
        exportedString[index] = current->character;
        index++;
        sprintf(&exportedString[index], "%d", current->numberOfCharacters);
        index += numberOfDigits(current->numberOfCharacters);
        exportedString[index] = NEXT_LINE;
        index++;
        current = current->next;
    }
    exportedString[index] = '\0';
}