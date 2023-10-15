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

int getSource(GraphG);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

void printGraph(FILE* out, Graph G);

#endif
