#include <stdlib.h>
#include "graph.h"

graph* load_graph(char *filename) {
    FILE *graph_text = fopen(filename, "r");
    graph *g = malloc(sizeof(graph));
    g->longest_weight = 0;

    // Reading vertices & arcs number
    fscanf(graph_text, "%d", &g->num_vertices);
    fscanf(graph_text, "%d", &g->num_arcs);

    g->matrix = malloc(g->num_vertices * sizeof(int*));
    g->predecessor_matrix = malloc(g->num_vertices * sizeof(int*));

    // Initialisation of empty matrix
    for (int i = 0; i < g->num_vertices; i++) {
        g->matrix[i] = malloc(g->num_vertices * sizeof(int));
        g->predecessor_matrix[i] = malloc(g->num_vertices * sizeof(int));

        for (int j = 0; j < g->num_vertices; j++) {
            if (i == j) {
                g->matrix[i][j] = 0;
                g->predecessor_matrix[i][j] = 999999;
            }
            else {
                g->matrix[i][j] = 999999;
                g->predecessor_matrix[i][j] = 999999;
            }
        }
    }

    // Filling of matrix
    for (int i = 0; i < g->num_arcs; i++) {
        int source, destination, weight;
        fscanf(graph_text, "%d %d %d", &source, &destination, &weight);
        g->matrix[source][destination] = weight;
        g->predecessor_matrix[source][destination] = source;

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

void display_matrix(int **matrix, int longest_weight, int num_vertices,char *replace_char) {

    int box_width = longest_weight + 2;

    // Print column headers
    printf("%*s", box_width, "");
    for (int i = 0; i < num_vertices; i++) {
        printf("%*d", box_width, i);
    }
    printf("\n");

    for (int i = 0; i < num_vertices; i++) {
        // Print row header
        printf("%*d", box_width, i);

        for (int j = 0; j < num_vertices; j++) {
            if (matrix[i][j] == 999999) {
                printf("%*s", box_width, replace_char);
            }
            else {
                printf("%*d", box_width, matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void display_graph(graph *g) {
    printf("Vertices: %d\n", g->num_vertices);
    printf("Arcs: %d\n", g->num_arcs);
    printf("Adjancy matrix:\n");

    display_matrix(g->matrix, g->longest_weight, g->num_vertices, "INF");

    printf("\n\nPredecessor matrix:\n");

    display_matrix(g->predecessor_matrix, g->longest_weight, g->num_vertices, "_");
}

void calculate_step_for_k(graph *g, int k) {
    if (k < 0 || k >= g->num_vertices) {
        return;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        for (int j = 0; j < g->num_vertices; j++) {
            // Skip the chosen node k row and column
            if (i == k || j == k) {
                continue;
            }

            // Check if a path through the chosen node k exists
            if (g->matrix[i][k] != 999999 && g->matrix[k][j] != 999999) {
                int new_dist = g->matrix[i][k] + g->matrix[k][j];

                if (g->matrix[i][j] > new_dist) {
                    g->matrix[i][j] = new_dist;
                    // Predecessor of j becomes the predecessor of j via k
                    g->predecessor_matrix[i][j] = g->predecessor_matrix[k][j];
                }
            }
        }
    }
}

void calculate_full_floyd_warshall(graph *g) {

    for (int k = 0; k < g->num_vertices; k++) {
        calculate_step_for_k(g, k);

        // Display the matrices result after a node
        printf("\n--------------------------------------------");
        printf("\nStep %d (Node %d)\n", k + 1, k);

        printf("\nAdjacency Matrix:\n");
        display_matrix(g->matrix, g->longest_weight, g->num_vertices, "INF");

        printf("\nPredecessor Matrix:\n");
        display_matrix(g->predecessor_matrix, g->longest_weight, g->num_vertices, "_");
    }
}
