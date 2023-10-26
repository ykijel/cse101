//-----------------------------------------------------------------------------
// Yahli Kijel
// ykijel
// 2023 Fall CSE101 PA3
// Graph.c
// Graph ADT implementation and functions
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

// Define the structure for a graph
typedef struct GraphObj {
    List* adjLists; // Array of adjacency lists
    int* color;    // Array to track visited vertices
    int* parent;   // Array to track parents in DFS
    int* discover; // Array to track discovery time
    int* finish;   // Array to track finish time
    int order;     // Number of vertices
    int size;      // Number of edges
    int time;      // Global time variable
} GraphObj;

// Function to create a new graph with 'n' vertices
Graph newGraph(int n) {
    Graph G = (Graph)malloc(sizeof(GraphObj));
    G->adjLists = (List*)malloc((n + 1) * sizeof(List));
    G->color = (int*)malloc((n + 1) * sizeof(int));
    G->parent = (int*)malloc((n + 1) * sizeof(int));
    G->discover = (int*)malloc((n + 1) * sizeof(int));
    G->finish = (int*)malloc((n + 1) * sizeof(int));
    G->order = n;
    G->size = 0;
    G->time = 0;

    for (int i = 1; i <= n; i++) {
        G->adjLists[i] = newList();
        G->color[i] = -1;    // -1 represents white (unvisited)
        G->parent[i] = NIL;  // NIL represents no parent
        G->discover[i] = UNDEF;
        G->finish[i] = UNDEF;
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
        free(G->discover);
        free(G->finish);
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

// Function to get the parent of vertex 'u' in DFS tree
int getParent(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->parent[u];
    }
    return NIL;
}

// Function to get the discovery time of vertex 'u' in DFS tree
int getDiscover(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->discover[u];
    }
    return 0;
}

// Function to get the finish time of vertex 'u' in DFS tree
int getFinish(Graph G, int u) {
    if (1 <= u && u <= getOrder(G)) {
        return G->finish[u];
    }
    return 0;
}

void addArc(Graph G, int u, int v) {
    if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
    	int edgeExists = 0;
    	for (moveFront(G->adjLists[u]); index(G->adjLists[u]) >= 0; moveNext(G->adjLists[u])) {
            if (get(G->adjLists[u]) == v) {
                edgeExists = 1;
                break;
            }
        }
        if(!edgeExists)
        {
        	addHelper(G->adjLists[u], v);
        	G->size++;
        }
        
    }
}

// Function to add an undirected edge between vertices 'u' and 'v'
void addEdge(Graph G, int u, int v) {
    if (1 <= u && u <= getOrder(G) && 1 <= v && v <= getOrder(G)) {
    	int edgeExists = 0;
    	for (moveFront(G->adjLists[u]); index(G->adjLists[u]) >= 0; moveNext(G->adjLists[u])) {
            if (get(G->adjLists[u]) == v) {
                edgeExists = 1;
                break;
            }
        }
        if(!edgeExists)
        {
        	addHelper(G->adjLists[u], v);
        	addHelper(G->adjLists[v], u);
        	G->size++;
        }
        
    }
}

// Function to perform Depth-First Search (DFS)
void DFS(Graph G, List S) {
    int stackEnd = length(S); // Initialize stackEnd to the length of the list (top of the stack)
    List stack = newList(); // Create a temporary List to simulate the stack

    // Reset graph properties
    for (int x = 1; x <= G->order; x++) {
        G->color[x] = -1;  // -1 represents white (unvisited)
        G->parent[x] = NIL; // NIL represents no parent
    }
    G->time = 0;

    for (int i = 1; i <= stackEnd; i++) {
        int x = front(S); // Get the first element from List S (top of the stack)
        deleteFront(S);   // Remove the first element to simulate stack behavior

        if (G->color[x] == -1) {
            Visit(G, x, stack);
        }
    }

    // Transfer elements from the stack to List S in the correct order
    moveFront(stack);
    while (index(stack) >= 0) {
        append(S, get(stack));
        moveNext(stack);
    }
    freeList(&stack); // Free the temporary stack list
}

// Visit function for DFS (modified to use a separate stack list)
void Visit(Graph G, int x, List stack) {
    G->discover[x] = ++(G->time);
    G->color[x] = 0; // 0 represents gray (visited but not explored)

    List adjList = G->adjLists[x];
    for (moveFront(adjList); index(adjList) >= 0; moveNext(adjList)) {
        int y = get(adjList);
        if (G->color[y] == -1) {
            G->parent[y] = x;
            Visit(G, y, stack);
        }
    }

    G->color[x] = 1; // 1 represents black (explored)
    G->finish[x] = ++(G->time);
    prepend(stack, x); // Push the current vertex onto the stack list
}

// Function to create a new graph that is the transpose of the given graph
Graph transpose(Graph G) {
    Graph transposed = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {
        List adjList = G->adjLists[u];
        for (moveFront(adjList); index(adjList) >= 0; moveNext(adjList)) {
            int v = get(adjList);
            addArc(transposed, v, u); // Reverse the direction by swapping u and v
        }
    }
    return transposed;
}

// Function to create a new graph that is a copy of the given graph
Graph copyGraph(Graph G) {
    Graph copy = newGraph(getOrder(G));
    for (int u = 1; u <= getOrder(G); u++) {
        List adjList = G->adjLists[u];
        for (moveFront(adjList); index(adjList) >= 0; moveNext(adjList)) {
            int v = get(adjList);
            addArc(copy, u, v); // Copy the edges from G to the copy
        }
    }
    return copy;
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

void addHelper(List myList, int x)
{
        if (length(myList) == 0) {
            prepend(myList, x);
        } else {
            moveFront(myList);
            int inserted = 0;

            while (index(myList) >= 0) {
            	
                if (x < get(myList)) {
                    insertBefore(myList, x);
                    inserted = 1;
                    break;
                }
                moveNext(myList);
            }

            // If the line was not inserted, insert it at the end
            if (!inserted) {
                append(myList, x);
            }
        }
}
