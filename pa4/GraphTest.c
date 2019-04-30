//Peter Jiang
//pjiang1
//CMPS101 PA4
//GraphTest.c


#include<stdlib.h>
#include<stdio.h>

#include"Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices
   List  P = newList(); // peripheral vertices
   List  E = newList(); // eccentricities
   Graph G = NULL;

   // Build graph G
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);
   addEdge(G,1, 2);

   // Print adjacency list representation of G
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex
   for(s=1; s<=n; s++){
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and
   // Peripheral vertices.
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results
   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   Graph X = newGraph(250);
   int j = 0;
   for(j = 1; j < 250; ++j) {
      if(j % 4 == 0)
         addEdge(S, j, 250 - j);
      else if(j % 5 == 1)
         addArc(X, j, 250 - j);
   }

   List A = newList();
   getPath(A, X, 99);
   printf("Path from 101 to 99 again: ");
   printList(stdout, A);
   printf("\n");

   for(i = 1; i < 250; ++i) {
      BFS(X, i);
      for(j = 1; j < 250; ++j) {
         int d = getDist(X, j);
         if(d != INF)
            printf("Dist %d-%d: %d\n", i, j, d);
      }
   }

   BFS(L, 25);
   List N = newList();
   getPath(N, L, 72;
   printf("Path from 25 to 72: ");
   printList(stdout, N);
   printf("\n");

   BFS(L, 89);
   List K = newList();
   getPath(K, L, 39);
   printf("Path from 89 to 39: ");
   printList(stdout, K);
   printf("\n");

   freeList(&K);
   freeList(&L);

   BFS(K, 10);
   BFS(L, 101);

   freeList(&M);
   freeGraph(&S);

   return(0);
}
