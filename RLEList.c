#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

int RLEListSize(RLEList list);
char RLEListGet(RLEList list, int index, RLEListResult *result);
void RLEListDestroy(RLEList list);
RLEList RLEListCreate();
RLEListResult RLEListAppend(RLEList list, char value);
RLEListResult RLEListRemove(RLEList list, int index);
RLEListResult RLEListMap(RLEList list, MapFunction map_function);
char* RLEListExportToString(RLEList list, RLEListResult* result);


struct RLEList_t{
    char data;
    int dataCount;
    RLEList next;
};

//implement the functions here


RLEList RLEListCreate(){
    RLEList head = malloc(sizeof (*head));
    if (!head) {return NULL;}
    head ->data='0';
    head ->dataCount=0;
    head ->next=NULL;
    return head;
}

RLEListResult RLEListAppend(RLEList list, char value){
    if (!list | !value) {return RLE_LIST_NULL_ARGUMENT;}
    int size = RLEListSize(list);
    if (size==0) {
        list->data = value;
        list->dataCount =1;
        return RLE_LIST_SUCCESS;
    }

    int ctr=0;
    RLEList current = list;
    while(ctr+current->dataCount < size) {
        ctr+=current->dataCount;
        current =current->next;
    }

    //check if the requested char exists
    if (current->data != value) {
        RLEList new =malloc(sizeof (*new));
        if (!new) {return RLE_LIST_OUT_OF_MEMORY;}
        new-> data = value;
        new-> dataCount = 1;
        new-> next = NULL;
        current->next = new;
    }
    else current -> dataCount = current->dataCount + 1;
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListRemove(RLEList list, int index){
    if (!list) {return RLE_LIST_NULL_ARGUMENT;}
    int size = RLEListSize(list);
    if ((size-1)<index) {return RLE_LIST_INDEX_OUT_OF_BOUNDS;}

    //if in the first item.
    if ((index<list->dataCount) || (list->next == NULL)) {
        list->dataCount -=1;
        if ((list->dataCount == 0 ) && (list->next != NULL)) {
            RLEList toDelete = list->next;
            list->data = toDelete->data;
            list->dataCount = toDelete->dataCount;
            list->next = toDelete->next;
            free(toDelete);
        }
        return RLE_LIST_SUCCESS;
    }

    //search the relevant item.
    int currentIndex =0;
    RLEList previous;
    while (list) {
        currentIndex+=list->dataCount;
        if (index < (currentIndex)) break;
        previous = list;
        list = list->next;
    }

    list->dataCount-=1;
    if (list->dataCount == 0){
        RLEList toDelete = list;
        previous->next = list->next;
        free(toDelete);
    }
    return RLE_LIST_SUCCESS;
}

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (!list) {return RLE_LIST_NULL_ARGUMENT;}
    RLEList current = list;
    while (current) {
        current->data = map_function(current->data);
        current = current->next;
    }
    return RLE_LIST_SUCCESS;
}

void RLEListDestroy(RLEList list){
    while(list)
    {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

int RLEListSize(RLEList list){
    if(list == NULL) return -1;
    int charCounter = 0;
    while(list){
        charCounter += list->dataCount;
        list = list->next;
    }
    return charCounter;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    RLEListResult internalResult =RLE_LIST_SUCCESS;
    if(list == NULL) internalResult = RLE_LIST_NULL_ARGUMENT;
    else if((RLEListSize(list)-1) <index) internalResult = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    else {
        int currentIndex =0;
        if (result) *result = RLE_LIST_SUCCESS;
        while (list) {
            currentIndex+=list->dataCount;
            if (index < (currentIndex)) return list->data;
            list = list->next;
        }
    }
    if (result) *result = internalResult;
    return 0;
}

char* RLEListExportToString(RLEList list, RLEListResult* result){
    RLEListResult internalResult = RLE_LIST_SUCCESS;
    if(list == NULL) {
        if (result!=NULL) *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int RLE_length =1;
    for (RLEList current=list;current->next != NULL;current=current->next,RLE_length++);
    char* wantedString = malloc(sizeof(char) * (RLE_length * 5 + 1));
    int currentIndex = 0;
    for (int i=0;i<RLE_length;i++){
        wantedString[currentIndex++] = list->data;
        int hundreds = list->dataCount%1000/100;
        if (hundreds!=0) wantedString[currentIndex++] = hundreds + '0';
        int tens = list->dataCount%100/10;
        if (hundreds!=0||tens!=0) wantedString[currentIndex++] = tens + '0';
        int units = list->dataCount%10;
        wantedString[currentIndex++] = units + '0';
        wantedString[currentIndex++] = '\n';
        list = list->next;
    }
    wantedString[currentIndex]='\0';
    if (result!=NULL) *result= internalResult;
    if(internalResult == RLE_LIST_SUCCESS) {return wantedString;}
    else return NULL;
}
