#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

typedef struct Node {
    int mat[N][N];
    int x, y;           
    int cost, level;     
    struct Node* parent; 
} Node;

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = malloc(sizeof(Node));
    memcpy(node->mat, mat, sizeof(node->mat));
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = 0;
    node->x = newX; node->y = newY;
    node->level = level;
    node->parent = parent;
    return node;
}

int calculateCost(int mat[N][N], int final[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] && mat[i][j] != final[i][j])
                cost++;
    return cost;
}

void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

void printPath(Node* node) {
    if (!node) return;
    printPath(node->parent);
    printMatrix(node->mat);
}

int comparator(const void* a, const void* b) {
    Node* n1 = *(Node**)a; Node* n2 = *(Node**)b;
    return (n1->cost + n1->level) - (n2->cost + n2->level);
}

void solve(int initial[N][N], int x, int y, int final[N][N]) {
    Node* pq[10000]; int size = 0;
    Node* root = malloc(sizeof(Node));
    memcpy(root->mat, initial, sizeof(root->mat));
    root->x = x; root->y = y; root->level = 0;
    root->cost = calculateCost(initial, final);
    root->parent = NULL;
    pq[size++] = root;

    int moves[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (size) {
        qsort(pq, size, sizeof(Node*), comparator);
        Node* curr = pq[0];
        if (curr->cost == 0) {
            printf("Solution at level %d:\n", curr->level);
            printPath(curr);
            return;
        }
        for (int i = 0; i < size - 1; i++) pq[i] = pq[i+1];
        size--;

        for (int i = 0; i < 4; i++) {
            int nx = curr->x + moves[i][0], ny = curr->y + moves[i][1];
            if (nx >= 0 && nx < N && ny >= 0 && ny < N) {
                Node* child = newNode(curr->mat, curr->x, curr->y, nx, ny, curr->level + 1, curr);
                child->cost = calculateCost(child->mat, final);
                pq[size++] = child;
            }
        }
    }
    printf("No solution found.\n");
}

int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };
    int final[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };
    int x, y;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
        if (initial[i][j] == 0) { x = i; y = j; }

    solve(initial, x, y, final);
    return 0;
}
