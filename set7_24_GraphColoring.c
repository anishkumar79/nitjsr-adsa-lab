#include <stdio.h>
#define V 4 // Number of vertices

// Check if it is safe to color vertex v with color c
int isSafe(int v, int graph[V][V], int color[], int c) {
    for(int i=0;i<V;i++)
        if(graph[v][i] && color[i]==c) return 0;
    return 1;
}

// Recursive function to solve graph coloring
int graphColoringUtil(int graph[V][V], int m, int color[], int v) {
    if(v == V) return 1; // All vertices colored

    for(int c=1;c<=m;c++){
        if(isSafe(v, graph, color, c)){
            color[v]=c;
            if(graphColoringUtil(graph, m, color, v+1)) return 1;
            color[v]=0; // backtrack
        }
    }
    return 0;
}

void graphColoring(int graph[V][V], int m){
    int color[V] = {0};
    if(graphColoringUtil(graph, m, color, 0)){
        printf("Colors assigned: ");
        for(int i=0;i<V;i++) printf("%d ", color[i]);
        printf("\n");
    } else
        printf("No solution exists\n");
}

int main(){
    int graph[V][V] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };
    int m = 3; // Number of colors
    graphColoring(graph, m);
    return 0;
}
