#include <stdio.h>
#include <stdlib.h>
#include "List.h"

typedef struct NodeObj* Node;

typedef struct NodeObj{
	int data;
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
	 	L->cursor_index = front(L);
	 }
}

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int x);

void append(List L, int x);

void insertBefore(List L, int x);

void insertAfter(List L, int x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

void printList(FILE* out, List L);

List copyList(List L);

