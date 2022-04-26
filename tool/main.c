#include "AsciiArtTool.h"
#include "RLEList.h"
#include <stdbool.h>
#include <string.h>
char invertMapChars(char source){
    if (source==' ') return '@';
    else return source;
}

int main (int argc, char** argv){
    bool iFlag = false;
    for (int i=0; i<argc;i++ ){
        if (strcmp(argv[i],"-i")==0) iFlag=true;
    }
    char * input_file = argv[argc-2], * output_file = argv[argc-1];
    FILE* inputStream = fopen(input_file, "r");
    FILE* outputStream = fopen(output_file, "w");
    RLEList list = asciiArtRead(inputStream);

    if(iFlag) {
        RLEListMap(list, invertMapChars);
        asciiArtPrint(list, outputStream);
    }
    else asciiArtPrintEncoded(list, outputStream);

    fclose(outputStream);
    fclose(inputStream);
    RLEListDestroy(list);
    return 0;


}