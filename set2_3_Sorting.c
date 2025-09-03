#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Utility to print array */
void printArray(int arr[], int n) {
    for (int i=0;i<n;i++) printf("%d ",arr[i]);
    printf("\n");
}

/* (i) Insertion Sort */
void insertionSort(int arr[], int n) {
    for (int i=1;i<n;i++) {
        int key=arr[i];
        int j=i-1;
        while(j>=0 && arr[j]>key) {
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=key;
    }
}

/* (ii) Bubble Sort */
void bubbleSort(int arr[], int n) {
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                int t=arr[j]; arr[j]=arr[j+1]; arr[j+1]=t;
            }
        }
    }
}

/* (iii) Selection Sort */
void selectionSort(int arr[], int n) {
    for(int i=0;i<n-1;i++){
        int minIdx=i;
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[minIdx]) minIdx=j;
        }
        int t=arr[i]; arr[i]=arr[minIdx]; arr[minIdx]=t;
    }
}

/* (iv) Shell Sort */
void shellSort(int arr[], int n) {
    for(int gap=n/2;gap>0;gap/=2){
        for(int i=gap;i<n;i++){
            int temp=arr[i];
            int j=i;
            while(j>=gap && arr[j-gap]>temp){
                arr[j]=arr[j-gap];
                j-=gap;
            }
            arr[j]=temp;
        }
    }
}

/* (v) Quick Sort */
int partition(int arr[],int low,int high){
    int pivot=arr[high];
    int i=low-1;
    for(int j=low;j<high;j++){
        if(arr[j]<pivot){
            i++;
            int t=arr[i]; arr[i]=arr[j]; arr[j]=t;
        }
    }
    int t=arr[i+1]; arr[i+1]=arr[high]; arr[high]=t;
    return i+1;
}
void quickSort(int arr[],int low,int high){
    if(low<high){
        int pi=partition(arr,low,high);
        quickSort(arr,low,pi-1);
        quickSort(arr,pi+1,high);
    }
}

/* (vi) Merge Sort */
void merge(int arr[],int l,int m,int r){
    int n1=m-l+1,n2=r-m;
    int *L=(int*)malloc(n1*sizeof(int));
    int *R=(int*)malloc(n2*sizeof(int));
    for(int i=0;i<n1;i++) L[i]=arr[l+i];
    for(int j=0;j<n2;j++) R[j]=arr[m+1+j];
    int i=0,j=0,k=l;
    while(i<n1 && j<n2){
        if(L[i]<=R[j]) arr[k++]=L[i++];
        else arr[k++]=R[j++];
    }
    while(i<n1) arr[k++]=L[i++];
    while(j<n2) arr[k++]=R[j++];
    free(L); free(R);
}
void mergeSort(int arr[],int l,int r){
    if(l<r){
        int m=(l+r)/2;
        mergeSort(arr,l,m);
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r);
    }
}

/* (vii) Heap Sort */
void heapify(int arr[],int n,int i){
    int largest=i,l=2*i+1,r=2*i+2;
    if(l<n && arr[l]>arr[largest]) largest=l;
    if(r<n && arr[r]>arr[largest]) largest=r;
    if(largest!=i){
        int t=arr[i]; arr[i]=arr[largest]; arr[largest]=t;
        heapify(arr,n,largest);
    }
}
void heapSort(int arr[],int n){
    for(int i=n/2-1;i>=0;i--) heapify(arr,n,i);
    for(int i=n-1;i>0;i--){
        int t=arr[0]; arr[0]=arr[i]; arr[i]=t;
        heapify(arr,i,0);
    }
}

/* (viii) Radix Sort */
int getMax(int arr[],int n){
    int mx=arr[0];
    for(int i=1;i<n;i++) if(arr[i]>mx) mx=arr[i];
    return mx;
}
void countingSortForRadix(int arr[],int n,int exp){
    int *output=(int*)malloc(n*sizeof(int));
    int count[10]={0};
    for(int i=0;i<n;i++) count[(arr[i]/exp)%10]++;
    for(int i=1;i<10;i++) count[i]+=count[i-1];
    for(int i=n-1;i>=0;i--){
        output[count[(arr[i]/exp)%10]-1]=arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for(int i=0;i<n;i++) arr[i]=output[i];
    free(output);
}
void radixSort(int arr[],int n){
    int m=getMax(arr,n);
    for(int exp=1;m/exp>0;exp*=10)
        countingSortForRadix(arr,n,exp);
}

/* (ix) Counting Sort (non-negative) */
void countingSort(int arr[],int n){
    int max=arr[0];
    for(int i=1;i<n;i++) if(arr[i]>max) max=arr[i];
    int *count=(int*)calloc(max+1,sizeof(int));
    for(int i=0;i<n;i++) count[arr[i]]++;
    int idx=0;
    for(int i=0;i<=max;i++){
        while(count[i]--) arr[idx++]=i;
    }
    free(count);
}

/* (x) Bucket Sort */
void bucketSort(int arr[],int n){
    if(n<=0) return;
    int max=arr[0];
    for(int i=1;i<n;i++) if(arr[i]>max) max=arr[i];
    int bucketCount=n;
    int **buckets=(int**)malloc(bucketCount*sizeof(int*));
    int *bucketSizes=(int*)calloc(bucketCount,sizeof(int));
    for(int i=0;i<bucketCount;i++)
        buckets[i]=(int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++){
        int bi=(long long)arr[i]*bucketCount/(max+1);
        buckets[bi][bucketSizes[bi]++]=arr[i];
    }
    int idx=0;
    for(int i=0;i<bucketCount;i++){
        // simple insertion sort inside bucket
        for(int j=1;j<bucketSizes[i];j++){
            int key=buckets[i][j];
            int k=j-1;
            while(k>=0 && buckets[i][k]>key){
                buckets[i][k+1]=buckets[i][k];
                k--;
            }
            buckets[i][k+1]=key;
        }
        for(int j=0;j<bucketSizes[i];j++) arr[idx++]=buckets[i][j];
        free(buckets[i]);
    }
    free(buckets); free(bucketSizes);
}

/* (xi) Radix Exchange Sort (MSD binary) */
void radixExchangeSort(int arr[],int left,int right,int bit){
    if(left>=right || bit<0) return;
    int i=left,j=right;
    while(i<=j){
        while(i<=right && ((arr[i]>>bit)&1)==0) i++;
        while(j>=left && ((arr[j]>>bit)&1)==1) j--;
        if(i<j){
            int t=arr[i]; arr[i]=arr[j]; arr[j]=t;
        }
    }
    radixExchangeSort(arr,left,j,bit-1);
    radixExchangeSort(arr,i,right,bit-1);
}

/* (xii) Address Calculation Sort (Hash/Bucket idea) */
void addressCalculationSort(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];

    int **table = malloc(n * sizeof(int*));
    int *size = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) table[i] = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        int idx = (long long)arr[i] * n / (max + 1);
        table[idx][size[idx]++] = arr[i];
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        // insertion sort
        for (int j = 1; j < size[i]; j++) {
            int x = table[i][j], l = j - 1;
            while (l >= 0 && table[i][l] > x) table[i][l + 1] = table[i][l--];
            table[i][l + 1] = x;
        }
        for (int j = 0; j < size[i]; j++) arr[k++] = table[i][j];
        free(table[i]);
    }
    free(table); free(size);
}


/* Driver */
int main(){
    int arr[]={34,7,23,32,5,62};
    int n=sizeof(arr)/sizeof(arr[0]);

    int tmp[100];

    memcpy(tmp,arr,sizeof(arr)); insertionSort(tmp,n); printf("Insertion: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); bubbleSort(tmp,n); printf("Bubble: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); selectionSort(tmp,n); printf("Selection: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); shellSort(tmp,n); printf("Shell: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); quickSort(tmp,0,n-1); printf("Quick: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); mergeSort(tmp,0,n-1); printf("Merge: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); heapSort(tmp,n); printf("Heap: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); radixSort(tmp,n); printf("Radix: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); countingSort(tmp,n); printf("Counting: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); bucketSort(tmp,n); printf("Bucket: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); radixExchangeSort(tmp,0,n-1,31); printf("Radix Exchange: "); printArray(tmp,n);
    memcpy(tmp,arr,sizeof(arr)); addressCalculationSort(tmp,n); printf("Address Calc: "); printArray(tmp,n);

    return 0;
}
