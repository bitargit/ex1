#include "AsciiArtTool.h"


#include <stdlib.h>






RLEList asciiArtRead(FILE* in_stream) {
    RLEList list = RLEListCreate();
    RLEList current = list;
//    FILE* in_str = fopen(in_stream, 'r');
//    if (!in_str) {
//        //error
//        return 0;
//    }

    char buffer[1] = "";

    while (*buffer != EOF){//OR buffer[0]
        fgets(buffer, 1, in_stream);
        RLEListAppend(current, buffer[0]);
        //in_str++;
    }
    fclose(in_stream);
    return  list;
}



RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    RLEListResult *result = NULL;
    int list_len = RLEListSize(list);
    for (int index; index < list_len; index++){
        char current_character = RLEListGet(list, index, result);
        fputs(current_character, out_stream);
    }

    return result;
}



RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{

}



















