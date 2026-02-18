//
// Created by Timothée on 18/02/2026.
//

#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

graph* load_graph(char *filename) {
    FILE *graph_text = fopen(filename, "r");
    if (!graph_text) {
        perror("Error opening file");
        return NULL;
    }
    graph *g = malloc(sizeof(graph));

    fscanf(graph_text, "%d", &g->num_vertices);
    fscanf(graph_text, "%d", &g->num_arcs);

    printf("Vertices: %d\n", g->num_vertices);
    printf("Arcs: %d\n", g->num_arcs);

    for (int i = 0; i < g->num_arcs; i++) {
        int source, destination, weight;
        fscanf(graph_text, "%d %d %d", &source, &destination, &weight);
        printf("Source: %d  Destination: %d  (Weight: %d)\n", source, destination, weight);

    }

    fclose(graph_text);
    return g;
}