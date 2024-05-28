#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Queue {
    int front, rear;
    int items[MAX];
} Queue;

// Initialize the queue
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
int isEmpty(Queue *q) {
    return q->front == -1;
}

// Check if the queue is full
int isFull(Queue *q) {
    return q->rear == MAX - 1;
}

// Enqueue an element
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
    printf("%d enqueued to queue\n", value);
}

// Dequeue an element
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front >= q->rear) {
        // Queue has only one element, so we reset the queue after dequeue
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    printf("%d dequeued from queue\n", value);
    return value;
}

// Display the queue
void displayQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements are: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->items[i]);
    }
    printf("\n");
}

int main() {
    Queue q;
    initializeQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);

    displayQueue(&q);

    dequeue(&q);
    dequeue(&q);

    displayQueue(&q);

    return 0;
}
