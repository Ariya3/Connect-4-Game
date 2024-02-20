#ifndef slist_h
#define slist_h

#include <stdio.h>

struct node{
    char data[3];
    struct node* next;
};

struct singlyLinkedList{
    struct node* head;
    struct node* tail;
};

typedef struct singlyLinkedList slist;

slist* createList();
void insertTail(slist* list, const char* data);
void freeList(slist* list);

#endif