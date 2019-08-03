//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa4
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//---------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

// structs ------------------------------------------------------------------------

//private NodeObj type
typedef struct NodeObj {
	int data;
	struct NodeObj* next;
	struct NodeObj* prev;
} NodeObj;

//private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
} ListObj;

// Constructors-Destructors -------------------------------------------------------

// newNode()
// Returns reference to the new Node object. Initializes next and data fields.
// Private
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->next = NULL;
	N->prev = NULL;
	return(N);
}

//freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL
// Private
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// returns reference to new empty List object.
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = L->back = L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		clear(*pL);
		free(*pL);
		*pL = NULL;
	}
}

// Access functions ---------------------------------------------------------------

// length()
// returns length of L
int length(List L) {
	if (L == NULL) {
		printf("List error: calling length() on NULL List reference\n");
		exit(1);
	}
	return (L->length);
}

// index()
// returns cursor position of L
int index(List L) {
	return (L->index);
}

// front()
// returns front element of L
// Pre: length>0
int front(List L) {
	if (L == NULL) {
		printf("List error: calling front() on empty List\n");
		exit(1);
	}
	return(L->front->data);
}

// back()
// returns back element of L-
// Pre: length > 0
int back(List L) {
	if (L == NULL) {
		printf("List error: calling back() on empty List\n");
		exit(1);
	}
	return (L->back->data);
}

// get()
// returns cursor data of L
// Pre: length > 0, index >= 0
int get(List L) {
	if (L == NULL) {
		printf("List error: calling get on empty List\n");
		exit(1);
	}
	if (L->index < 0) {
		printf("List error: calling get on out of bounds index.\n");
		exit(1);
	}
	return (L->cursor->data);
}

// equals()
// returns true(1) if A is identical to B, false(0) otherwise
int equals(List A, List B) {
	int eq = 0;
	Node aN = NULL;
	Node bN = NULL;
	aN = A->front;
	bN = B->front;
	if (aN == NULL || bN == NULL) {
		printf("List error: calling equals() on NULL List reference\n");
		exit(1);
	}
	eq = (A->length == B->length);
	while (eq && aN != NULL && bN != NULL) {
		eq = (aN->data == bN->data);
		aN = aN->next;
		bN = bN->next;
	}
	return eq;
}

// Manipulation procedures --------------------------------------------------------

// clear()
// Resets the List to its original empty state
void clear(List L) {
	if (L->length > 0) {
		while (L->back->prev != NULL) {
			L->back = L->back->prev;
			freeNode(&L->back->next);
		}
		freeNode(&L->back);
		L->front = NULL;
		L->back = NULL;
		L->cursor = NULL;
		L->index = -1;
		L->length = 0;
	}
}

// moveFront()
// If List is non-empty, places the cursor under the front element,
// otherwise does nohthing
void moveFront(List L) {
	if (L->length>0) {
		L->cursor = L->front;
		L->index = 0;
	}
}

// moveBack()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveBack(List L) {
	if (L->length>0) {
		L->cursor = L->back;
		L->index = L->length - 1;
	}
}

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing
void movePrev(List L) {
	if (L->cursor->prev != NULL) {
		L->cursor = L->cursor->prev;
		L->index--;
	}
	else if (L->cursor->prev == NULL) {
		L->cursor = NULL;
		L->index = -1;
	}
	else {}
}

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing
void moveNext(List L) {
	if (L->cursor->next != NULL) {
		L->cursor = L->cursor->next;
		L->index++;
	}
	else if (L->cursor->next == NULL) {
		L->cursor = NULL;
		L->index = -1;
	}
	else {}
}

// prepend()
// Insert new element into this List. If List is non-empty
// insertion takes place before front element
void prepend(List L, int data) {
	Node N = newNode(data);
	if (L->length == 0) {
		L->front = N;
		L->back = N;
	}
	else {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	L->length++;
}

// append()
// Insert new element into this List. If List is non-empty
// insertion takes place after back element.
void append(List L, int data) {
	Node N = newNode(data);
	if (L->length == 0) {
		L->front = N;
		L->back = N;
	}
	else {
		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->length++;
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data) {
	if (L->length == 0) {
		printf("List error: insertBefore() called on empty List.\n");
		exit(1);
	}
	if (L->index < 0) {
		printf("List error: insertBefore called on undefined index.\n");
		exit(1);
	}
	Node N = newNode(data);
	if (L->cursor->prev == NULL) {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}
	else {
		L->cursor->prev->next = N;
		N->prev = L->cursor->prev;
		L->cursor->prev = N;
		N->next = L->cursor;
	}
	L->length++;
	L->index++;
}

// insertAfter()
// Insert new element after cursor
// Pre: length > 0, index >=0
void insertAfter(List L, int data) {
	if (L->length == 0) {
		printf("List error: insertAfter() called on empty List.\n");
		exit(1);
	}
	if (L->index < 0) {
		printf("List error: insertAfter() called on undefined index.\n");
		exit(1);
	}
	Node N = newNode(data);
	if (L->cursor->next == NULL) {
		L->back->next = N;
		N->prev = L->back;
		L->back = N;
	}
	else {
		L->cursor->next->prev = N;
		N->next = L->cursor->next;
		N->prev = L->cursor;
		L->cursor->next = N;
	}
	L->length++;
}

// deleteFront()
// Deletes front element.
// Pre: length > 0
void deleteFront(List L) {
	if (L->length == 0) {
		printf("List error: deleteFront() called on empty List.\n");
		exit(1);
	}
	if (L->length == 1) {
		freeNode(&L->front);
		L->front = NULL;
		L->back = NULL;
		L->index = -1;
	}
	else {
		L->front = L->front->next;
		freeNode(&L->front->prev);
		L->index--;
	}
	L->length--;
}

// deleteBack()
// Deletes back element.
// Pre: length > 0
void deleteBack(List L) {
	if (L->length == 0) {
		printf("List error: deleteBack() called on empty List.\n");
		exit(1);
	}
	if (L->length == 1) {
		freeNode(&L->back);
		L->front = NULL;
		L->back = NULL;
		L->index = -1;
	}
	else {
		L->back = L->back->prev;
		freeNode(&L->back->next);
	}
	L->length--;
}

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length > 0, index >=0
void delete(List L) {
	if (L->length == 0) {
		printf("List error: delete() called on empty List.\n");
		exit(1);
	}
	if (L->index < 0) {
		printf("List error: delete() called on undefined index.\n");
		exit(1);
	}
	if (L->cursor == L->front) {
		deleteFront(L);
	}
	else if (L->cursor == L->back) {
		deleteBack(L);
	}
	else {
		Node toDel = NULL;
		toDel = L->cursor;
		L->cursor->next->prev = L->cursor->prev;
		L->cursor->prev->next = L->cursor->next;
		L->length--;
		freeNode(&toDel);
	}
	L->cursor = NULL;
	L->index = -1;
}

// Other function -----------------------------------------------------------------

// printList()
// Prints the List to the file pointed to by out
// formatted as a space-seperated string
void printList(FILE* out, List L) {
	Node N = NULL;
	if (L == NULL) {
		printf("List error: calling printList() on NULL List reference.\n");
		exit(1);
	}
	for (N = L->front; N != NULL; N = N->next) {
		fprintf(out, "%d ", N->data);
	}
}

// copyList()
// Returns the List L representing the same integer sequence as
// this List. The cursor in the new List is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L) {
	List toRet = newList();
	Node N = L->front;
	while (N != NULL) {
		append(toRet, N->data);
		N = N->next;
	}
	return toRet;
}

// isEmpty()
// Returns true(1) if the List L is empty, otherwise
// returns false(0) if the List L is not empty
int isEmpty(List L) {
	if (L->length == 0)
		return 1;
	return 0;
}