/*Peter Jiang
	pjiang1
	4/23/2018
	pa2
*/

	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#include "List.h"
	#define MAX_LEN 200

	int main(int argc, char * argv[]){

	   // Initialize variables
	   int count = 0;
	   FILE *in, *out;
	   char line[MAX_LEN];

	   // check command line
	   if( argc != 3 ){
	      printf("Usage: %s <input file> <output file>\n", argv[0]);
	      exit(1);
	   }

	   //open files to read and write
	   in = fopen(argv[1], "r");
	   out = fopen(argv[2], "w");
	   if( in==NULL ){
	      printf( "Unable to open file %s for reading\n", argv[1]);
	      exit(1);
	   }
	   if( out==NULL ){
	      printf("Unable to open file %s for writing\n", argv[2]);
	      exit(1);
	   }

	   //count the lines //
	   while( fgets(line, MAX_LEN, in) != NULL)  {
	      count++;
	   }

	   char lines[count - 1][MAX_LEN];
	   int N = 0;
	   //reset file pointer to start of file
	   rewind(in);

	   // Copy the file lines into a string array
	   while(fgets(line, MAX_LEN, in) != NULL) {
	      strcpy(lines[N], line);
	       N++;
	   }

	   // Create new List ADT
	   List list = newList();

	   append(list, 0);

	   // Insertion Sort
	   for(int j = 1; j < count; ++j) {
	      char *tmp = lines[j];
	      int i = j - 1;
	      moveBack(list);
	      while(i >= 0 && strcmp(tmp, lines[get(list)]) <= 0) {
	         --i;
	         movePrev(list);
	      }
	      if (index(list)>=0){
	         insertAfter(list, j);
	      } else{
	         prepend(list, j);
			 }
	   }

	   // Reset index to the front
	   moveFront(list);

	   while(index(list)>=0) {
	      fprintf(out, "%s", lines[get(list)]);
	      moveNext(list);
	   }

	   fclose(in);
	   fclose(out);

	   // Free list ADT
	   freeList(&list);

	   return(0);
	}
