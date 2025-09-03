#include <stdio.h>
#include <stdlib.h>

typedef struct { int l, r, mid, phase; } Frame;

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int)), *R = malloc(n2 * sizeof(int));
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void mergeSortIter(int arr[], int n) {
    Frame *stack = malloc(n * sizeof(Frame));
    int top = -1;
    stack[++top] = (Frame){0, n - 1, 0, 0};
    while (top >= 0) {
        Frame f = stack[top--];
        if (f.l >= f.r) continue;
        if (f.phase == 0) {
            f.mid = (f.l + f.r) / 2;
            stack[++top] = (Frame){f.l, f.r, f.mid, 1};
            stack[++top] = (Frame){f.mid + 1, f.r, 0, 0};
            stack[++top] = (Frame){f.l, f.mid, 0, 0};
        } else merge(arr, f.l, f.mid, f.r);
    }
    free(stack);
}

int main() {
    int arr[] = {38,27,43,3,9,82,10}, n = 7;
    mergeSortIter(arr, n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
}
