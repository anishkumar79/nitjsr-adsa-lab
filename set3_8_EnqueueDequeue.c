#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int data[SIZE];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

int isFull(Queue *q) {
    return q->rear == SIZE - 1;
}

void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->data[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int value = q->data[q->front++];
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return value;
}

// Stack using two queues
typedef struct {
    Queue q1;
    Queue q2;
} Stack;

void initStack(Stack *s) {
    initQueue(&s->q1);
    initQueue(&s->q2);
}

void pushCostlyEnqueue(Stack *s, int value) {
    // Enqueue to q2
    enqueue(&s->q2, value);

    // Move all elements from q1 to q2
    while (!isEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Swap q1 and q2
    Queue temp = s->q1;
    s->q1 = s->q2;
    s->q2 = temp;
}

int popCostlyEnqueue(Stack *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty\n");
        return -1;
    }
    return dequeue(&s->q1);
}
void pushCostlyDequeue(Stack *s, int value) {
    enqueue(&s->q1, value);
}

int popCostlyDequeue(Stack *s) {
    if (isEmpty(&s->q1)) {
        printf("Stack is empty\n");
        return -1;
    }
}

    // Move all but last element to q2
int main() {
    Stack s;
    initStack(&s);

    // Method 1
    pushCostlyEnqueue(&s, 10);
    pushCostlyEnqueue(&s, 20);
    pushCostlyEnqueue(&s, 30);
    printf("Popped (Method 1): %d\n", popCostlyEnqueue(&s));

    // Method 2
    pushCostlyDequeue(&s, 40);
    pushCostlyDequeue(&s, 50);
    printf("Popped (Method 2): %d\n", popCostlyDequeue(&s));
    printf("Popped (Method 2): %d\n", popCostlyDequeue(&s));

    return 0;
}
