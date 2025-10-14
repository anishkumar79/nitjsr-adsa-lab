#include <stdio.h>

int maxVal = 0; // Global variable to store maximum value

void knapsackBT(int W, int wt[], int val[], int n, int i, int currW, int currVal) {
    // Base case: all items considered or capacity full
    if (i == n) {
        if (currVal > maxVal)
            maxVal = currVal;
        return;
    }

    // Case 1: Skip current item
    knapsackBT(W, wt, val, n, i + 1, currW, currVal);

    // Case 2: Include current item (if it fits)
    if (currW + wt[i] <= W)
        knapsackBT(W, wt, val, n, i + 1, currW + wt[i], currVal + val[i]);
}

int main() {
    int val[] = {1, 2, 3};
    int wt[]  = {4, 5, 1};
    int W = 4;
    int n = sizeof(val) / sizeof(val[0]);

    knapsackBT(W, wt, val, n, 0, 0, 0);
    printf("Maximum value (Backtracking) = %d\n", maxVal);
    return 0;
}
