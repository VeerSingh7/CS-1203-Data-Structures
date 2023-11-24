#include <stdio.h>
#define V 4
#define INF 99999

// Auxiliary space analysis:
// Two VxV matrices are used: dist and parent.
// Each matrix requires V^2 space.
// Assuming size of int is 4 bytes, total auxiliary space is 2 * (V^2 * 4 bytes).

void printSolution(int dist[][V], int parent[][V]) {
    printf("The following matrix shows the shortest distances between every pair of vertices \n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

void floydWarshall(int graph[][V]) {
    int dist[V][V], parent[V][V]; // Auxiliary space: 2 * V^2 integers

    // Initialize distance and parent matrices
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            dist[i][j] = graph[i][j];
            if (graph[i][j] != INF && i != j)
                parent[i][j] = i;
            else
                parent[i][j] = -1;
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    parent[i][j] = parent[k][j]; // Update parent
                }
            }
        }
    }

    // Check for negative cycles
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("Negative cycle detected\n");
            return;
        }
    }

    printSolution(dist, parent);
}

int main() {
    int graph[V][V] = { { 0, 5, INF, 10 },
                        { INF, 0, 3, INF },
                        { INF, INF, 0, 1 },
                        { INF, INF, INF, 0 } };

    floydWarshall(graph);
    return 0;
}
