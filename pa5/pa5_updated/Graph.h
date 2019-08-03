//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa5
//---------------------------------------------------------------------------------

//---------------------------------------------------------------------------------
// Graph.h
//---------------------------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include"List.h"

// consts -------------------------------------------------------------------------
#define NIL -2
#define INF -3
#define WHT -4
#define GRY -5
#define BLK -6
#define UNDEF -7

// Exported Type
typedef struct GraphObj* Graph;

// Constructors-Destructors -------------------------------------------------------

// Graph()
// returns reference to new Graph
// with n vertices and no edges
Graph newGraph(int n); 

// freeGraph()
// Frees all heap memory associated with Graph *pG 
// and sets *pG to NULL
void freeGraph(Graph *pG);

// --------------------------------------------------------------------------------
// Access functions ---------------------------------------------------------------

// getOrder()
// returns number of vertices in Graph G
int getOrder(Graph G);

// getSize()
// returns number of edges in Graph G
int getSize(Graph G);

// getParent()
// returns parent of vertex u in the Breadth First tree 
// created by BFS(), or NIL if BFS() has not yet been called.
// pre: 1 <= u <= getOrder()
int getParent(Graph G, int u);

// getDiscover()
// returns the discover time of vertex u
// if DFS() is not called yet, returns UNDEF
// pre: 1 <= u <= getOrder()
int getDiscover(Graph G, int u);

// getFinish()
// returns the finish time of vertex u
// if DFS() is not called yet, returns UNDEF
// pre: 1 <= u <= getOrder()
int getFinish(Graph G, int u);

// --------------------------------------------------------------------------------
// Manipulation procedures --------------------------------------------------------

// makeNull()
// deletes all edges of G, restoring it to its orginal (no edge) state
void makeNull(Graph G);

// addEdge()
// inserts a new edge joining u to v
// (i.e. U is added to the adjacency List of v,
//  and v to the adjacency List of u)
void addEdge(Graph G, int u, int v);


// addArc()
// inserts a new directed edge from u to v,
// (i.e. v is added to the adjacency List of u, but
//  not u to the adjacency List of v )
void addArc(Graph G, int u, int v);

// DFS()
// runs the DFS algorithm on the Graph G setting the color, discover and finish times
// fields of G accordingly
// when recursive portion of DFS is done, arranges finish times in decreasing order
// on the List S
// pre: length(S) == getOrder(G)
void DFS(Graph G, List S);

// visit()
// recursive helper function for DFS()
// sets the discover and finish times of all vertices in Graph G
void visit(Graph G, List S, int x, int *time);

// --------------------------------------------------------------------------------
// Other operations ---------------------------------------------------------------

// transpose()
// reverse directions on all edges of G
Graph transpose(Graph G);

// copyGraph()
// returns a copy of Graph G
Graph copyGraph(Graph G);

// printGraph()
// prints the adjacency List represenation of G to the file
// pointed to by out
void printGraph(FILE* out, Graph G);
#endif 