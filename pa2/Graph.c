#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"
#define INF -1
#define NIL 0

// Define the structure for a graph
typedef struct GraphObj {
    List* adjLists; // Array of adjacency lists
    int* color;    // Array to track visited vertices
    int* parent;   // Array to track parents in BFS
    int* distance; // Array to track distances in BFS
    int order;     // Number of vertices
    int size;      // Number of edges
    int source;    // Source vertex for BFS
} GraphObj;

// Function to create a new graph with 'n' vertices
Graph newGraph(int n) {
    Graph G = (Graph)malloc(sizeof(GraphObj));
    G->adjLists = (List*)malloc((n + 1) * sizeof(List));
    G->color = (int*)malloc((n + 1) * sizeof(int));
    G->parent = (int*)malloc((n + 1) * sizeof(int));
    G->distance = (int*)malloc((n + 1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->source = NIL;

    for (int i = 1; i <= n; i++) {
        G->adjLists[i] = newList();
        G->color[i] = -1;    // -1 represents white (unvisited)
        G->parent[i] = NIL;  // NIL represents no parent
        G->distance[i] = INF; // INF represents infinite distance
    }

    return G;
}

// Function to free the graph
void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        Graph G = *pG;
        for (int i = 1; i <= G->order; i++) {
            freeList(&(G->adjLists[i]));
        }
        free(G->adjLists);
        free(G->color);
        free(G->parent);
        free(G->distance);
        free(G);
        *pG = NULL;
    }
}

// Function to get the order of the graph (number of vertices)
int getOrder(Graph G) {
    return G->order;
}

// Function to get the size of the graph (number of edges)
int getSize(Graph G) {
    return G->size;
}

// Function to get the source vertex for BFS
int getSource(Graph G) {
    return G->source;
}

// Function to get the parent of vertex 'u' in BFS tree
int getParent(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->parent[u];
    }
    return NIL;
}

// Function to get the distance from the source to vertex 'u' in BFS tree
int getDist(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->distance[u];
    }
    return INF;
}

// Function to retrieve the path from the source to vertex 'u' in BFS tree
void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL || getDist(G, u) == INF) {
        append(L, NIL);
        return;
    }

    if (u == getSource(G)) {
        append(L, u);
    } else if (getParent(G, u) == NIL) {
        append(L, NIL);
    } else {
        getPath(L, G, getParent(G, u));
        append(L, u);
    }
}

// Function to make the graph null (clear it)
void makeNull(Graph G) {
    for (int i = 1; i <= G->order; i++) {
        clear(G->adjLists[i]);
        G->color[i] = -1;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    G->size = 0;
    G->source = NIL;
}

// Function to add an undirected edge between vertices 'u' and 'v'
void addEdge(Graph G, int u, int v) {
    if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
        append(G->adjLists[u], v);
        append(G->adjLists[v], u);
        G->size--;
    }
}

// Function to add a directed edge from vertex 'u' to vertex 'v'
void addArc(Graph G, int u, int v) {
    if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
        append(G->adjLists[u], v);
        G->size++;
    }
}

// Function to perform Breadth-First Search (BFS) from source 's'
void BFS(Graph G, int s) {
    if (1 <= s && s <= getOrder(G)) {
        for (int x = 1; x <= G->order; x++) {
            if (x != s) {
                G->color[x] = -1;    // -1 represents white (unvisited)
                G->parent[x] = NIL;  // NIL represents no parent
                G->distance[x] = INF; // INF represents infinite distance
            }
        }

        G->color[s] = 0; // 0 represents gray (visited but not explored)
        G->parent[s] = NIL;
        G->distance[s] = 0;

        List Q = newList();
        append(Q, s);

        while (length(Q) != 0) {
            int x = front(Q);
            deleteFront(Q);

            List adjList = G->adjLists[x];
            for (moveFront(adjList); index(adjList) >= 0; moveNext(adjList)) {
                int y = get(adjList);
                if (G->color[y] == -1) {
                    G->color[y] = 0; // 0 represents gray (visited but not explored)
                    G->parent[y] = x;
                    G->distance[y] = G->distance[x] + 1;
                    append(Q, y);
                }
            }

            G->color[x] = 1; // 1 represents black (explored)
        }

        freeList(&Q);
    }
}

// Function to print the graph
void printGraph(FILE* out, Graph G) {
    if (out != NULL) {
        for (int i = 1; i <= G->order; i++) {
            fprintf(out, "%d: ", i);
            printList(out, G->adjLists[i]);
            fprintf(out, "\n");
        }
    }
}
