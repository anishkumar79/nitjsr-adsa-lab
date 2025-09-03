#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

typedef struct {
    int data[SIZE];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int isFull(Stack *s) {
    return s->top == SIZE - 1;
}

void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->data[++s->top] = value;
}

int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->data[s->top--];
}

int peek(Stack *s) {
    if (isEmpty(s)) return -1;
    return s->data[s->top];
}

// Queue using two stacks
typedef struct {
    Stack stack1;
    Stack stack2;
} Queue;

void initQueue(Queue *q) {
    init(&q->stack1);
    init(&q->stack2);
}

void enqueueCostlyPush(Queue *q, int value) {
    // Move all elements to stack2
    while (!isEmpty(&q->stack1)) {
        push(&q->stack2, pop(&q->stack1));
    }

    // Push new element to stack1
    push(&q->stack1, value);

    // Move everything back to stack1
    while (!isEmpty(&q->stack2)) {
        push(&q->stack1, pop(&q->stack2));
    }
}

int dequeueCostlyPush(Queue *q) {
    if (isEmpty(&q->stack1)) {
        printf("Queue is empty\n");
        return -1;
    }
    return pop(&q->stack1);
}
void enqueueCostlyPop(Queue *q, int value) {
    push(&q->stack1, value);
}

int dequeueCostlyPop(Queue *q) {
    if (isEmpty(&q->stack2)) {
        while (!isEmpty(&q->stack1)) {
            push(&q->stack2, pop(&q->stack1));
        }
    }

    if (isEmpty(&q->stack2)) {
        printf("Queue is empty\n");
        return -1;
    }

    return pop(&q->stack2);
}
int main() {
    Queue q;
    initQueue(&q);

    // Method 1
    enqueueCostlyPush(&q, 10);
    enqueueCostlyPush(&q, 20);
    enqueueCostlyPush(&q, 30);
    printf("Dequeued (Method 1): %d\n", dequeueCostlyPush(&q));

    // Method 2
    enqueueCostlyPop(&q, 40);
    enqueueCostlyPop(&q, 50);
    printf("Dequeued (Method 2): %d\n", dequeueCostlyPop(&q));
    printf("Dequeued (Method 2): %d\n", dequeueCostlyPop(&q));

    return 0;
}
