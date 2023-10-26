//-----------------------------------------------------------------------------
// Yahli Kijel
// ykijel
// 2023 Fall CSE101 PA3
// GraphTest.c
// Tests for Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   
   Graph G = newGraph(100);
   List S = newList();
   Graph T=NULL, C=NULL;
   
   printf("Size: %d\n", getSize(G));
   addArc(G, 54,1);
   addArc(G, 54,2);
   addArc(G, 54,2);
   addArc(G, 54,3);
   addArc(G, 1,54);
   addArc(G, 1,54);
   addArc(G, 1,55);
   addArc(G, 1,55);
   printf("Size: %d\n", getSize(G));
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");

   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");

   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}
