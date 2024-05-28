#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#define MAX_SIZE 100

typedef struct CircularQueue {
    int front, rear;
    int items[MAX_SIZE];
} CircularQueue;

void initializeQueue(CircularQueue *q);
int isEmptyQueue(CircularQueue *q);
int isFullQueue(CircularQueue *q);
void enqueue(CircularQueue *q, int value);
int dequeue(CircularQueue *q);
void displayQueue(CircularQueue *q);

#endif /* CIRCULAR_QUEUE_H */
