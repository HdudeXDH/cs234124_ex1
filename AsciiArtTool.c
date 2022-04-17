//
// Created by User on 4/16/2022.
//


#include "AsciiArtTool.h"


//TODO: move to header file
#define CHUNK_SIZE 256 //256

RLEList asciiArtRead(FILE* in_stream){
    char buffer[CHUNK_SIZE];
    RLEList list = RLEListCreate();
    while (fgets(buffer, CHUNK_SIZE, in_stream) != EOF) {
        for (int i=0;(i<CHUNK_SIZE)&(buffer[i]!=NULL);i++) {
            RLEListAppend(list, buffer[i]);
        }
    }
    return list;

};
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    char buffer;
    if(!list) return RLE_LIST_NULL_ARGUMENT;
    for(int i =0; i< RLEListSize(list);i++)
    {
        buffer = RLEListGet(list,i, NULL);
        fputs(buffer,out_stream);
    }
    return RLE_LIST_SUCCESS;
};

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
    if(!list) return RLE_LIST_NULL_ARGUMENT;
    char * buffer = RLEListExportToString(list,NULL);
    fputs(buffer,out_stream);
    return RLE_LIST_SUCCESS;
};