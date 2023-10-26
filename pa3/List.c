//-----------------------------------------------------------------------------
// Yahli Kijel
// ykijel
// 2023 Fall CSE101 PA3
// List.c
// List ADT implementation and functions
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

#define FORMAT "%d"

typedef struct NodeObj* Node;

typedef struct NodeObj
{
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
    if (pL != NULL && *pL != NULL)
    {
        while ((*pL)->front != NULL)
        {
            Node temp = (*pL)->front;
            (*pL)->front = (*pL)->front->next;

            // Free the memory of the node being deleted
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
	if(length(L) > 0 && L->front != NULL)
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
	if(length(L) > 0 && index(L) >= 0 && L->cursor != NULL)
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

void clear(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: Attempted to clear a NULL list.\n");
        exit(1);
    }

    // Free all nodes in the list
    while (length(L) > 0)
    {
        deleteFront(L);
    }
}

void set(List L, int x)
{
	if(length(L) > 0 && index(L) >= 0)
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
		else
		{
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
		else
		{
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
	L->cursor_index++;
}

void append(List L, int x)
{
	Node newNode = malloc(sizeof(NodeObj));
	newNode->data = x;
	newNode->prev = L->back;
	newNode->next = NULL;

	if(length(L) == 0)
	{
		L->front = L->back = newNode;
	}
	else
	{
		L->back->next = newNode;
		L->back = newNode;
	}
	L->length++;
}

void insertBefore(List L, int x)
{
    if (length(L) > 0 && index(L) >= 0)
    {
        Node newNode = malloc(sizeof(NodeObj));
        if (newNode == NULL)
        {
            fprintf(stderr, "Error: Failed to allocate memory for new node.\n");
            exit(1);
        }

        newNode->data = x;

        if (L->cursor->prev != NULL)
        {
            newNode->prev = L->cursor->prev;
            L->cursor->prev->next = newNode;
        }
        else
        {
            newNode->prev = NULL;
            L->front = newNode;
        }

        newNode->next = L->cursor;
        L->cursor->prev = newNode;

        L->length++;
        L->cursor_index++;
    }
}

void insertAfter(List L, int x)
{
    if (length(L) > 0 && index(L) >= 0)
    {
        Node newNode = malloc(sizeof(NodeObj));
        if (newNode == NULL)
        {
            fprintf(stderr, "Error: Failed to allocate memory for new node.\n");
            exit(1);
        }
        newNode->data = x;

        newNode->next = L->cursor->next;
        newNode->prev = L->cursor;
        L->cursor->next = newNode;

        if (newNode->next != NULL)
        {
            newNode->next->prev = newNode;
        }
        else
        {
            L->back = newNode;
        }

        L->length++;
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
		if(L->cursor_index != -1)
		{
			L->cursor_index--;
		}
		
	}
}

void deleteBack(List L)
{
    if (length(L) > 0)
    {
        if (L->cursor == L->back)
        {
            L->cursor = L->cursor->prev;
            L->cursor_index=-1;
        }
        
        Node temp = L->back;

        if (L->length == 1)
        {
            L->front = NULL;
            L->back = NULL;
        }
        else
        {
            if (L->back == L->cursor)
            {
                L->cursor = L->cursor->prev;
                L->cursor_index--;
            }

            L->back = L->back->prev;
            L->back->next = NULL;
        }
        free(temp);
        L->length--;
    }
}

void delete(List L) {
    if (length(L) > 0 && index(L) >= 0) {
    	
    	Node temp = L->cursor;
        if (L->cursor == L->front) {
            L->front = L->front->next;
            if (L->front != NULL) {
                L->front->prev = NULL;
            } else {
                L->back = NULL;
            }
        } else if (L->cursor == L->back) {
            L->back = L->back->prev;
            if (L->back != NULL) {
                L->back->next = NULL;
            } else {
                L->front = NULL;
            }
        } else {
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev;
        }

        L->cursor = NULL;
        L->cursor_index = -1;
        L->length--;
        
        free(temp);
     
    }
}

void printList(FILE* out, List L)
{
    if (L == NULL || out == NULL)
    {
        fprintf(stderr, "Error: NULL List or output file.\n");
        return;
    }
    
    Node current = L->front;

    while (current != NULL)
    {
        fprintf(out, FORMAT, current->data);

        if (current->next != NULL)
        {
            fprintf(out, " ");
        }

        current = current->next;
    }

    fprintf(out, "");
}

List copyList(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "Error: Attempted to copy a NULL list.\n");
        exit(1);
    }

    List copiedList = newList(); // Create a new list

    Node current = L->front; // Start from the front of the original list

    while (current != NULL)
    {
        append(copiedList, current->data); // Append each element to the new list
        current = current->next;
    }

    return copiedList;
}

List concatList(List A, List B) {
    List result = newList();

    // Copy elements from List A to the result
    Node currentA = A->front;
    while (currentA != NULL) {
        append(result, currentA->data);
        currentA = currentA->next;
    }

    // Copy elements from List B to the result
    Node currentB = B->front;
    while (currentB != NULL) {
        append(result, currentB->data);
        currentB = currentB->next;
    }

    return result;
}
