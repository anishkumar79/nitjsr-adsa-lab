#include <stdio.h>

#define MAX 25

int G[MAX][MAX];
int n, e, m;

// Check if subset nodes[] of size m forms a clique
int isClique(int nodes[]) {
    for (int i = 0; i < m; i++)
        for (int j = i + 1; j < m; j++)
            if (!G[nodes[i]][nodes[j]])
                return 0;
    return 1;
}

// Recursive combination generator
int found = 0;
void generate(int idx, int start, int nodes[]) {
    if (found) return; // stop early if clique found

    if (idx == m) {
        if (isClique(nodes))
            found = 1;
        return;
    }

    for (int v = start; v < n; v++) {
        nodes[idx] = v;
        generate(idx + 1, v + 1, nodes);
    }
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);

    int u, v;
    printf("Enter edges (u v):\n");
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &u, &v);
        G[u][v] = G[v][u] = 1;
    }

    printf("Enter clique size m: ");
    scanf("%d", &m);

    int nodes[MAX];
    generate(0, 0, nodes);

    if (found)
        printf("Yes, clique of size %d exists.\n", m);
    else
        printf("No clique of size %d exists.\n", m);

    return 0;
}
