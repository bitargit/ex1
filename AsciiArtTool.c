#include "AsciiArtTool.h"


#include <stdlib.h>






RLEList asciiArtRead(FILE* in_stream) {
    RLEList list = RLEListCreate();
    RLEList current = list;

    char character;
    while ((character = fgetc(in_stream)) != EOF){
        printf("%c\n", character);
        RLEListAppend(current, character);
        //in_str++;
    }
    fclose(in_stream);
    return  list;
}



RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    int list_len = RLEListSize(list);
    for (int index = 0; index < list_len; index++){//OR index = 1
        char current_character = RLEListGet(list, index, NULL);
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
    printf("exported =\n%s\n", stringExported);
    int i = 0;
    while(stringExported[i] != '\0'){
        char current_character = stringExported[i];
        fputc(current_character, out_stream);
        i++;
    }

    return RLE_LIST_SUCCESS;
}



















