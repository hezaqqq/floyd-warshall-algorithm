#include <stdlib.h>
#include "graph.h"

graph* load_graph(char *filename) {
    FILE *graph_text = fopen(filename, "r");
    if (graph_text == NULL) return NULL;

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
        if (source == destination && weight >= 0) continue;
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
    printf("Adjacency matrix:\n");

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

int detect_absorbing_cycle(graph *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        if (g->matrix[i][i] < 0) { // We check the diagonal values to see if the weight of going from a vertex to itself through any possible path is negative (this would mean that there is a negative cycle reachable from that vertex)
            return 1; // Absorbing cycle detected
        }
    }
    return 0; // No absorbing cycle
}

void display_shortest_path(graph *g, int start, int end) {
    if (g->matrix[start][end] == 999999) {
        printf("No path exists from %d to %d.\n", start, end);
        return;
    }

    // We retrace the shortest path backwards from end to start thanks to the predecessor matrix
    int path[1024]; 
    int length = 0;
    int current = end; // As stated above, we start from the last vertex

    while (current != start) {
        path[length] = current;
        length++;
        current = g->predecessor_matrix[start][current];
    }
    path[length] = start; // Adding the start at the end of the path
    length++;

    // Display the path array in the correct order, which is backwards again so it's the right way this time
    printf("Shortest path from %d to %d: ", start, end);
    for (int i = length - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) { // We want to print the arrow after every vertex except the last one
            printf(" -> ");
        } 
    }
    printf("\nTotal weight: %d\n", g->matrix[start][end]);
}


void path_question(graph *g) {
    char answer;

    printf("\nDo you want to find a shortest path? (y/n): ");
    scanf(" %c", &answer);

    while (answer == 'y' || answer == 'Y') {
        int start, end;

        printf("Starting vertex (0 to %d): ", g->num_vertices - 1);
        scanf("%d", &start);
        printf("Ending vertex (0 to %d): ", g->num_vertices - 1);
        scanf("%d", &end);

        if (start < 0 || start >= g->num_vertices ||
            end < 0 || end >= g->num_vertices) {
            printf("Invalid vertices.\n");
        } else if (start == end) {
            printf("Start and end are the same vertex.\n");
        } else {
            display_shortest_path(g, start, end);
        }

        printf("\nAnother path? (y/n): ");
        scanf(" %c", &answer);
    }
    return;
}