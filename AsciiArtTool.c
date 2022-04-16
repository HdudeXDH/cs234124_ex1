//
// Created by User on 4/16/2022.
//

#include "RLEList.h"
#include "AsciiArtTool.h"

//TODO: move to header file
#define CHUNK_SIZE 1 //256

RLEList asciiArtRead(FILE* in_stream){
    FILE* stream = fopen("hello.txt", "w");
    //char buffer[CHUNK_SIZE];
    char buffer;
    RLEList list = RLEListCreate();
    while (fgets(buffer, CHUNK_SIZE, stream) != NULL) {
        RLEListAppend(list,buffer);
    }
    return list;

};
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){

};
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){

};