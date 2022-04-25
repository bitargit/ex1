#include "RLEList.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
//#define NDEGBUG
#define ERROR -1
#define NEXT_LINE '\n'
#define MULTIPLIER_EXPORT_STRING 3
#define SIZE_OF_EXPORTED_LINK 4
#define CHARACTER 0
#define NUMBER_OF_CHARACTERS 1
#define END_LINE 2
#define END_OF_STRING 3
#define NULL_CHAR '\0'


typedef enum {
    NODE_INDEX,
    CHAR_INDEX
} Index;

static int findIndex(RLEList list, int index, Index type);

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
    int numberOfNodes = findIndex(list, index, NODE_INDEX);
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

static int findIndex(RLEList list, int index, Index type)
{
    RLEList current = list->next;
    int countNodes = 1, count = 0;
    while (count < index){
        if (count + current->numberOfCharacters <= index){
            count += current->numberOfCharacters;
            current = current->next;
            countNodes++;
        }
        else{
            while (count < index){
                count++;
            }
        }
    }
    return (type == NODE_INDEX ? countNodes : count);
}

char RLEListGet(RLEList list, int index, RLEListResult *result)//result return values problematic
{
    if (list == NULL){
        *result = (result != NULL) ? RLE_LIST_NULL_ARGUMENT : *result;
        return 0;
    }

    if (index >= RLEListSize(list) || index < 0){
        *result = (result != NULL) ? RLE_LIST_INDEX_OUT_OF_BOUNDS : *result;
        return 0;
    }

    int charIndexInList = findIndex(list, index, NODE_INDEX);
    RLEList current = list;
    int i = 0;

    while (i < charIndexInList - 1){
        current = current->next;
        i++;
    }
    //*result = (result != NULL) ? RLE_LIST_SUCCESS : *result;
   // printf("%d\n", *result);
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

char* RLEListExportToString(RLEList list, RLEListResult* result){
    if (list == NULL){
        *result = (result != NULL) ? RLE_LIST_NULL_ARGUMENT : *result;
        return NULL;
    }
    int sizeOfList = RLEListSize(list);
    int numberOfNodes = findIndex(list, sizeOfList - 1, NODE_INDEX);
    char* formatedString = malloc(numberOfNodes * MULTIPLIER_EXPORT_STRING);
    if (!formatedString){
        *result = (result != NULL) ? RLE_LIST_ERROR : *result;
        return NULL;
    }
    RLEList current = list->next;
    char *tempString = malloc(SIZE_OF_EXPORTED_LINK);
    if (!tempString){
        *result = (result != NULL) ? RLE_LIST_ERROR : *result;
        return NULL;
    }
    while (current != NULL){
        tempString[CHARACTER] = current->character;
        tempString[NUMBER_OF_CHARACTERS] = current->numberOfCharacters;//convert to string
        tempString[END_LINE] = NEXT_LINE;
        tempString[END_OF_STRING] = NULL_CHAR;
        //printf("%s", tempString);
        strcat(formatedString, tempString);
        current = current->next;
    }
    free(tempString);
    return formatedString;
}

void printList(RLEList list)
{
    RLEList current = list->next;
    while (current != NULL){
        for(int i = 0; i < current->numberOfCharacters; i++){
            printf("%c", current->character);
        }
        current = current->next;
    }
    printf("\n");
}