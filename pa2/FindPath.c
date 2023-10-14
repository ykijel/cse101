#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Graph.h"
#define INF -1
#define NIL 0

// Helper function to print the shortest path from source to destination
void printPath(FILE *out, Graph G, int source, int destination) {
    if (destination == source) {
        fprintf(out, "%d", source);
    } else if (getParent(G, destination) == NIL) {
        fprintf(out, "%d is not reachable from %d", destination, source);
    } else {
        printPath(out, G, source, getParent(G, destination));
        fprintf(out, " %d", destination);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE *in, *out;
    in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int n, u, v;
    fscanf(in, "%d", &n);

    Graph G = newGraph(n);

    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) {
            break;
        }

        addEdge(G, u, v);
    }
    
    printGraph(out, G);
    fprintf(out, "\n");

    while (fscanf(in, "%d %d", &u, &v) == 2) {
        if (u == 0 && v == 0) {
            break;
        }

        if (u < 1 || u > n || v < 1 || v > n) {
            fprintf(out, "Error: Invalid source or destination vertex.\n");
        } else {
            BFS(G, u);

            if (getDist(G, v) == INF) {
                fprintf(out, "The distance from %d to %d is infinity\n", u, v);
                fprintf(out, "No %d-%d path exists\n", u, v);
            } else {
                fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
                fprintf(out, "A shortest %d-%d path is: ", u, v);

                // Call the helper function to print the path
                printPath(out, G, u, v);

                fprintf(out, "\n");
                fprintf(out, "\n");
                
            }
        }
    }

    freeGraph(&G);
    fclose(in);
    fclose(out);
    return 0;
}
