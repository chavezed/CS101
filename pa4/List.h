//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa4
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// List.h
//---------------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_

// Exported type-------------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors -------------------------------------------------------

// newList()
// returns reference to new empty List object.
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL);

// Access functions ---------------------------------------------------------------

// length()
// returns length of L
int length(List L);

// index()
// returns cursor position of L-
int index(List L);

// front()
// returns front element of L
// Pre: length>0
int front(List L);

// back()
// returns back element of L-
// Pre: length > 0
int back(List L);

// get()
// returns cursor data of L
// Pre: length > 0, index >= 0
int get(List L);

// equals()
// returns true(1) if A is identical to B, false(0) otherwise
int equals(List A, List B);

// Manipulation procedures --------------------------------------------------------

// clear()
// Resets the List to its original empty state 
void clear(List L);

// moveFront()
// If List is non=empty, places the cursor under the front element,
// otherwise does nohthing
void moveFront(List L);

// moveBack()
// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing
void moveNext(List L);

// prepend()
// Insert new element into this List. If List is non-empty
// insertion takes place before front element
void prepend(List L, int data);

// append()
// Insert new element into this List. If List is non-empty
// insertion takes place after back element.
void append(List L, int data);

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data);

// insertAfter()
// Insert new element after cursor
// Pre: length > 0, index >=0
void insertAfter(List L, int data);

// deleteFront()
// Deletes front element.
// Pre: length > 0
void deleteFront(List L);

// deleteBack()
// Deletes back element.
// Pre: length > 0
void deleteBack(List L);

// delete()
// Deletes cursor element, making cursor undefined.
// Pre: length > 0, index >=0
void delete(List L);

// Other functions ----------------------------------------------------------------

// printList()
// Prints the List to the file pointed to by out
// formatted as a space-seperated string
void printList(FILE* out, List L);

// copyList()
// Returns the List L representing the same integer sequence as
// this List. The cursor in the new List is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L);

// isEmpty()
// Returns true(1) if the List L is empty, otherwise
// returns false(0) if the List L is not empty
int isEmpty(List L);
#endif