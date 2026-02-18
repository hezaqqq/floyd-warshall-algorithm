//
// Created by Timothée on 18/02/2026.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graph.h"

graph* load_graph(char *filename) {
    FILE *graph_text = fopen(filename, "r");
    graph *g = malloc(sizeof(graph));
    g->longest_weight = 0;

    // Reading vertices & arcs number
    fscanf(graph_text, "%d", &g->num_vertices);
    fscanf(graph_text, "%d", &g->num_arcs);

    g->matrix = malloc(g->num_vertices * sizeof(int*));

    // Initialisation of empty matrix
    for (int i = 0; i < g->num_vertices; i++) {
        g->matrix[i] = malloc(g->num_vertices * sizeof(int));
        for (int j = 0; j < g->num_vertices; j++) {
            g->matrix[i][j] = 0;
        }
    }

    // Filling of matrix
    for (int i = 0; i < g->num_vertices; i++) {
        int source, destination, weight;
        fscanf(graph_text, "%d %d %d", &source, &destination, &weight);
        g->matrix[source][destination] = weight;

        // Counts the length of the int (for display)
        int len = 0;
        int temp = weight;

        if (temp <= 0) {
            len++;
            temp = -temp;
        }

        while (temp > 0) {
            temp /= 10;
            len++;
        }

        if (len > g->longest_weight) {
            g->longest_weight = len;
        }
    }

    fclose(graph_text);
    return g;
}


void display_graph(graph *g) {
    printf("Vertices: %d\n", g->num_vertices);
    printf("Arcs: %d\n", g->num_arcs);
    int box_width = g->longest_weight + 2;

    // Print column headers
    printf("%*s", box_width, "");
    for (int j = 0; j < g->num_vertices; j++) {
        printf("%*d", box_width, j);
    }
    printf("\n");

    for (int i = 0; i < g->num_vertices; i++) {
        // Print row header
        printf("%*d", box_width, i);

        for (int j = 0; j < g->num_vertices; j++) {
            printf("%*d", box_width, g->matrix[i][j]);
        }
        printf("\n");
    }
    return;
}