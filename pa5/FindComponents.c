//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa5
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// FindComponents.c
// Determines strong components of G
// by using DFS on G and transpose(G)
//---------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

#define MAX_LEN 150

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	char line[MAX_LEN];
	
	// check num of args
	if(argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}
	
	// input/output file validation
	in = fopen(argv[1], "r");
	if( in == NULL) {
		printf("Unable to open file %s for reading.\n", argv[1]);
		exit(1);
	}
	out = fopen(argv[2], "w");
	if( out == NULL) {
		printf("Unable to open file %s for writing.\n", argv[2]);
		exit(1);
	}
	
	// -------------
	
	Graph G = NULL;
	List S = newList();
	int size;
	int a,b;
	int entryDone = 0;
	
	if(fgets(line,MAX_LEN, in)) {
		sscanf(line, "%d", &size);
		G = newGraph(size);
	}
	
	if(G != NULL) {
		while (!entryDone && fgets(line, MAX_LEN, in)) {
			sscanf(line, "%d %d", &a, &b);
			if (a == 0 && b == 0) {
				entryDone = 1;
			}
			else {
				addArc(G, a, b);
			}
		}
		
		
		for(int i = 1; i <= size; i++) {
			append(S, i);
		}
		
		DFS(G, S);
		Graph tG = transpose(G);
		DFS(tG, S);
		
		fprintf(out, "Adjacency list represenation of G:\n");
		printGraph(out, G);
		fprintf(out, "\n");
		int sccCount = 0;
		for(int i = 1; i <= getOrder(tG); i++) {
			if( getParent(tG, i) == NIL ) {
				sccCount++;
			}
		}
		List sccList = newList();
		moveBack(S);
		fprintf(out, "G contains %d strongly connected components:\n", sccCount);
		for(int i = 1; i <= sccCount; i++) {
			while(getParent(tG, get(S)) != NIL && index(S) != -1) {
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
		freeList(&sccList);
		freeGraph(&tG);
	}
	
	freeList(&S);
	freeGraph(&G);
	fclose(in);
	fclose(out);
	
	return (0);
}