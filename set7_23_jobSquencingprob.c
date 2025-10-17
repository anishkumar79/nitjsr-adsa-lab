#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char id;
    int deadline;
    int profit;
} Job;

// Comparison function to sort jobs in descending order of profit
int cmp(const void *a, const void *b) {
    return ((Job*)b)->profit - ((Job*)a)->profit;
}

// Job Sequencing Function
void jobSequencing(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), cmp); // sort by profit

    int result[n];       // To store result (job indices)
    int slot[n];         // Slot availability (0 = free)
    for(int i=0;i<n;i++) slot[i]=0;

    for(int i=0;i<n;i++) {
        for(int j = (jobs[i].deadline-1 < n ? jobs[i].deadline-1 : n-1); j>=0; j--) {
            if(slot[j]==0) {   // free slot
                slot[j]=1;
                result[j]=i;
                break;
            }
        }
    }

    printf("Scheduled Jobs: ");
    for(int i=0;i<n;i++)
        if(slot[i]) printf("%c ", jobs[result[i]].id);
    printf("\n");
}

// Driver code
int main() {
    Job jobs[] = {{'A', 2, 100}, {'B', 1, 19}, {'C', 2, 27}, {'D', 1, 25}, {'E', 3, 15}};
    int n = sizeof(jobs)/sizeof(jobs[0]);
    jobSequencing(jobs, n);
    return 0;
}
