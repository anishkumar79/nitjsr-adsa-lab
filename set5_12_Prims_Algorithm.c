#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 5  // Number of vertices

int minKey(int key[], bool mst[]) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++)
        if (!mst[v] && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 8, 5},
        {0, 3, 0, 0, 7},
        {6, 8, 0, 0, 9},
        {0, 5, 7, 9, 0}
    };

    int parent[V], key[V], total = 0;
    bool mst[V] = {false};

    for (int i = 0; i < V; i++) key[i] = INT_MAX;
    key[0] = 0; parent[0] = -1;

    for (int c = 0; c < V - 1; c++) {
        int u = minKey(key, mst);
        mst[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && !mst[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    printf("Edge\tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d\t%d\n", parent[i], i, graph[i][parent[i]]);
        total += graph[i][parent[i]];
    }
    printf("Total weight of MST: %d\n", total);
}
