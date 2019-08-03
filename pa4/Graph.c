//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa4
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
	int* distance;
	int order;
	int edges;
	int source;

} GraphObj;


// Constructors-Destructors--------------------------------------------------------

Graph newGraph(int n) {
	Graph N = malloc(sizeof(GraphObj));
	N->adjList = malloc((n + 1) * sizeof(List));
	N->color = malloc((n + 1) * sizeof(int));
	N->parent = malloc((n + 1) * sizeof(int));
	N->distance = malloc((n + 1) * sizeof(int));
	for (int i = 0; i <= n; i++) {
		N->adjList[i] = newList();
	}
	N->order = n;
	N->edges = 0;
	N->source = NIL;
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
		free((*pG)->distance);
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

int getSource(Graph G) {
	return(G->source);
}

int getParent(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		printf("Graph error: getParent() called on undefined\n");
		exit(1);
	}
	if (getSource(G) == NIL) { //BFS not called yet
		return NIL;
	}
	return(G->parent[u]);
}

int getDist(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		printf("Graph error: getDist() called on undefined u\n");
		exit(1);
	}
	if (getSource(G) == NIL) {
		return INF;
	}
	return (G->distance[u]);
}

void getPath(List L, Graph G, int u) {
	if (getSource(G) == NIL) {
		printf("Graph error: getPath() called before BFS()\n");
		exit(1);
	}
	if (u < 1 || u > getOrder(G)) {
		printf("Graph error: getPath() called on undefined u\n");
		exit(1);
	}

	if (getSource(G) == u) {
		prepend(L, u);
	}
	else {
		int temp = G->parent[u];
		prepend(L, u);
		while (temp != NIL) {
			prepend(L, temp);
			temp = G->parent[temp];
		}
	}
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

void BFS(Graph G, int s) {
	for (int i = 1; i <= getOrder(G); i++) {
		if (i != s) {
			G->color[i] = WHT;
			G->distance[i] = INF;
			G->parent[i] = NIL;
		}
	}
	G->color[s] = GRY;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	G->source = s;
	List Q = newList();
	prepend(Q, s); //Enqueue
	int x, y;
	while (length(Q) > 0) {
		x = front(Q);
		deleteFront(Q); // Dequeue (front + deleteFront)
		for (moveFront(G->adjList[x]); index(G->adjList[x]) != -1; moveNext(G->adjList[x])) {
			y = get(G->adjList[x]);
			if (G->color[y] == WHT) {
				G->color[y] = GRY;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(Q, y);
			}
		}
		G->color[x] = BLK;
	}
	freeList(&Q);
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