#ifndef HW1_ASCII_ART_TOOL_H
#define HW1_ASCII_ART_TOOL_H
#include <stdlib.h>
#include "RLEList.h"

/**
*   asciiArtRead: Recives a file with characters and returns the characters in a RLEList
*
* @param in_stream - Object of type File* that contains the image to compress
* @return
*   NULL in case of a problem
*   RLEList that contains all the characters in the file
*/
RLEList asciiArtRead(FILE* in_stream);


/**
*   asciiArtPrint: Writes an image to the file using the given RLEList
*
* @param list - RLEList that contains all the characters in an image
* @param out_stream - Object of type File* to which the image is writen to
* @return
*   NULL in case of a problem
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
* 	LIST_SUCCESS the RLEList has been successfuly writen to the file.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
*   asciiArtPrintEncoded: Writes an encoded image to the file using the given RLEList
*
* @param list - RLEList that contains all the characters in an image
* @param out_stream - Object of type File* to which the encoded image is writen to
* @return
*   NULL in case of a problem
*   RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
* 	LIST_SUCCESS the RLEList has been successfuly writen to the file.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);
RLEListResult asciiInvertImage(RLEList list);
char mapList(char current);

#endif // HW1_ASCII_ART_TOOL_H