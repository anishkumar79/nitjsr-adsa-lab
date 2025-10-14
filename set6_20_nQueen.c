#include <stdio.h>
#define N 4  // Change N for different board sizes

int board[N][N];

// Check if placing a queen at board[row][col] is safe
int isSafe(int row, int col) {
    for (int i = 0; i < col; i++) // check left row
        if (board[row][i]) return 0;
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) // upper diagonal
        if (board[i][j]) return 0;
    for (int i = row, j = col; j >= 0 && i < N; i++, j--) // lower diagonal
        if (board[i][j]) return 0;
    return 1;
}

// Solve N-Queens recursively
int solveNQ(int col) {
    if (col >= N) return 1; // all queens placed

    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;
            if (solveNQ(col + 1)) return 1;
            board[i][col] = 0; // backtrack
        }
    }
    return 0;
}

// Print board
void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

int main() {
    if (solveNQ(0))
        printBoard();
    else
        printf("Solution does not exist\n");
    return 0;
}
