#include <stdio.h>
#define MAX 5

typedef struct {
    int arr[MAX], front, rear;
} CQueue;

void init(CQueue *q){ q->front = q->rear = -1; }
int isFull(CQueue *q){ return (q->front == (q->rear+1)%MAX); }
int isEmpty(CQueue *q){ return (q->front == -1); }

void enqueue(CQueue *q,int x){
    if(isFull(q)) return printf("Queue Full\n");
    if(isEmpty(q)) q->front=0;
    q->rear=(q->rear+1)%MAX;
    q->arr[q->rear]=x;
}
int dequeue(CQueue *q){
    if(isEmpty(q)) return printf("Queue Empty\n"),-1;
    int x=q->arr[q->front];
    if(q->front==q->rear) q->front=q->rear=-1;
    else q->front=(q->front+1)%MAX;
    return x;
}
void display(CQueue *q){
    if(isEmpty(q)) return;
    int i=q->front;
    while(1){
        printf("%d ",q->arr[i]);
        if(i==q->rear) break;
        i=(i+1)%MAX;
    }
    printf("\n");
}

int main(){
    CQueue q; init(&q);
    enqueue(&q,10); enqueue(&q,20); enqueue(&q,30); enqueue(&q,40);
    display(&q);
    dequeue(&q); dequeue(&q);
    display(&q);
    enqueue(&q,50); enqueue(&q,60);
    display(&q);
}
