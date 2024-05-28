#include <stdio.h>
#include "circular_queue.h"

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