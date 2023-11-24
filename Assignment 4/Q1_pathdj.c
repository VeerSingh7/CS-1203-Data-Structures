#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5  // Number of vertices in the graph (example)

// Function to find the vertex with minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int n, int parent[]) {
    printf("Vertex\t Distance from Source\tPath");
    for (int i = 1; i < V; i++) {
        printf("\n%d -> %d \t\t %d\t\t%d ", 0, i, dist[i], i);
        printPath(parent, i);
    }
}

// Function to print paths from source to j using parent array
void printPath(int parent[], int j) {
    // Base Case : If j is source
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf(" %d", j);
}

// Funtion that implements Dijkstra's single source shortest path algorithm for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src) {
    int dist[V];  // The output array. dist[i] will hold the shortest distance from src to i
    int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized
    int parent[V]; // Parent array to store shortest path tree

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0, parent[i] = -1;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }

   
    printSolution(dist, V, parent);
}
int main() {
    
    int graph[V][V] = {{0, 2, 0, 6, 0},
                       {2, 0, 3, 8, 5},
                       {0, 3, 0, 0, 7},
                       {6, 8, 0, 0, 9},
                       {0, 5, 7, 9, 0},
                      };

    dijkstra(graph, 0);

    return 0;
}
