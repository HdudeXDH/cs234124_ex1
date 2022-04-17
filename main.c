//
// Created by User on 4/16/2022.
//
#include "AsciiArtTool.h"
#include "RLEList.h"
#include <stdbool.h>
#include <string.h>
char invertMapChars(char source){
    if (source==' ') return '@';
    else return source;
}

int main (int argc, char** argv){
    bool i_flag = false,e_flag=false;
    for (int i=0; i<argc;i++ ){
        if (strcmp(argv[i],"-i")==0) i_flag=true;
        if (strcmp(argv[i],"-e")==0) e_flag=true;
    }
    char * input_file = argv[argc-2], * output_file = argv[argc-1];
    FILE* input_stream = fopen( input_file,"r");
    FILE* output_stream = fopen(output_file,"w");
    RLEList  list = asciiArtRead(input_stream);

    if(i_flag) {
        RLEListMap(list, invertMapChars);
        asciiArtPrint(list,output_stream);
    }
    else asciiArtPrintEncoded(list,output_stream);
    printf("%s , %s , %s , %s",argv[0],argv[1],argv[2],argv[3] );
    printf("%s , %s , %s , %s",argv[0],argv[1],argv[2],argv[3] );
    printf("ofir  ha homo");
    fclose(output_stream);
    fclose(input_stream);
    RLEListDestroy(list);
    return 0;


}