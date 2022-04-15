#include "RLEList.h"

int RLEListSize(RLEList list);
char RLEListGet(RLEList list, int index, RLEListResult *result);
void RLEListDestroy(RLEList list);


struct RLEList_t{
    char data;
    int data_count;
    RLEList next;
};

//implement the functions here

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
    while(!list){
        char_ctr += list->data_count;
        list = list->next;
    }
    return char_ctr;
}

char RLEListGet(RLEList list, int index, RLEListResult *result){
    if(list == NULL) *result = RLE_LIST_NULL_ARGUMENT;
    else if((list+index) == NULL) *result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    else *result = RLE_LIST_SUCCESS;
    if(*result == RLE_LIST_SUCCESS)
        return (list+index)->data;
    else return 0;
}