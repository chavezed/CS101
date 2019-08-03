//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa5
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// GraphTest.c
// Test for Graph Module
//---------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]) {
	int n = 8;
	Graph A = newGraph(n);
	Graph B = NULL;
	Graph C = NULL;
	List S = newList();
	FILE* out = stdout;
	
	// add directed edges
	addArc(A, 1,2);
	addArc(A, 1,5);
	addArc(A, 2,5);
	addArc(A, 2,6);
	addArc(A, 3,2);
	addArc(A, 3,4);
	addArc(A, 3,6);
	addArc(A, 3,7);
	addArc(A, 3,8);
	addArc(A, 6,5);
	addArc(A, 6,7);
	addArc(A, 8,4);
	addArc(A, 8,7);
	
	// print Graph
	fprintf(out, "Adjacency List representation of A:\n");
	printGraph(out, A);
	fprintf(out, "\n\n");
	
	// transpose
	B = transpose(A);
	fprintf(out, "Adjacency List representation of A transpose:\n");
	printGraph(out, B);
	fprintf(out, "\n\n");
	
	// copy
	C = copyGraph(A);
	fprintf(out, "Adjacency List representation of A copy:\n");
	printGraph(out, C);
	fprintf(out, "\n\n");
	
	// makeNull
	makeNull(C);
	fprintf(out, "Adjacency List representation of A copy after makeNull:\n");
	printGraph(out, C);
	fprintf(out, "\n\n");
	
	// initialize Stack S (using List ADT to implement stack)
	// for initial call to DFS()
	for(int i = 1; i <= n; i++) {
		append(S, i);
	}
	fprintf(out, "Stack S before DFS():\n");
	printList(out, S);
	fprintf(out, "\n\n");
	
	// run DFS on A 
	DFS(A, S);
	fprintf(out, "After running DFS() on Graph A (note: NIL = -2):\n");
	fprintf(out, "x:  d  f  p\n");
	for(int i=1; i<=n; i++){
		fprintf(out, "%d: %2d %2d %2d\n", i, getDiscover(A, i), getFinish(A, i), getParent(A, i));
	}
	fprintf(out, "Stack S after DFS() on Graph A: \n");
	printList(out, S);
	fprintf(out, "\n\n");
	
	// run DFS on B (A transpose)
	DFS(B, S);
	fprintf(out, "After running DFS() on Graph B (note: NIL = -2):\n");
	fprintf(out, "x:  d  f  p\n");
	for(int i=1; i<=n; i++){
		fprintf(out, "%d: %2d %2d %2d\n", i, getDiscover(B, i), getFinish(B, i), getParent(B, i));
	}
	fprintf(out, "Stack S after DFS() on Graph A:\n");
	printList(out, S);
	fprintf(out, "\n\n");
	
	// find strong components
	List sccList = newList();
	int sccCount = 0;
		for(int i = 1; i <= getOrder(B); i++) {
			if( getParent(B, i) == NIL ) {
				sccCount++;
			}
		}
	moveBack(S);
	fprintf(out, "G contains %d strongly connected components:\n", sccCount);
	for(int i = 1; i <= sccCount; i++) {
		while(getParent(B, get(S)) != NIL && index(S) != -1) {
			prepend(sccList, get(S));
			movePrev(S);
		}
		if(index(S) != -1) {
			prepend(sccList, get(S));
			movePrev(S);
		}
		fprintf(out, "Component %d: ", i);
		printList(out, sccList);
		fprintf(out, "\n");
		clear(sccList);
	}	
	
	
	// free memory
	freeList(&sccList);
	freeList(&S);
	freeGraph(&A);
	freeGraph(&B);
	freeGraph(&C);
	
	return (0);
}