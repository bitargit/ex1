#include <stdio.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"

/**
 * This is AsciiArtTool program
 * @return
 */
int main(int argc, char** argv)
{
    if(argc != 3){
        printf("Error receiving the arguments\n");
        return 0;
    }

    FILE *sourceFile = fopen(argv[1], "r");
    FILE *targetFile = fopen(argv[2], "w");
    RLEList list = asciiArtRead(sourceFile);


    if (!strcmp(argv[0],"-e")){
        asciiArtPrintEncoded(list, targetFile);
        fclose(sourceFile);
        fclose(targetFile);
        return 0;
    }
    else if (!strcmp(argv[0],"-i")){
        asciiArtPrint(list, targetFile);
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