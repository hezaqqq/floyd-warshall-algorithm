#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    graph *g = load_graph("../graphs/graph_1.txt");

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
