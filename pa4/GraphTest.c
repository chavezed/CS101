//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa4
//---------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"


int main(int argc, char* argv[]) {

	Graph G1 = newGraph(15);
	List path = newList();
	FILE* out = stdout;
	for (int i = 1; i <= 15; i++) {
		addEdge(G1, i, (i % 15) + 1);
	}
	fprintf(out, "Undirected Graph\n");
	printGraph(out, G1);
	
	BFS(G1, 4);
	getPath(path, G1, 13);
	fprintf(out, "\nThe distance from %d to %d is ", 4, 13);
	if (getDist(G1, 13) == INF) {
		fprintf(out, "infinity\n");
		fprintf(out, "No %d-%d path exists\n", 4, 13);
	}
	else {
		fprintf(out, "%d\n", getDist(G1, 13));
		fprintf(out, "A shortest %d-%d path is: ", 4, 13);
		printList(out, path);
		fprintf(out, "\n");
		clear(path);
	}
	fprintf(out, "\nOrder: %d", getOrder(G1));
	fprintf(out, "\nSize: %d", getSize(G1));
	fprintf(out, "\nSource: %d", getSource(G1));
	fprintf(out, "\nParent of 13: %d\n", getParent(G1, 13));

	makeNull(G1);
	printGraph(out, G1);
	fprintf(out, "\nOrder: %d", getOrder(G1));
	fprintf(out, "\nSize: %d", getSize(G1));

	//--------------------------------------------------------------------------------
	// Digraph
	Graph G2 = newGraph(15);
	for (int i = 1; i <= 15; i++) {
		addArc(G2, i, (i % 15) + 1);
	}
	fprintf(out, "\n\nDirected Graph\n");
	printGraph(out, G2);

	BFS(G2, 4);
	getPath(path, G2, 13);
	fprintf(out, "\nThe distance from %d to %d is ", 4, 13);
	if (getDist(G2, 13) == INF) {
		fprintf(out, "infinity\n");
		fprintf(out, "No %d-%d path exists\n", 4, 13);
	}
	else {
		fprintf(out, "%d\n", getDist(G2, 13));
		fprintf(out, "A shortest %d-%d path is: ", 4, 13);
		printList(out, path);
		fprintf(out, "\n");
		clear(path);
	}
	fprintf(out, "\nOrder: %d", getOrder(G2));
	fprintf(out, "\nSize: %d", getSize(G2));
	fprintf(out, "\nSource: %d", getSource(G2));
	fprintf(out, "\nParent of 13: %d\n", getParent(G2, 13));

	makeNull(G2);
	printGraph(out, G2);
	fprintf(out, "\nOrder: %d", getOrder(G2));
	fprintf(out, "\nSize: %d\n", getSize(G2));

	freeList(&path);
	freeGraph(&G1);
	freeGraph(&G2);

	return (0);
}