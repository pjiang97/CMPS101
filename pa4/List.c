//Peter Jiang
//pjiang1
//CMPS 101 PA2
//List.c
//Implementation file for list ADT

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//structs----------------------------------
//private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* previous;
}NodeObj;

typedef NodeObj* Node;

typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;

   int length;
   int index;
}ListObj;

//Constructor Destructors----------------------
// Creates a Node with int data, Node prev, and Node next.
Node newNode(int data, Node previous, Node next){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->previous = previous;
   N->next = next;
   return(N);
}
//node deconstructor
// Free memory for the Node.
void freeNode(Node* pN){
   if(pN != NULL && *pN != NULL){
      free(*pN);
      *pN = NULL;
   }
}

//list constructor
//Creates a new empty List.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// Free memory for the List and the Nodes inside.
void freeList(List* pL){
   if(pL != NULL && *pL != NULL){
      Node temp = (*pL)->front;
      while(temp != NULL){
         Node cursor = temp;
         temp = temp->next;
         free(cursor);
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions---------
// length()
// Returns the number of elements in this List.
int length(List L){
   if(L == NULL) {
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return L->length;
}

// index()
// If cursor is defined, returns the index of the cursor
// element, otherwise returns -1.
int index(List L){
   if(L == NULL){
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return L->index;
}

// front()
// Returns front element.
// Pre: length() > 0
int front(List L){
   if(L == NULL){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }

   if(L->length < 1){
      printf("List Error: calling front() on empty List reference\n");
      exit(1);
   }
   return L->front->data;
}
//back()
// Returns back element.
// Pre: length() > 0
int back(List L){
   if(L == NULL){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1){
      printf("List Error: calling back() on empty List reference\n");
      exit(1);
   }
   return L->back->data;
}

//get()
// Returns cursor element.
// Pre: length() > 0
int get(List L){
   if(L == NULL){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0){
      printf("List Error: calling get() with an undefined index on List\n");
      exit(1);
   }
   if(L->length < 1){
      printf("List Error: calling get() on empty List reference\n");
      exit(1);
   }
   return L->cursor->data;
}
// equals()
// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B){
   int eq = 1;
   Node temp1 = NULL;
   Node temp2 = NULL;
   if (A == NULL || B == NULL) {
     printf("List Error: calling equals() on NULL List reference\n");
     exit(1);
   }
   temp1 = A->front;
   temp2 = B->front;
   if (length(A) == length(B)) {
     while (eq && temp1 != NULL) {
       eq = (temp1->data == temp2->data);
       temp1 = temp1->next;
       temp2 = temp2->next;
     }
     return eq;
   }
   return 0;
 }

// Manipulation procedures---------------------
// clear()
// Resets this List to its original empty state.
void clear(List L){
   if(L == NULL){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   Node front = L->front;
   while(front != NULL){
      Node reset = front;
      front = front->next;
      free(reset);
   }

   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->index = -1;
   L->length = 0;
}

// moveFront()
// If List is non-empty, places the cursor under the front
// element, otherwise does nothing.
void moveFront(List L){
   if(L == NULL) {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0){
      L->cursor = L->front;
      L->index = 0;
   }
}

// moveback()
// If List is non-empty, places the cursor under the back
// element, otherwise does nothing.
void moveBack(List L){
   if(L == NULL) {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0){
      L->cursor = L->back;
      L->index = L->length - 1;
   }
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step
// toward the front of this List, if cursor is defined and at front,
// cursor becomes undefined, if cursor is undefined does nothing.
void movePrev(List L){
   if(L == NULL) {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->index != 0){
      L->cursor = L->cursor->previous;
      L->index--;
   }
   else if(L->cursor != NULL && L->index == 0){
      L->cursor = NULL;
      L->index = -1;
   }
}

// moveNexT()
// If cursor is defined and not at back, moves cursor one step
// toward the back of this List, if cursor is defined and at back,
// cursor becomes undefined, if cursor is undefined does nothing.
void moveNext(List L){
   if(L == NULL) {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->index != L->length - 1){
      L->cursor = L->cursor->next;
      L->index++;
   }
   else if(L->cursor != NULL && L->index == L->length - 1){
      L->cursor = NULL;
      L->index = -1;
   }
}

// prepend()
// Insert new element into this List. If List is non-empty,
// insertion takes place before the front element.
void prepend(List L, int data){
   if(L == NULL) {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   Node temp = newNode(data, NULL, L->front);
   if(L->front == NULL)
      L->back = temp;
   else{
      L->front->previous = temp;
   }
   L->front = temp;
   L->length++;
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after back element.
void append(List L, int data){
   if(L == NULL) {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   Node temp = newNode(data, L->back, NULL);
   if(L->front == NULL)
      L->front = temp;
   else
      L->back->next = temp;
   L->back = temp;
   L->length++;
}

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int data){
   if(L == NULL) {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: calling insertBefore() on an empty List");
      exit(1);
   }
   if(L->index < 0) {
      printf("List Error: calling insertBefore() with an undefined index on List");
      exit(1);
   }
   Node temp = newNode(data, L->cursor->previous, L->cursor);
   if(L->cursor->previous != NULL)
      L->cursor->previous->next = temp;
   else
      L->front = temp;
   L->cursor->previous = temp;
   L->length++;
}

// Insert new element after cursor.
// Pre: length() > 0, index() >= 0
void insertAfter(List L, int data){
   if(L == NULL) {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1) {
      printf("List Error: calling insertAfter() on an empty List");
      exit(1);
   }
   if(L->index < 0) {
      printf("List Error: calling insertAfter() with an undefined index on List");
      exit(1);
   }
   Node temp = newNode(data, L->cursor, L->cursor->next);
   if(L->cursor->next != NULL)
      L->cursor->next->previous = temp;
   else
      L->back = temp;
   L->cursor->next = temp;
   L->length++;
}

// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L){
   if(L == NULL) {
      printf("List Error: deleteFront() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1){
      printf("List Error: deleteFront() called on an empty List\n");
      exit(1);
   }
   if(L->cursor == L->front){
      L->cursor = NULL;
      L->index = -1;
   }
   Node temp = L->front;
   L->front = L->front->next;
   L->front->previous = NULL;
   L->length--;
   freeNode(&temp);
}

// Deletes the back element.
// Pre: length() > 0
void deleteBack(List L){
   if(L == NULL) {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(1);
   }
   if(L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   }
   if(L->back == L->front)
      L->front = NULL;

   Node temp = L->back;
   if(L->back->previous != NULL)
      L->back = L->back->previous;
   L->back->next = NULL;
   L->length--;
   freeNode(&temp);
}

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L){
   if(L == NULL) {
      printf("List Error: delete() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1){
      printf("List Error: delete() called with an undefined index on List\n");
      exit(1);
   }
   if(L->index < 0){
      printf("List Error: delete() called on empty List");
      exit(1);
   }
   if(L->cursor == L->back){
      deleteBack(L);
   }else if(L->cursor == L->front){
      deleteFront(L);
   }else{
      Node temp = L->cursor;
      L->cursor->previous->next = L->cursor->next;
      L->cursor->next->previous = L->cursor->previous;

      L->cursor = NULL;
      L->index = -1;
      L->length--;
      freeNode(&temp);
   }
}

//Other operations------------------------
// Overrides Object's toString method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
void printList(FILE* out, List L){
   Node temp = L->front;
   int i = 0;
   while(temp != NULL){
      if(i != 0)
         fprintf(out, " %d", temp->data);
      else
         fprintf(out, "%d", temp->data);
      temp = temp->next;
      i++;
   }
}

// Returns a new List representing the same integer sequence as this
// List. The curor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L){
   if (L == NULL){
     printf("List Error: copyList() called on empty list");
     exit(1);
   }
   List copy = newList();
   Node N = L->front;

   while(N != NULL){
      append(copy, N->data);
      N = N->next;
   }
   return copy;
}
