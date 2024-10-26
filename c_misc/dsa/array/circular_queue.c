#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Define the maximum size of the queue

typedef struct CircularQueue {
    int front, rear;
    int items[MAX];
} CircularQueue;

// Initialize the queue
void initializeQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
int isEmptyQueue(CircularQueue *q) {
    return q->front == -1;
}

// Check if the queue is full
int isFullQueue(CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

// Enqueue an element
void enqueue(CircularQueue *q, int value) {
    if (isFullQueue(q)) {
        printf("Queue is full!\n");
        return;
    }
    if (isEmptyQueue(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX;
    q->items[q->rear] = value;
    printf("%d enqueued to queue\n", value);
}

// Dequeue an element
int dequeue(CircularQueue *q) {
    if (isEmptyQueue(q)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear) {
        // Queue has only one element, reset after dequeue
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX;
    }
    printf("%d dequeued from queue\n", value);
    return value;
}

// Display the queue
void displayQueue(CircularQueue *q) {
    if (isEmptyQueue(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue elements are: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->items[i]);
        if (i == q->rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    CircularQueue q;
    initializeQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    displayQueue(&q);

    dequeue(&q);
    dequeue(&q);

    displayQueue(&q);

    enqueue(&q, 60);
    enqueue(&q, 70);

    displayQueue(&q);

    return 0;
}
