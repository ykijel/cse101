#ifndef GRAPH_H
#define GRAPH_H
#include <stdbool.h>
#include "List.h"
#define INF -1
#define NIL 0

typedef struct GraphObj* Graph;

Graph newGraph(int n);

void freeGraph(Graph* pG);

int getOrder(Graph G);

int getSize(Graph G);

int getParent(Graph G, int u);

int getDiscover(Graph G, int u);

int getFinish(Graph G, int u);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void DFS(Graph G, List S);

Graph transpose(Graph G);

Graph copyGraph(Graph G);

void printGraph(FILE* out, Graph G);

#endif
