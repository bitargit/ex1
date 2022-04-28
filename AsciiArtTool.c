#include "AsciiArtTool.h"

#define SPACE ' '
#define AT_SIGN '@'
#define END_OF_STRING '\0'
RLEList asciiArtRead(FILE* in_stream) {
    RLEList list = RLEListCreate();
    if(!list){
        return NULL;
    }
    char character;
    RLEListResult result;
    while ((character = fgetc(in_stream)) != EOF){
        result = RLEListAppend(list, character);
        if (result != RLE_LIST_SUCCESS){
            //maybe delte list?
            return NULL;
        }
    }
    return  list;
}

RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    int listLength = RLEListSize(list);
    if (listLength < 0){
        return listLength;
    }
    for (int index = 0; index < listLength; index++){
        char current_character = RLEListGet(list, index, NULL);
        if (current_character == 0){
            return RLE_LIST_NULL_ARGUMENT;
        }
        fputc(current_character, out_stream);
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if (list == NULL || out_stream == NULL){
        return RLE_LIST_NULL_ARGUMENT;
    }

    char *stringExported = RLEListExportToString(list, NULL);
    if (!stringExported){
        return RLE_LIST_NULL_ARGUMENT;
    }

    int i = 0;
    while(stringExported[i] != END_OF_STRING){
        char current_character = stringExported[i];
        fputc(current_character, out_stream);
        i++;
    }
    free(stringExported);
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiInvertImage(RLEList list){
    RLEListMap(list, mapList);
    return RLE_LIST_SUCCESS;
}

char mapList(char current){
    if (current == SPACE){
        current = AT_SIGN;
    }
    else if(current == AT_SIGN){
        current = SPACE;
    }
    return current;
}