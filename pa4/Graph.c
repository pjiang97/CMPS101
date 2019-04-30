//Peter Jiang
//pjiang1
//CMPS 101 PA4
//Graph.c

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

//struct
typedef struct GraphObj{
	List *adj;
	int *color;
	int *parent;
	int *distance;
	int source;
	int size;
	int order;
} GraphObj;

// Constructors-Deconstructors
// Graph Constructor
Graph newGraph(int n){
	Graph G = malloc(sizeof(struct GraphObj));
	G->adj = calloc(n + 1, sizeof(List));
	G->color = calloc(n + 1, sizeof(int));
	G->parent = calloc(n + 1, sizeof(int));
	G->distance = calloc(n + 1, sizeof(int));
	G->source = NIL;
	G->order = n;
	G->size = 0;

	for(int i = 0; i < (n + 1); i++){
		G->adj[i] = newList();
		G->color[i] = WHITE;
		G->parent[i] =  NIL;
		G->distance[i] = INF;
	}
	return G;
}

// Graph Deconstructor
void freeGraph(Graph *pG){
	Graph graph = *pG;
	for(int i = 0; i < (graph->order + 1); i++){
		freeList(&(graph->adj[i]));
	}
	free(graph->adj);
	free(graph->parent);
	free(graph->color);
	free(graph->distance);
	free(*pG);
	*pG = NULL;
}

// Access Functions
// getOrder(): return the order (vertices) of the graph
int getOrder(Graph G){
	return G->order;
}

// getSize(): return the size (edges) of the graph
int getSize(Graph G){
	return G->size;
}

// getSource(): returns the source vertex
// most recently used in function BFS(),
// or NIL if BFS() has not yet been called
int getSource(Graph G){
	return G->source;
}

// getParent() : return the parent of vertex u in
// the Breadth-First tree created by BFS(), or
// NIL if either u has no parent or BFS() has not yet been called
// Pre: 1<=u<=getOrder(G)
int getParent(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getParent() with vertex out of boudns\n");
		exit(1);
	}
	return G->parent[u];
}

// getdistance(): returns the distanceance from the most recent
// BFS source to vertex u, or INF if either u is not reachable
// from the source or if BFS() has not yet been called
// Pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u){
	if(u < 1 || u > getOrder(G)){
		printf("GRaph Error: calling getdistance() with vertex out of bounds\n");
		exit(1);
	}
	if(getSource(G) == NIL){
		return INF;
	}
	return G->distance[u];
}

// getPath(): appends to the List L the vertices of a
// shortest path in G from source to u, or appends
// to L the value NIL if no such path exists
// Pre: getSource(G)!=NIL, 1<=u<=getOrder(G)
void getPath(List L, Graph G, int u){
	if(getSource(G) == NIL){
		printf("Graph Error: calling getPath() with NULL source\n");
	}
	if(u < 1 || u > getOrder(G)){
		printf("Graph Error: calling getPath() with vertex out of boudns\n");
		exit(1);
	}
	int S = G->source;
	if (u == S){
		append(L, u);
	}else if (G->parent[u] == NIL){
		append(L, NIL);
	}else{
		getPath(L, G, G->parent[u]);
		append(L, u);
	}
}

// Manipulation procedures
// makeNull(): deletes all edges of G,
// restoring it to its original (no edge) state

void makeNull(Graph G) {
	for(int i = 0; i < G->order + 1; i++){
		clear(G->adj[i]);
		G->color[i] = WHITE;
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
  G->size = 0;
}

// addEdge(): inserts a new edge joining
// u to v and v to u (bidirectional)
// Preconditions: 1<=u<=getOrder(G), 1<=v<=getOrder(G)

void addEdge(Graph G, int u, int v){
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("Graph Error: calling addEdge() with vertices out of bounds\n");
		exit(1);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

// addArc(): inserts a new edge joining u to v (one direction)
// Preconditions: 1<=u<=getOrder(G), 1<=v<=getOrder(G)
void addArc(Graph G, int u, int v){
	if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)){
		printf("GRaph Error: calling addArc() with vertices out of bounds\n");
		exit(1);
	}

	List L = G->adj[u];
	moveFront(L);
	while(index(L) > -1 && v > get(L)){
		moveNext(L);
	}
	if(index(L) == -1)
		append(L, v);
	else
		insertBefore(L, v);
	G->size++;
}

// Performs Breadth-first search on the Graph G with the
// given source vertex s.
void BFS(Graph G, int s) {
	 //using BFS from textbook
	 for(int i = 1; i < (G->order); i++) {
		  G->color[i] = WHITE;
			G->parent[i] = NIL;
      G->distance[i] = INF;
   }
	 G->color[s] = GRAY;
	 G->source = s;
   G->distance[s] = 0;

	 List Q = newList();
   prepend(Q, s);
   while(length(Q) > 0) {
      int u = back(Q);
      deleteBack(Q);
      List adj = G->adj[u];
      moveFront(adj);
      while(index(adj) > -1) {
         int v = get(adj);
         if(G->color[v] == WHITE) {
            G->color[v] = GRAY;
            G->parent[v] = u;
            G->distance[v] = G->distance[u] + 1;
            prepend(Q, v);
         }
         moveNext(adj);
      }
   }
   freeList(&Q);
}

//Other operations
void printGraph(FILE *out, Graph G) {
   for(int i = 1; i <= getOrder(G); i++) {
      fprintf(out, "%d: ", i);
      printList(out, G->adj[i]);
      fprintf(out, "\n");
   }
}
