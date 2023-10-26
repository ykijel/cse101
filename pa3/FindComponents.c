//-----------------------------------------------------------------------------
// Yahli Kijel
// ykijel
// 2023 Fall CSE101 PA3
// FindComponents.c
// Main function implementation
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s infile outfile\n", argv[0]);
        exit(1);
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if (!in || !out) {
        perror("Error opening files");
        exit(1);
    }

    // Read the number of vertices
    int numVertices;
    if (fscanf(in, "%d", &numVertices) != 1) {
        fprintf(stderr, "Error reading the number of vertices from the input file.\n");
        exit(1);
    }

    // Create the graph
    Graph G = newGraph(numVertices);

    int source, destination;
    while (fscanf(in, "%d %d", &source, &destination) == 2) {
        if (source == 0 && destination == 0) {
            break; // End of edges in the input file
        }
        addArc(G, source, destination);
    }

    // Print the adjacency list representation of G
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // Create the component list
    List componentList = newList();
    for (int i = 1; i <= numVertices; i++) {
        append(componentList, i);
    }

    // Run DFS on G
    DFS(G, componentList);

    // Calculate the transpose of G
    Graph GT = transpose(G);

    // Declare the strongComponents array
    List *strongComponents = malloc(numVertices * sizeof(List));
    for (int i = 0; i < numVertices; i++) {
        strongComponents[i] = newList();
    }

    // Run DFS on the transpose GT
    DFS(GT, componentList);

    // Determine the strong components of G
    int numComponents = 0;
    int *componentNumber = malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        componentNumber[i] = -1; // Initialize to -1, indicating no component yet
    }
    moveBack(componentList);
    
    
    while(index(componentList) >= 0){
    	int vertex = get(componentList);
    	int parent = getParent(GT, vertex);
    	List component = newList();
    	numComponents++;
    	while(parent != NIL)
    	{
    		prepend(component, vertex);
    		movePrev(componentList);
    		vertex = get(componentList);
    		parent = getParent(GT, vertex);
    	}
    	strongComponents[numComponents - 1] = component;
    	prepend(component, vertex);
    	movePrev(componentList);
    }
    fprintf(out, "G contains %d strongly connected components:\n", numComponents);

    // Print the strong components
    for (int i = 0; i < numComponents; i++) {
        List component = strongComponents[i];
        fprintf(out, "Component %d: ", i + 1);
        moveFront(component);

        while (index(component) >= 0) {
            fprintf(out, "%d ", get(component));
            moveNext(component);
        }

        freeList(&strongComponents[i]);
        fprintf(out, "\n");
    }

    free(componentNumber);
    free(strongComponents);
    freeList(&componentList);
    freeGraph(&G);
    freeGraph(&GT);
    fclose(in);
    fclose(out);

    return 0;
}
