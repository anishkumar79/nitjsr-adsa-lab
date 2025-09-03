#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct{
    Node *rear;
}CQueue;

void init(CQueue *q){ q->rear=NULL; }
int isEmpty(CQueue *q){ return q->rear==NULL; }

void enqueue(CQueue *q,int x){
    Node* t=malloc(sizeof(Node));
    t->data=x;
    if(isEmpty(q)){ t->next=t; q->rear=t; }
    else{ t->next=q->rear->next; q->rear->next=t; q->rear=t; }
}
int dequeue(CQueue *q){
    if(isEmpty(q)) return printf("Queue Empty\n"),-1;
    Node *f=q->rear->next; int x=f->data;
    if(f==q->rear) q->rear=NULL;
    else q->rear->next=f->next;
    free(f); return x;
}
void display(CQueue *q){
    if(isEmpty(q)) return;
    Node* p=q->rear->next;
    do{ printf("%d ",p->data); p=p->next; }while(p!=q->rear->next);
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
