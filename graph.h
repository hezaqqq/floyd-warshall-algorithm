//
// Created by Timothée on 18/02/2026.
//

#ifndef FLOYD_WARSHALL_ALGORITHM_GRAPH_H
#define FLOYD_WARSHALL_ALGORITHM_GRAPH_H

#include <stdio.h>

typedef struct {
    int num_vertices;
    int num_arcs;
    int **matrix;
} graph;

graph* load_graph(char *filename);

#endif //FLOYD_WARSHALL_ALGORITHM_GRAPH_H
