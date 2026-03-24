#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    graph *g = load_graph(argv[1]);
    if (g == NULL) {
        printf("No graph found (%s).\n", argv[1]);
        return 1;
    }

    display_graph(g);

    calculate_full_floyd_warshall(g);

    // Absorbing cycle detection
    if (detect_absorbing_cycle(g)) {
        printf("\nThe graph contains an absorbing cycle (at least)\n");
        printf("Shortest paths cannot be computed.\n");
    } else {
        printf("\nNo absorbing circuit detected.\n");
        // Allow user to query shortest paths
        path_question(g);
    }

    return 0;
}
