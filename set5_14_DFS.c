#include <stdio.h>

#define MAX 10
int graph[MAX][MAX], visited[MAX], disc[MAX], finish[MAX], time = 0, n;

void DFS(int u) {
    visited[u] = 1;
    disc[u] = ++time;

    for (int v = 0; v < n; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {
                printf("Tree Edge: %d -> %d\n", u, v);
                DFS(v);
            } else if (!finish[v])
                printf("Back Edge: %d -> %d\n", u, v);
            else if (disc[u] < disc[v])
                printf("Forward Edge: %d -> %d\n", u, v);
            else
                printf("Cross Edge: %d -> %d\n", u, v);
        }
    }
    finish[u] = ++time;
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    for (int i = 0; i < n; i++)
        if (!visited[i])
            DFS(i);
}
