//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa4
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// FindPath.c
//---------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

#define MAX_LEN 150

int main(int argc, char* argv[]) {
	FILE* in;
	FILE* out;
	char line[MAX_LEN];

	//check num of args
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// input/output file validation
	in = fopen(argv[1], "r");
	if (in == NULL) {
		printf("Unable to open file %s for reading.\n", argv[1]);
		exit(1);
	}
	out = fopen(argv[2], "w");
	if (out == NULL) {
		printf("Unable to open file %s for writing.\n", argv[2]);
		exit(1);
	}

	// ----------------
	
	Graph G = NULL;
	List path = newList();
	int pathDone = 0;
	int entryDone = 0;
	int a, b;
	int size;
	if (fgets(line, MAX_LEN, in)) {
		sscanf(line, "%d", &size);
		G = newGraph(size);
	}
	if (G != NULL) {
		while (!entryDone && fgets(line, MAX_LEN, in)) {
			sscanf(line, "%d %d", &a, &b);
			if (a == 0 && b == 0) {
				entryDone = 1;
			}
			else {
				addEdge(G, a, b);
			}
		}

		printGraph(out,G);

		while (!pathDone && fgets(line, MAX_LEN, in)) {
			sscanf(line, "%d %d", &a, &b);
			if (a == 0 && b == 0) {
				pathDone = 1;
			}
			else {
				BFS(G, a);
				getPath(path, G, b);
				fprintf(out, "\nThe distance from %d to %d is ", a, b);
				if (getDist(G, b) == INF) {
					fprintf(out, "infinity\n");
					fprintf(out, "No %d-%d path exists\n", a, b);
				}
				else {
					fprintf(out, "%d\n", getDist(G, b));
					fprintf(out, "A shortest %d-%d path is: ",a,b);
					printList(out, path);
					fprintf(out, "\n");
					clear(path);
				}
			}
		}
	}
	freeList(&path);
	freeGraph(&G);
	fclose(in);
	fclose(out);

	return (0);
}