#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int u, v, w;
};

int parent[50];

int find(int i) {
    return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
}

void unionSet(int a, int b) {
    parent[a] = b;
}

int cmp(const void *a, const void *b) {
    return ((struct Edge*)a)->w - ((struct Edge*)b)->w;
}

int main() {
    int V, E, total = 0;
    printf("Enter vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Edge edge[E];
    printf("Enter edges (u v w):\n");
    for (int i = 0; i < E; i++)
        scanf("%d %d %d", &edge[i].u, &edge[i].v, &edge[i].w);

    qsort(edge, E, sizeof(edge[0]), cmp);

    for (int i = 0; i < V; i++) parent[i] = i;

    printf("\nEdge\tWeight\n");
    for (int i = 0, c = 0; i < E && c < V - 1; i++) {
        int a = find(edge[i].u), b = find(edge[i].v);
        if (a != b) {
            printf("%d - %d\t%d\n", edge[i].u, edge[i].v, edge[i].w);
            total += edge[i].w;
            unionSet(a, b);
            c++;
        }
    }
    printf("Total weight of MST: %d\n", total);
}
