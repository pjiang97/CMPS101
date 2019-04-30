//Peter Jiang
//pjiang1
//CMPS101 PA4
//List.h

//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

typedef struct ListObj* List;

//constructor-destructor
List newList(void);
void freeList(List* pL);

//access functions
int length(List L);
int index(List L);
int front(List L);
int back(List L);
int get(List L);
int equals(List A, List B);

//manipulation procedures
void clear(List L);
void moveFront(List L);
void moveBack(List L);
void movePrev(List L);
void moveNext(List L);
void prepend(List L, int data);
void append(List L, int data);
void insertBefore(List L, int data);
void insertAfter(List L, int data);
void deleteFront(List L);
void deleteBack(List L);
void delete(List L);

//other operations
void printList(FILE* out, List L);
List copyList(List L);

#endif
