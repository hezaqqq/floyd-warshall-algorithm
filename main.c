#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    graph *g = load_graph("../graph1.txt");

    display_graph(g);

    calculate_full_floyd_warshall(g);

    return 0;
}