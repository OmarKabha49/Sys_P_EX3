#include "StrList.h"
#include <stdio.h>
#include <string.h>

typedef struct _StrList StrList;

typedef struct strNode{
    char * data;
    struct strNode * next;
}strNode;


struct _StrList{
    struct strNode * head;
    size_t length;
};

void swap(strNode * node1,strNode * node2);

//first we need to allocate the string into the node
strNode * strNode_alloc(char* data,strNode* next){
    strNode * p = (strNode*) malloc(sizeof(strNode));
    p->data = strdup(data);
    p->next = next;
    return p;
}

// free the string after the allocation
void strNode_free(strNode * strNode){
    free(strNode->data);
    free(strNode);
}


//allocate string list that contains string nodes
StrList* StrList_alloc(){
    StrList* p = (StrList*) malloc(sizeof(StrList));
    p->head = NULL;
    p->length = 0;
    return p;
}

//free the nodes inside the list , then free the list
void StrList_free(StrList* strList){
    if(strList == NULL) return;
    strNode * head = strList->head;
    strNode *p;
    while (head){
        p = head;
        head = head->next;
        strNode_free(p);
    }
    free(strList);
}

size_t StrList_size(const StrList* strList){
    return strList->length;
}

void StrList_insertLast(StrList* strList, const char* data){
    strNode * newNode = strNode_alloc((char*)data,NULL);
    //let the head of the list be the new node if the list is empty
    if(strList->head == NULL){
        strList->head = newNode;
    }
    else{
        //else , we iterate until we get null is equal to current.next
        strNode * curr = strList->head;
        while (curr->next != NULL){
            curr = curr->next;
        }
        //let the current.next be the new node
        curr->next = newNode;
    }
    //make the list length bigger
    strList->length += 1;
}

void StrList_insertAt(StrList* StrList,const char* data,int index){
    //invalid index
    if(index < 0 || index > StrList->length){ return;}

    //let the new node be the head of list if index = 0
    if(index == 0){
        strNode * newNode = strNode_alloc((char*)data,StrList->head);
        StrList->head = newNode;
    }
    //else, we iterate until we find the correct place
    else{
        strNode * curr = StrList->head;
        for (int i = 0; i < index -1; ++i){
            curr = curr->next;
        }
        //let tne next of the current node be the new node
        strNode * newNode = strNode_alloc((char*)data,curr->next);
        curr->next = newNode;
    }
    //after inserting a new node we should add 1 to the length
    StrList->length+=1;
}

char* StrList_firstData(const StrList* StrList){
    if(StrList->head != NULL){
        return StrList->head->data;
    }
    return NULL;
}

void StrList_print(const StrList* StrList){
    if(StrList_size(StrList)==0){return;}
    strNode * curr = StrList->head;
    while (curr->next!=NULL){
        printf("%s ",curr->data);
        curr = curr->next;
    }
    printf("%s",curr->data);
}

void StrList_printAt(const StrList* StrList,int index){
    if(index < 0 || index > StrList->length){ return;}
    strNode * curr = StrList->head;
    for (int i = 0; i < index; ++i) {
        curr = curr->next;
    }
    printf("%s",curr->data);
}

int StrList_count(StrList* StrList, const char* data){
    strNode * curr = StrList->head;
    int counter = 0;
    while(curr != NULL){
        if(strcmp(curr->data,data) == 0){counter++;}
        curr = curr->next;
    }
    return counter;
}


void StrList_remove(StrList* StrList, const char* data){
    strNode * curr = StrList->head;
    strNode * prev = NULL;

    while(curr != NULL) {
        if (strcmp(curr->data, data) == 0) {
            if (prev == NULL) {StrList->head = curr->next;}
            else {prev->next = curr->next;}
            strNode_free(curr);
            StrList->length -= 1;

            if(prev == NULL){curr = StrList->head;}
            else{curr = prev->next;}

        } else{
            prev = curr;
            curr = curr->next;
        }
    }
}

void StrList_removeAt(StrList* StrList, int index){
    if(index < 0 || index > StrList->length) return;
    strNode * curr = StrList->head;
    strNode * prev = NULL;
    int i = 0;
    while(curr!=NULL && i < index){
        prev = curr;
        curr = curr->next;
        i++;
    }

    if(prev == NULL) {StrList->head = curr->next;}
    else{prev->next = curr->next;}

    strNode_free(curr);
    StrList->length-=1;

}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    strNode * p1 = StrList1->head;
    strNode * p2 = StrList2->head;

    while(p1!= NULL && p2 != NULL){
        if(strcmp(p1->data,p2->data) != 0){return 0;}
        p1 = p1->next;
        p2 = p2->next;
    }
    return 1;
}

StrList* StrList_clone(const StrList* strList){
    StrList* clone = StrList_alloc();
    strNode * curr = strList->head;

    while (curr != NULL){
        StrList_insertLast(clone,curr->data);
        curr = curr->next;
    }
    return clone;
}

void StrList_reverse( StrList* StrList){
    strNode * curr = StrList->head;
    strNode * next = NULL;
    strNode * prev = NULL;

    while(curr != NULL){
        next = curr->next; // store the next of the current node
        curr->next = prev; // revers the pointer

        prev = curr;
        curr = next;
    }
    StrList->head = prev;
}

void StrList_sort(StrList* StrList){
    //empty list and list with one element is already sorted
    if(StrList == NULL || StrList->head->next == NULL){ return;}


    //bubble sort
    strNode * curr = StrList->head;
    strNode * next = curr->next;
    while(curr != NULL){
        while (next!= NULL){
            if(strcmp(curr->data,next->data) > 0){
                swap(curr,next);
            }
            next = next->next;
        }
        if(curr->next != NULL){
            curr = curr->next;
            next = curr->next;
        } else{ break;}
    }
}

int StrList_isSorted(StrList* StrList){
    //empty list and list with one element is already sorted
    if(StrList == NULL || StrList->head->next == NULL){ return 1;}

    strNode * curr = StrList->head;
    strNode * next = curr->next;
    //comparing between the current node and the next node if the list is not sorted then return 0, else return 1
    while(curr != NULL) {
        while (next != NULL) {
            if (strcmp(curr->data, next->data)  >  0) {return 0;}
            next = next->next;
        }
        if(curr->next != NULL){
            curr = curr->next;
            next = curr->next;
        } else{ break;}
    }
    return 1;
}

//swap between the data
void swap(strNode * node1,strNode * node2){
    char *temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

//count how much character in the list
int StrList_CountTheCharacters(StrList* strList){
    strNode * curr = strList->head;
    int counter = 0;
    for (int i = 0; i < StrList_size(strList); ++i) {
        counter+= strlen(curr->data);
        curr = curr->next;
    }
    return counter;
}