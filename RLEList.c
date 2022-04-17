#include "RLEList.h"
#include <stdlib.h>
#include <string.h>

int RLEListSize(RLEList list);
char RLEListGet(RLEList list, int index, RLEListResult *result);
void RLEListDestroy(RLEList list);


struct RLEList_t{
    char data;
    int data_count;
    RLEList next;
};

//implement the functions here


RLEList RLEListCreate(){
    RLEList head = malloc(sizeof (*head));
    if (!head) {return NULL;}
    head ->data='0';
    head ->data_count=0;
    head ->next=NULL;
    return head;
};

RLEListResult RLEListAppend(RLEList list, char value){
    if (!list | !value) {return RLE_LIST_NULL_ARGUMENT;}
    int size = RLEListSize(list);
    RLEList tail;
    if (size==0) {
        list->data = value;
        list->data_count =1;
        return RLE_LIST_SUCCESS;
    }

    int ctr=0;
    RLEList current = list;
    while(ctr+current->data_count<size) {
        ctr+=current->data_count;
        current =current->next;
    }

    //check if the requested char exists
    if (current->data != value) {
        RLEList new =malloc(sizeof (*new));
        if (!new) {return RLE_LIST_OUT_OF_MEMORY;}
        new-> data = value;
        new-> data_count = 1;
        new-> next = NULL;
        current->next = new;
    }
    else current -> data_count = current->data_count + 1;
    return RLE_LIST_SUCCESS;
};

RLEListResult RLEListRemove(RLEList list, int index){
    if (!list) {return RLE_LIST_NULL_ARGUMENT;}
    int size = RLEListSize(list);
    if ((size-1)<index) {return RLE_LIST_INDEX_OUT_OF_BOUNDS;}
    //if in the first item.

    if ((index<list->data_count) || (list->next == NULL)) {
        list->data_count -=1;
        if ((list->data_count ==0 )&&(list->next != NULL)) {
            list = list->next;}
        return RLE_LIST_SUCCESS;
    }

    //search the relevant item.
    int current_index =0;
    RLEList previous;
    while (list) {
        current_index+=list->data_count;
        if (index < (current_index)) break;
        previous = list;
        list = list->next;
    }

//    for (index -= list->data_count; (index- list->next->data_count >0 ) ; index -= list->next->data_count) {
//        list =list->next;
//    }
    list->data_count-=1;
    if (list->data_count==0){
        RLEList to_delete = list;
        previous->next = list->next;
        free(to_delete);
    };
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
    RLEListResult internal_result =RLE_LIST_SUCCESS;
    if(list == NULL) internal_result = RLE_LIST_NULL_ARGUMENT;
    else if((RLEListSize(list)-1) <index) internal_result = RLE_LIST_INDEX_OUT_OF_BOUNDS;
    else {
        int current_index =0;
        if (result) *result = RLE_LIST_SUCCESS;
        while (list) {
            current_index+=list->data_count;
            if (index < (current_index)) return list->data;
            list = list->next;
        }
    }
    if (result) *result = internal_result;
    return 0;
}

char* RLEListExportToString(RLEList list, RLEListResult* result){
    RLEListResult internal_result = RLE_LIST_SUCCESS;
    if(list == NULL) {internal_result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    int RLE_length =1;
    for (RLEList current=list;current->next != NULL;current=current->next,RLE_length++);
    char* wanted_string = malloc(sizeof(char)* (RLE_length*3+1));
//    int i = 0;
//    while(list)
    for (int i=0;i<RLE_length;i++)
    {
      wanted_string[3*i] = list->data;
      wanted_string[3*i+1] = list->data_count +'0';
      wanted_string[3*i+2] = '\n';
      list = list->next;
    }
    wanted_string[RLE_length*3]='\0';
    if (result!=NULL) *result= internal_result;
    if(internal_result == RLE_LIST_SUCCESS) return wanted_string;
    else return NULL;
}
