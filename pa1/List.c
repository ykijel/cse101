#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj* Node;

typedef struct NodeObj{
ListElement data;
Node next;
Node prev;
} NodeObj;

typedef struct ListObj{
Node front;
Node back;
Node cursor;
int length;
int cursor_index;
} ListObj;

List newList(void)
{
List L = malloc(sizeof(ListObj));
L->front = L->back = L->cursor = NULL;
L->length = 0;
L->cursor_index = -1;
return L;
}

void freeList(List* pL)
{
if(pL != NULL && *pL != NULL)
{
while(*pL->front != NULL)
{
Node temp = *pL->front;
*pL->front = *pL->front->next;
free(temp);
}
free(*pL);
*pL = NULL;
}
}

int length(List L)
{
return L->length;
}

int index(List L)
{
return L->cursor_index;
}

int front(List L)
{
if(length(L) > 0)
{
return L->front->data;
}

return -1;
}

int back(List L)
{
if(length(L) > 0)
{
return L->back->data;
}

return -1;
}

int get(List L)
{
if(length(L) > 0 && index(L) >= 0)
{
return L->cursor->data;
}
return -1;
}

bool equals(List A, List B)
{
if(length(A) != length(B))
{
return false;
}

Node tempA = A->front;
Node tempB = B->front;
while(tempA != NULL && tempB != NULL)
{
if(tempA->data != tempB->data)
{
return false;
}
tempA = tempA->next;
tempB = tempB->next;
}
return true;

}

void clear(List L);

void set(List L, int x)
{
if(length(L) > 0 && index >= 0)
{
L->cursor->data = x;
}
}

void moveFront(List L)
{
if(length(L) > 0)
{
L->cursor = L->front;
L->cursor_index = 0;
}
}

void moveBack(List L)
{
if(length(L) > 0)
{
L->cursor = L->back;
L->cursor_index = length(L) - 1;
}
}


void movePrev(List L)
{
if(length(L) > 0 && index(L) >= 0)
{
if(L->cursor != L->front)
{
L->cursor = L->cursor->prev;
L->cursor_index--;
}
else{
L->cursor = NULL;
L->cursor_index = -1;
}
}

}

void moveNext(List L)
{
if(length(L) > 0 && index(L) >= 0)
{
if(L->cursor != L->back)
{
L->cursor = L->cursor->next;
L->cursor_index++;
}
else{
L->cursor = NULL;
L->cursor_index = -1;
}
}
}

void prepend(List L, int x)
{
Node newNode = malloc(sizeof(NodeObj));
newNode->data = x;
newNode->prev = NULL;
newNode->next = L->front;

if(length(L) == 0)
{
L->back = newNode;
}
else
{
L->front->prev = newNode;
}

L->front = newNode;
L->length++;
}

void append(List L, int x)
{
Node newNode = malloc(sizeof(NodeObj));
newNode->data = x;
newNode->prev = L->back;
newNode->next = NULL;

if(length(L) == 0)
{
L->back = newNode;
}
else
{
L->back->next = newNode;
}

L->back = newNode;
L->length++;
}

void insertBefore(List L, int x)
{
if(length(L) > 0 && index(L) >= 0)
{
Node newNode = malloc(sizeof(NodeObj));
newNode->data = x;
newNode->prev = L->cursor->prev;
newNode->next = L->cursor;
L->cursor->prev = newnode;
L->length++;
L->cursor_index++;

if(L->cursor->prev != NULL)
{
L->cursor->prev->next = newNode;
}
else{
L->front = newNode;
}



}
}

void insertAfter(List L, int x)
{
if(length(L) > 0 && index(L) >= 0)
{
Node newNode = malloc(sizeof(NodeObj));
newNode->data = x;
newNode->prev = L->cursor;
newNode->next = L->cursor->next;
L->cursor->next = newnode;
L->length++;

if(L->cursor->next != NULL)
{
L->cursor->next->prev = newNode;
}
else{
L->back = newNode;
}
}
}

void deleteFront(List L)
{
if(length(L) > 0)
{
Node temp = L->front;

if(L->front == L->cursor)
{
L->cursor = NULL;
L->cursor_index = -1;
}

L->front = L->front->next;

if(L->front != NULL)
{
L->front->prev = NULL;
}
else{
L->back = NULL;
}

free(temp);
L->length--;
}
}

void deleteBack(List L)
{
if(length(L) > 0)
{
Node temp = L->back;

if(L->back == L->cursor)
{
L->cursor = NULL;
L->cursor_index = -1;
}

L->back = L->back->prev;

if(L->back != NULL)
{
L->back->next = NULL;
}
else{
L->front = NULL;
}

free(temp);
L->length--;
}
}

void delete(List L)
{
if(length(L) > - && index(L) >= 0)
{
Node temp = L->cursor;
}
if(L->cursor == L->front)
{
L->front = L->front->next;
if(L->front != NULL)
{
L->front->prev = NULL;
}
else{
L->back = NULL;
}
}
else if(L->cursor == L->back)
{
L->back = L->back->prev;
if(L->back != NULL)
{
L->back->next = NULL;
}
else
{
L->front = NULL;
}
}
else{
L->prev->next = L->cursor->next;
L->cursor->next->prev = L->cursor->prev;
}

free(temp);
L->cursor = NULL;
L->cursor_index = -1;
L->length--;
}

void printList(FILE* out, List L);

List copyList(List L);
