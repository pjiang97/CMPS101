/*Peter Jiang
*4/24/2018
*pjiang1
*pa2
*/
#include<stdio.h>
#include<stdlib.h>
#include "List.h"

//Structs ==================

typedef struct NodeObj {
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

//private Node type
typedef NodeObj* Node;

//private ListObj tyoe
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

//Constructors Destructors ==============

//newNode()
//Retursn reference to Node object. Initializes next and data fields.
//Private.
Node newNode(int data){
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

//freeNode()
//Frees heap memory pointed to by *pN, sets *pN to NULL.
//Private
void freeNode(Node* pN){
	if(pN != NULL && *pN != NULL){
		free(*pN);
		*pN = NULL;
	}
}

//List newList()
//returns refernce to new empty List Object.
List newList(void){
	List L;
	L = malloc(sizeof(ListObj));
	L->front =L->back = L->cursor = NULL;
	L->index = -1;
	L->length = 0;
	return(L);
}


int isEmpty(List L){
	if( L == NULL){
		printf("List error: isEmpty() called on NULL list reference\n");
		exit(1);
	}
	return(L->length==0);
}

void freeList(List* pL){
	if(pL !=NULL && *pL !=NULL) {
		while( !isEmpty(*pL) ) {
			deleteFront(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}
//Access functions ==========================================


//length()
//Retursn the Length of L
int length(List L){
	if(L == NULL){
		printf("List Error: calling length() on NULL List reference\n");
		exit(1);
	}
	return(L->length);
}

//index()
//Returns the index
int index(List L){
	if(L == NULL){
		printf("List Error: calling index() on NULL List reference\n");
		exit(1);
	}
	return(L->index);
}

//front()
//returns the value at the front of L
//pre: !isEmpty(L);
int front(List L){
	if(L == NULL){
		printf("List Error: calling front() on NULL List Reference\n");
		exit(1);
	}
	if(isEmpty(L) ){
		printf("List Error: calling front() on an empty List\n");
		exit(1);
	}

	return(L->front->data);
}

//back()
//returns the value at the back of L
//Pre: !isEmpty(L);
int back(List L){

	if(L == NULL){
		printf("List Error: calling back on empty List reference\n");
		exit(1);
	}
	if( isEmpty(L) ){
		printf("List Error: calling back() on an empty List\n");
		exit(1);
	}
	return(L->back->data);
}

//get()
//returns value at cursor
//pre: !isEmpty(L);
int get(List L){
	if(L == NULL){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	if(isEmpty(L)){
		printf("List Error: calling get() on NULL List reference\n");
		exit(1);
	}
	return(L->cursor->data);
}

//equals()
//returns true(1) if A is identical to B, false (0) otherwise
//inspired off of Queue.c
int equals(List A, List B) {
   if(A == NULL || B == NULL) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   if(A->length != B->length) {
      return 0;
   }
   Node cfront = B->front;
   Node tmp = A->front;
   while(cfront->next != NULL && tmp->next != NULL) {
      if(cfront->data != tmp->data)
         return 0;
      cfront = cfront->next;
      tmp = tmp->next;
   }
   return 1;
}

//Manipultation procedure ==================

//clear()
//emptys entire List to make it empty
void clear(List L) {
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;

}

// If List is non-empty, places the cursor under the front
// element, otherwise does nothing.
void moveFront(List L) {
	if(L->length > 0){
		L->cursor = L->front;
		L->index = 0;
	}
}

// If List is non-empty, places the cursor under the back
// element, otherwise does nothing.
void moveBack(List L){
	if(L->length > 0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

// If cursor is defined and not at front, moves cursor one step
// toward the front of this List, if cursor is defined and at front,
// cursor becomes undefined, if cursor is undefined does nothing.
void movePrev(List L) {
	if(L->cursor != NULL && L->index != 0) {
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else if(L->cursor != NULL && L->index == 0) {
		L->cursor = NULL;
		L->index = -1;
	}
}

// If cursor is defined and not at back, moves cursor one step
// toward the back of this List, if cursor is defined and at back,
// cursor becomes undefined, if cursor is undefined does nothing.
void moveNext(List L) {
	if(L->cursor != NULL && L->index != L->length - 1) {
		L->cursor = L->cursor->next;
		L->index++;
	}
	else if(L->cursor != NULL && L->index == L->length - 1) {
		L->cursor = NULL;
		L->index = -1;
	}
}

//prepend()
//insert new element into this List. If List in non-empty.
//insertion takes place before fornt elemnt
void prepend(List L,int data){
	Node temp = newNode(data);

	if(L->front == NULL){
		L->front = L->back = temp;
	}
	else{
		L->front->prev = temp;
		temp->next = L->front;
		L->front = temp;
		L->index++;
	}
	L->length++;
}


//append()
//insert new elment into this List. If list in no-empty,
//insertion takes place after back element
void append(List L, int data){
	Node temp = newNode(data);
	if(L->front == NULL){
		L->front = L->back = temp;
	}
	else {
		L->back->next = temp;
		temp->prev = L->back;
		L->back = temp;
	}
	L->length++;
}

//insertBefore()
//Inserts new element before cursor element in this List.
//Pre: length()>0, index() >= 0
void insertBefore(List L, int data){
	Node temp = newNode(data);

	if( L == NULL ){
		printf("List error: insertBefore() called on empty List reference\n");
		exit(1);
	}else {
		temp->next = L->cursor;

		if(L->cursor->prev != NULL){
			temp->prev = L->cursor->prev;
			L->cursor->prev->next = temp;
		}
		L->cursor->prev = temp;
		if(temp->prev == NULL){
			L->front = temp;
		}
		L->index++;
		L->length++;
	}
}

//insertAfter()
//inserts new elemeemt after cursor element in this List.
//Pre: length()>0, index>=0
void insertAfter(List L, int data) {
	if (L == NULL) {
		printf("List Error: insertAfter() called on NULL List reference\n");
		exit (1);
	} if (L->length <= 0) {
		printf("List Error: insertAfter() called on empty List\n");
		exit (1);
	} if (L->cursor < 0) {
		printf("List Error: insertAfter() called on list w/ undefined cursor\n");
		exit (1);
	} else if (L->cursor == L->back) {
		append(L, data);
	} else {
		// Link the new node
		Node N = newNode(data);
		N->prev = L->cursor;
		N->next = L->cursor->next;
		// Link the previous node
		L->cursor->next->prev = N;
		// Link the next node
		L->cursor->next = N;
		// Update the length
		L->length++;
	}
}

//deleteFront(){
//pre: length() >0
//based off of Queue.c method Dequeue
void deleteFront(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling Delete front() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling Delete front on an empty List\n");
      exit(1);
   }
   if(L->index == 0){
      L->index = -1;
      L->cursor = NULL;
   }
   N = L->front;
   if( length(L) > 1 ) { L->front = L->front->next; }

   L->length--;
   //N = NULL;
   freeNode(&N);
}

//DeleteBack
//deletes element at the back of the list
void deleteBack(List L){
   Node N = NULL;

   if( L==NULL ){
      printf("List Error: calling DeList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling DeList on an empty List\n");
      exit(1);
   }
   N = L->back;
   if( L->length > 1 ) {L->back = L->back->prev; }
   else {
      L->front = L->back = NULL;
      //freeNode(L->front);
   }
   L->length--;
   N = NULL;
   freeNode(&N);
}

//delete
//delete element at cursor
void delete(List L){
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling DeList() on NULL List reference\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling DeList on an empty List\n");
      exit(1);
   }else if(index(L) == -1){
      printf("List Error: calling delete on a null cursor");
      exit(1);
   }else if(index(L) >= 0){
      if(L->cursor->prev == NULL){
         L->front = L->cursor->next;
      }
      else if(L->cursor->next == NULL){
         L->back = L->cursor->prev;
      }
      N = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      L->cursor = NULL;
      L->length--;
      L->index = -1;
      freeNode(&N);
   }


}

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in L on a single line to stdout.
void printList(FILE* out, List L) {
	Node temp = L->front;
	while(temp != NULL) {
		fprintf(out, "%d ", temp->data);
		temp = temp->next;
	}
}

// Returns a new List representing the same integer sequence as this
// List. The curor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {
	List c = newList();
	Node temp = L->front;
	while(temp != NULL) {
		append(c, temp->data);
		temp = temp->next;
	}
	return c;
}
