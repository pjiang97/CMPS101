//Peter Jiang
//pjiang1
//CMPS101 PA4
//FindPath.c

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "Graph.h"

#define MAX_LEN 256

int main(int argc, char * argv[]){
   //check command line for 3 arguments
   if( argc != 3 ){
      printf("FindPath: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   FILE *in, *out;
   int size, u, v;
   int source, dest;

   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   //gets size
    fscanf(in, "%d", &size);
    Graph G = newGraph(size);

    // read edges
    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) break;
        addEdge(G,u,v);
    }

    printGraph(out, G);

    List L = newList();
    while (fscanf(in, "%d %d", &source, &dest)) {
        if (source == 0 && dest == 0){
            break;
        }
        BFS(G, source);
        getPath(L, G, dest);

        if (getDist(G, dest) != -1) {
            fprintf(out, "\nThe distance from %d to %d is %d \n", source, dest, getDist(G, dest));
            fprintf(out, "A shortest %d-%d path is: ", source, dest);
            printList(out, L);
            fprintf(out, "\n");
        }
				else{
            fprintf(out, "\nThe distance from %d to %d is infinity \n", source, dest);
            fprintf(out, "No %d-%d path exists\n", source, dest);
        }
        clear(L);
    }

		//free memory
    freeList(&L);
    freeGraph(&G);
    fclose(in);
    fclose(out);
}
