#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
    graph *g = load_graph("../graph.txt");

    display_graph(g);

    return 0;
}