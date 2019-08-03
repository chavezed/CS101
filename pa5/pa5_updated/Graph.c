//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa5
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
//---------------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"


// structs ------------------------------------------------------------------------

typedef struct GraphObj {
	List* adjList;
	int* color;
	int* parent;
	int* discover;
	int* finish;
	int order;
	int edges;
} GraphObj;


// Constructors-Destructors--------------------------------------------------------

Graph newGraph(int n) {
	Graph N = malloc(sizeof(GraphObj));
	N->adjList = malloc((n + 1) * sizeof(List));
	N->color = malloc((n + 1) * sizeof(int));
	N->parent = malloc((n + 1) * sizeof(int));
	N->discover = malloc((n + 1) * sizeof(int));
	N->finish = malloc((n + 1) * sizeof(int));
	for (int i = 0; i <= n; i++) {
		N->adjList[i] = newList();
	}
	for (int i = 1; i <= n; i++) {
		N->discover[i] = UNDEF;
		N->finish[i] = UNDEF;
		N->parent[i] = NIL;
	}
	N->order = n;
	N->edges = 0;
	return(N);
}

void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		for(int i = 0; i <= getOrder(*pG); i++) {
			freeList(&(*pG)->adjList[i]);
		}
		free((*pG)->adjList);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->discover);
		free((*pG)->finish);
		free(*pG);
		*pG = NULL;
	}
}

// --------------------------------------------------------------------------------
// Access functions ---------------------------------------------------------------

int getOrder(Graph G) {
	return(G->order);
}

int getSize(Graph G) {
	return(G->edges);
}

int getParent(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		printf("Graph error: getParent() called on undefined\n");
		exit(1);
	}
	return(G->parent[u]);
}

int getDiscover(Graph G, int u) {
	if( u < 1 || u > getOrder(G)) {
		printf("Graph error: getDiscover() called on undefined u\n");
		exit(1);
	}
	return (G->discover[u]);
}

int getFinish(Graph G, int u) {
	if( u < 1 || u > getOrder(G)) {
		printf("Graph error: getFinish() called on undefined u\n");
		exit(1);
	}
	return (G->finish[u]);
}

void makeNull(Graph G) {
	for (int i = 1; i <= getOrder(G); i++) {
		clear(G->adjList[i]);
	}
	G->edges = 0;
}

void addEdge(Graph G, int u, int v) {
	if (u < 1 || u > getOrder(G)) {
		printf("Graph error: addEdge() called on out of bound vertex\n");
		exit(1);
	}
	if (v < 1 || v > getOrder(G)) {
		printf("Graph error: addEdge() called on out of bound vertex\n");
		exit(1);
	}

	int temp;
	int found1 = 0;
	int found2 = 0;
	int found3 = 0;
	int found4 = 0;
	for (moveFront(G->adjList[u]); index(G->adjList[u]) != -1; moveNext(G->adjList[u])) {
		temp = get(G->adjList[u]);
		if (temp == v) {
			moveBack(G->adjList[u]);
			found1 = 1;
		}
		else if (v < temp) {
			insertBefore(G->adjList[u], v);
			moveBack(G->adjList[u]);
			found1 = 1;
			found3 = 1;
		}
		else {}
	}
	if (!found1) {
		append(G->adjList[u], v);
		found1 = 1;
		found3 = 1;
	}
	//----------
	for (moveFront(G->adjList[v]); index(G->adjList[v]) != -1; moveNext(G->adjList[v])) {
		temp = get(G->adjList[v]);
		if (temp == u) {
			moveBack(G->adjList[v]);
			found2 = 1;
		}
		else if (u < temp) {
			insertBefore(G->adjList[v], u);
			moveBack(G->adjList[v]);
			found2 = 1;
			found4 = 1;
		}
		else {}
	}
	if (!found2) {
		append(G->adjList[v], u);
		found2 = 1;
		found4 = 1;
	}

	if (found3 || found4) {
		G->edges++;
	}
}

void addArc(Graph G, int u, int v) {
	if (u < 1 || u > getOrder(G)) {
		printf("Graph error: addArc() called on out of bound vertex u\n");
		exit(1);
	}
	if (v < 1 || v > getOrder(G)) {
		printf("Graph error: addArc() called on out of bound vertex v\n");
		exit(1);
	}

	int temp;
	int found = 0;
	for (moveFront(G->adjList[u]); index(G->adjList[u]) != -1; moveNext(G->adjList[u])) {
		temp = get(G->adjList[u]);
		if (temp == v) {
			moveBack(G->adjList[u]);
			found = 1;
		}
		else if (v < temp) {
			insertBefore(G->adjList[u], v);
			moveBack(G->adjList[u]);
			found = 1;
			G->edges++;
		}
		else {}
	}
	if (!found) {
		append(G->adjList[u], v);
		G->edges++;
	}
}

void DFS(Graph G, List S) {
	if(length(S) != getOrder(G)) {
		printf("Graph error: length of S != vertices of G\n");
		exit(1);
	}
	for(int i = 1; i <= getOrder(G); i++) {
		G->color[i] = WHT;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->finish[i] = UNDEF;
	}
	int time = 0;
	List stack = newList();
	for(moveFront(S); index(S)!=-1; moveNext(S)) {
		if(G->color[get(S)] == WHT) {
			visit(G, stack, get(S), &time);
		}
	}
	
	clear(S);
	for(moveFront(stack); index(stack)!=-1; moveNext(stack)) {
		append(S, get(stack));
	}
	freeList(&stack);
}

void visit(Graph G, List S, int x, int *time) {
	G->color[x] = GRY;
	G->discover[x] = ++(*time);
	List y = G->adjList[x];
	for(moveFront(y); index(y)!=-1; moveNext(y) ) {
		if(G->color[ get(y) ] == WHT ) {
			G->parent[ get(y) ] = x;
			visit(G, S, get(y), time);
		}
	}
	G->color[x] = BLK;
	G->finish[x] = ++(*time);
	prepend(S, x);
}

Graph transpose(Graph G) {
	Graph N = newGraph(getOrder(G));
	List temp;
	for(int i = 0; i <= getOrder(G); i++) {
		temp = G->adjList[i];
		for(moveFront(temp); index(temp)!=-1; moveNext(temp) ) {
			addArc(N, get(temp), i);
		}
	}
	return (N);
}

Graph copyGraph(Graph G) {
	Graph N = newGraph(getOrder(G));
	List temp;
	for(int i = 1; i <= getOrder(G); i++) {
		temp = G->adjList[i];
		for(moveFront(temp); index(temp)!=-1; moveNext(temp) ) {
			addArc(N, i, get(temp) );
		}
	}
	return (N);	
}

void printGraph(FILE *out, Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling printGraph() on NULL Graph reference.\n");
		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out, "%d: ", i);
		printList(out, G->adjList[i]);
		fprintf(out, "\n");
	}
}