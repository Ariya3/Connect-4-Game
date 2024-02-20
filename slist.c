#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

slist* createList(){
    slist* list = (slist*)malloc(sizeof(slist));
    if(list == NULL){
        fprintf(stderr, "Could not create LL\n");
        exit(1);
    }

    list -> head = NULL;
    list -> tail = NULL;
    return list;
}

//creates new node and put it at the end of linked list
void insertTail(slist* list, const char* data){
    //creates new node 
    struct node* newNode;
    newNode = malloc(sizeof(struct node));
    if(newNode == NULL){
        fprintf(stderr, "Couldn't insert node into LL");
        exit(1);
    }

    strcpy(newNode -> data, data);
    newNode -> next = NULL;

    //adjust pointers
    if(list -> head = NULL){
        list -> head = newNode;
        list -> tail = newNode;
    } else {
        list -> head = newNode;
        list -> tail = newNode;
    }
}

//empties the current linked list
void freeList(slist* list){
    struct node* current = list -> head;
    while(current != NULL){
        struct node* temp = current;
        current = current -> next;
        free(temp);
    }
    free(list);
}