//---------------------------------------------------------------------------------
// Eduardo Chavez
// echavez9@ucsc.edu
// pa4
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

// getSource()
// returns label of the vertex that was most recently used
// as source for BFS() 
int getSource(Graph G);

// getParent()
// returns parent of vertex u in the Breadth First tree 
// created by BFS(), or NIL if BFS() has not yet been called.
// pre: 1 <= u <= getOrder()
int getParent(Graph G, int u);

// getDist()
// returns the distance from the most recent BFS course to vertex u,
// or INF if BFS() has not yet been called.
// pre: 1 <= u <= getOrder()
int getDist(Graph G, int u);

// getPath()
// appends to the List L the vertices of the shortest path in G from source to u
// or appends to the List the value NIL if no such path exists.
// pre: getSource(G) != NIL
// pre: 1 <= u <= getOrder()
void getPath(List L, Graph G, int u);

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



// BFS()
// runs the BFS algorithm on the Graph G with source s, setting the color,
// distance, parent, and source fields of G accordingly.
// (NOTE: must be called before getPath() )
void BFS(Graph G, int s);

// --------------------------------------------------------------------------------
// Other operations ---------------------------------------------------------------

// printGraph()
// prints the adjacency List represenation of G to the file
// pointed to by out
void printGraph(FILE* out, Graph G);
#endif 