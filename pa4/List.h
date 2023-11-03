//-----------------------------------------------------------------------------
// Yahli Kijel
// ykijel
// 2023 Fall CSE101 PA4
// List.h
// List ADT header file
//-----------------------------------------------------------------------------

#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

#define FORMAT "%d"

typedef void* ListElement;
typedef struct ListObj* List;

List newList(void);

void freeList(List* pL);

int length(List L);

int index(List L);

ListElement front(List L);

ListElement back(List L);

ListElement get(List L);

void clear(List L);

void set(List L, ListElement x);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, ListElement x);

void append(List L, ListElement x);

void insertBefore(List L, ListElement x);

void insertAfter(List L, ListElement x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

void printList(FILE* out, List L);

List concatList(List A, List B);

#endif
