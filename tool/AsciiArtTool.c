#include "AsciiArtTool.h"


RLEList asciiArtRead(FILE* in_stream){
    char buffer[CHUNK_SIZE];
    RLEList list = RLEListCreate();
    while (fgets(buffer, CHUNK_SIZE, in_stream)) {
        for (int i=0;(i<CHUNK_SIZE)&&(buffer[i]!=NULL_END);i++) {
            RLEListAppend(list, buffer[i]);
        }
    }
    return list;

}
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream){
    char buffer[2];
    buffer[1] = '\0';
    if(!list) return RLE_LIST_NULL_ARGUMENT;
    for(int i =0; i< RLEListSize(list);i++)
    {
        buffer[0] = RLEListGet(list,i, NULL);
        fputs(buffer,out_stream);
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream){
    if(!list) return RLE_LIST_NULL_ARGUMENT;
    char *buffer = RLEListExportToString(list,NULL);
    fputs(buffer,out_stream);
    return RLE_LIST_SUCCESS;
}