#include "RLEList.h"
#include <stdlib.h>

int RLEListSize(RLEList list);
char RLEListGet(RLEList list, int index, RLEListResult *result);
void RLEListDestroy(RLEList list);


struct RLEList_t{
    char data;
    int data_count;
    RLEList next;
};

//implement the functions here
#define NULL 0
typedef struct RLEList_t *RLEList; //TODO: why should be here?

RLEList RLEListCreate(){
    RLEList head = malloc(sizeof (*head));
    if (!head) {return NULL;}
    head ->data="";
    head ->data_count=0;
    head ->next=NULL;
    return head;
};

RLEListResult RLEListAppend(RLEList list, char value){
    if (!list | !value) {return RLE_LIST_NULL_ARGUMENT;}
    int size = RLEListSize(list);
    RLEList tail;
    //check if the requested char exists
    if (RLEListGet(list, size, tail) != value) {
        RLEList new =malloc(sizeof (*new));
        if (!new) {return RLE_LIST_OUT_OF_MEMORY;}
        new-> data = value;
        new-> data_count = 1;
        new-> next = NULL;
        tail->next = new;
    }
    else tail -> data_count = tail->data_count + 1;
    return RLE_LIST_SUCCESS;
};

RLEListResult RLEListRemove(RLEList list, int index){
    if (!list) {return RLE_LIST_NULL_ARGUMENT;}
    if ((RLEListSize(list)-1)<index) {return RLE_LIST_INDEX_OUT_OF_BOUNDS}
    RLEList result;
    RLEListGet(list,index,result);
    if (result->data_count == 1){
        RLEList previous;
        RLEListGet(list,index-1,previous);
        if (result->next == NULL) {previous->next = NULL;}
        else {previous->next = result->next;}
        free(result);
    }
    else{
        result->data_count -=1;
    }

    return RLE_LIST_SUCCESS;
};

RLEListResult RLEListMap(RLEList list, MapFunction map_function){
    if (!list) {return RLE_LIST_NULL_ARGUMENT;}
    RLEList current = list;
    while (current) {
        current->data = map_function(current->data);
        current = current->next;
    }
    return RLE_LIST_SUCCESS;
};

//TODO: ofir: check if my functions are working properly
void RLEListDestroy(RLEList list){
    while(!list)
    {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

int RLEListSize(RLEList list){
    if(list == NULL) return -1;
    int char_ctr = 0;
    while(!list){ // TODO: offir i
        char_ctr += list->data_count;
        list = list->next;
    }
    return char_ctr;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){ //shouldnt do what is suppose to
    if(list == NULL) *result = RLE_LIST_NULL_ARGUMENT;
    else if((list+index) == NULL) *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    else *result = RLE_LIST_SUCCESS;
    if(*result == RLE_LIST_SUCCESS)
        return (list+index)->data;
    else return 0;
}