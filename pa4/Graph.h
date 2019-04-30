//Peter Jiang
//pjiang1
//CMPS101 PA4
//Graph.h

#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdio.h>
#include "List.h"

#define NIL -2
#define INF -1

// Exported type
typedef struct GraphObj* Graph;

// Constructor-destructors
Graph newGraph(int n);
void freeGraph(Graph* pG);

// Access functions
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// Manipulation
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// Other operations
void printGraph(FILE *out, Graph G);

#endif
