#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

#define FLAG 1
#define SOURCE_FILE 2
#define TARGET_FILE 3
#define NUMBER_OF_ARGUMENTS 4
#define ENCODED_FLAG "-e"
#define INVERTED_FLAG "-i"

/**
 * This is AsciiArtTool program
 * @return
 */
int main(int argc, char** argv)
{
    if((argc != NUMBER_OF_ARGUMENTS) || (strcmp(argv[FLAG], ENCODED_FLAG) != 0 && strcmp(argv[FLAG], INVERTED_FLAG) != 0)){
        printf("Error receiving the arguments\n");
        return 0;
    }

    FILE *sourceFile = fopen(argv[SOURCE_FILE], "r");
    if (!sourceFile){
        printf("Error, can't open file: %s\n", argv[SOURCE_FILE]);
        return 0;
    }
    FILE *targetFile = fopen(argv[TARGET_FILE], "w");
    if (!targetFile){
        printf("Error, can't create file: %s", argv[TARGET_FILE]);
        fclose(sourceFile);
        return 0;
    }
    RLEList list = asciiArtRead(sourceFile);
    if (!list){
        printf("Couldn't create list in main\n");
        fclose(sourceFile);
        fclose(targetFile);
    }
    
    if (!strcmp(argv[FLAG],ENCODED_FLAG)){
        asciiArtPrintEncoded(list, targetFile);
        RLEListDestroy(list);
        fclose(sourceFile);
        fclose(targetFile);
        return 0;
    }
    else if (!strcmp(argv[FLAG],INVERTED_FLAG)){
        asciiInvertImage(list);
        asciiArtPrint(list, targetFile);
        RLEListDestroy(list);
        fclose(sourceFile);
        fclose(targetFile);
        return 0;
    }
    else{
        return 0;
    }
}