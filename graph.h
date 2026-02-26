#ifndef FLOYD_WARSHALL_ALGORITHM_GRAPH_H
#define FLOYD_WARSHALL_ALGORITHM_GRAPH_H

#include <stdio.h>

typedef struct {
    int num_vertices;
    int num_arcs;
    int **matrix;
    int **predecessor_matrix;
    int longest_weight;

} graph;

graph* load_graph(char *filename);
void display_matrix(int **matrix, int longest_weight, int num_vertices,char *replace_char);
void display_graph(graph *g);
void calculate_step_for_k(graph *g, int k);
void calculate_full_floyd_warshall(graph *g);

#endif //FLOYD_WARSHALL_ALGORITHM_GRAPH_H
