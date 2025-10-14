#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to run Bellman-Ford algorithm
void BellmanFord(int graph[][3], int V, int E, int src) {
    int dis[V];
    
    // Step 1: Initialize distances
    for (int i = 0; i < V; i++)
        dis[i] = INT_MAX;
    dis[src] = 0;

    // Step 2: Relax all edges |V| - 1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph[j][0];
            int v = graph[j][1];
            int weight = graph[j][2];

            if (dis[u] != INT_MAX && dis[u] + weight < dis[v])
                dis[v] = dis[u] + weight;
        }
    }

    // Step 3: Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = graph[i][0];
        int v = graph[i][1];
        int weight = graph[i][2];

        if (dis[u] != INT_MAX && dis[u] + weight < dis[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    // Print results
    printf("Vertex\tDistance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d\t\t%d\n", i, dis[i]);
}

// Driver code
int main() {
    int V = 5; // vertices
    int E = 8; // edges

    // Each row of graph[] = {source, destination, weight}
    int graph[][3] = { 
        {0, 1, -1}, 
        {0, 2, 4},
        {1, 2, 3}, 
        {1, 3, 2}, 
        {1, 4, 2}, 
        {3, 2, 5}, 
        {3, 1, 1}, 
        {4, 3, -3}
    };

    BellmanFord(graph, V, E, 0);
    return 0;
}
