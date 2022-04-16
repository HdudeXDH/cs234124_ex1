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
    if ((RLEListSize(list)-1)<index) {return RLE_LIST_INDEX_OUT_OF_BOUNDS;}
    //if in the first item.
    if (index<list->data_count) {
        list->data_count -=1;
        return RLE_LIST_SUCCESS;
    }

    RLEList current = list;
    RLEList previous;
    for (int ctr=0; (ctr<index) |(!current); ctr+=current->data_count) {
        previous = current;
        current =current->next;
    }

    if (current->data_count == 1){
        if (current->next == NULL) {previous->next = NULL;}
        else {previous->next = current->next;}
        free(current);
    }
    else{
        current->data_count -=1;
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
    while(list)
    {
        RLEList toDelete = list;
        list = list->next;
        free(toDelete);
    }
}

int RLEListSize(RLEList list){
    if(list == NULL) return -1;
    int char_ctr = 0;
    while(list){ // TODO: offir i
        char_ctr += list->data_count;
        list = list->next;
    }
    return char_ctr;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){ //shouldnt do what is suppose to
    if(list == NULL) *result = RLE_LIST_NULL_ARGUMENT;
    else if((RLEListSize(list)-1) <index) *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;

    else {
        int current_index =0;
        *result = RLE_LIST_SUCCESS;
        while (list) {
            if (index < (current_index+list->data_count)) return (list+index)->data;
        }
    }
    return 0;
}
