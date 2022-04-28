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

    if (!strcmp(argv[1],"-e")){
        asciiArtPrintEncoded(list, targetFile);
        free(list);
        fclose(sourceFile);
        fclose(targetFile);
        return 0;
    }
    else if (!strcmp(argv[1],"-i")){
        asciiArtPrint(list, targetFile);
        free(list);
        fclose(sourceFile);
        fclose(targetFile);
        return 0;
    }
    else{
        return 0;
    }
}



/*
     //printf("%d", RLE_LIST_SUCCESS);
    RLEList a = RLEListCreate();
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'a');
    RLEListAppend(a, 'b');
    RLEListAppend(a, 'b');
    RLEListAppend(a, 'b');
    RLEListAppend(a, 'b');
    RLEListAppend(a, 'b');
    RLEListAppend(a, 'b');
    RLEListAppend(a, 'b');
    RLEListAppend(a, 'b');
    RLEListAppend(a, 'c');
    RLEListAppend(a, 'd');
    RLEListAppend(a, 'e');
    RLEListAppend(a, 'f');
    RLEListAppend(a, 'g');
    RLEListAppend(a, 'h');
    RLEListAppend(a, 'i');
    RLEListAppend(a, 'i');
//    printf("first string:\n");
//    printf("%s", RLEListExportToString(a, NULL));
//    printList(a);
//    //printf("HEHE\n");
//    printf("get: %c\n", RLEListGet(a, 5, NULL));
//    printf("BYR\n");
//    printf("total: %d\n", RLEListSize(a));
//    printf("remove code: %d\n", RLEListRemove(a, 1));
//    printf("changed string:\n");
//    printList(a);
//    printf("total: %d\n", RLEListSize(a));
//    printf("%s", RLEListExportToString(a, NULL));
//
//    RLEListDestroy(a);


    //printf("Hello\n");

    FILE* testfile = fopen("C:/Users/USER/Desktop/maherbitar/untitled/test1.txt", "r");
    if(!testfile)
    {
        printf("ERROR OPENING FILE\n");
        return 0;
    }

    printf("fileIsOpened\n");

    RLEList inputFile = asciiArtRead(testfile);

    fclose(testfile);

    printf("testFileIsClosed\n");

//    printf("%s", RLEListExportToString(inputFile, NULL));


    FILE* outputFile = fopen("C:/Users/USER/Desktop/maherbitar/untitled/output1.txt", "w");
    if(!outputFile)
    {
        printf("ERROR OPENING FILE\n");
        return 0;
    }
    printf("noProblemOpeningTheFile\n");
    //RLEListResult result = asciiArtPrint(inputFile, outputFile);

    RLEListResult result2 = asciiArtPrintEncoded(a, outputFile);
    //printf("result = %d\n", result);

    fclose(outputFile);

 */