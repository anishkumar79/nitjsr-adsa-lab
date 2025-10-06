#include <stdio.h>
#include <stdbool.h>

#define MAX 10
int g[MAX][MAX], n, path[MAX], plen = 0, min = 1000, max = -1;
bool vis[MAX], rec[MAX];

// DFS for directed graphs
void dfs_dir(int u) {
    vis[u] = rec[u] = true;
    path[plen++] = u;
    for (int v = 0; v < n; v++)
        if (g[u][v]) {
            if (!vis[v]) dfs_dir(v);
            else if (rec[v]) {
                int len = 0;
                for (int i = 0; i < plen; i++) if (path[i]==v) len = plen-i;
                if (len>0){ if(len<min) min=len; if(len>max) max=len; }
            }
        }
    rec[u] = false; plen--;
}

// DFS for undirected graphs (avoid parent edge)
void dfs_undir(int u, int parent) {
    vis[u] = true; path[plen++] = u;
    for (int v=0; v<n; v++)
        if (g[u][v]) {
            if (!vis[v]) dfs_undir(v, u);
            else if (v != parent) { // back edge
                int len=0; for(int i=0;i<plen;i++) if(path[i]==v) len=plen-i;
                if(len>0){ if(len<min) min=len; if(len>max) max=len; }
            }
        }
    plen--;
}

int main() {
    int choice;
    printf("Vertices: "); scanf("%d",&n);
    printf("Directed(1) or Undirected(2)? "); scanf("%d",&choice);
    printf("Adjacency matrix:\n");
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) scanf("%d",&g[i][j]);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++) vis[j]=rec[j]=false; plen=0;
        if(choice==1) dfs_dir(i);
        else dfs_undir(i,-1);
    }

    if(min==1000) printf("No cycles\n");
    else printf("Smallest cycle: %d\nLargest cycle: %d\n", min, max);
}
