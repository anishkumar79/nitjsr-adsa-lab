#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 4
#define SIZE (N*N)

typedef struct {
    int mat[N][N];
    int x, y;       // Blank tile position
    int cost;       // Cost = g(n) + h(n)
    int level;      // g(n): moves made so far
} Node;

// Goal state
int goal[N][N] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,0}
};

// Moves: up, down, left, right
int row[] = {-1,1,0,0};
int col[] = {0,0,-1,1};

// Manhattan distance heuristic
int calculateCost(int mat[N][N]) {
    int count = 0;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(mat[i][j] && mat[i][j] != goal[i][j])
                count += abs(i - (mat[i][j]-1)/N) + abs(j - (mat[i][j]-1)%N);
    return count;
}

// Copy matrix
void copyMat(int src[N][N], int dest[N][N]){
    memcpy(dest, src, SIZE*sizeof(int));
}

// Check if position is valid
int isSafe(int x, int y){
    return x>=0 && x<N && y>=0 && y<N;
}

// Solve using Branch and Bound (simple recursive)
void solve(Node node, int *minCost) {
    int cost = calculateCost(node.mat) + node.level;
    if(cost >= *minCost) return; // prune branches

    if(calculateCost(node.mat) == 0){ // goal reached
        *minCost = node.level;
        printf("Solved in %d moves\n", node.level);
        return;
    }

    for(int i=0;i<4;i++){
        int newX = node.x + row[i];
        int newY = node.y + col[i];
        if(isSafe(newX,newY)){
            Node child;
            copyMat(node.mat, child.mat);
            // swap blank with adjacent
            child.mat[node.x][node.y] = child.mat[newX][newY];
            child.mat[newX][newY] = 0;
            child.x = newX;
            child.y = newY;
            child.level = node.level + 1;
            solve(child, minCost);
        }
    }
}

int main(){
    int initial[N][N] = {
        {1,2,3,4},
        {5,6,7,8},
        {9,10,11,12},
        {13,15,14,0}
    };

    Node root;
    copyMat(initial, root.mat);
    root.level = 0;

    // Find blank position
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(root.mat[i][j]==0){ root.x=i; root.y=j; }

    int minCost = 1000;
    solve(root, &minCost);
    if(minCost == 1000) printf("No solution found\n");
    return 0;
}
