#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int* array;
    int count;
    int capacity;
    int heap_type;
} Heap;

Heap* createHeap(int capacity, int heap_type) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->heap_type = heap_type;
    heap->count = 0;
    heap->capacity = capacity;
    heap->array = (int*)malloc(sizeof(int) * heap->capacity);
    return heap;
}

int parent(Heap* heap, int i) {
    if (i <= 0 || i >= heap->count) {
        return -1;
    }
    return (i - 1) / 2;
}

int leftChild(Heap* heap, int i) {
    int left = 2 * i + 1;
    if (left >= heap->count) {
        return -1;
    }
    return left;
}

int rightChild(Heap* heap, int i) {
    int right = 2 * i + 2;
    if (right >= heap->count) {
        return -1;
    }
    return right;
}

int getMax(Heap* heap) {
    if (heap->count == 0) {
        return -1;
    }
    return heap->array[0];
}

void percolateDown(Heap* heap, int i) {
    int l, r, max, temp;
    l = leftChild(heap, i);
    r = rightChild(heap, i);

    if (l != -1 && heap->array[l] > heap->array[i]) {
        max = l;
    } else {
        max = i;
    }

    if (r != -1 && heap->array[r] > heap->array[max]) {
        max = r;
    }

    if (max != i) {
        temp = heap->array[i];
        heap->array[i] = heap->array[max];
        heap->array[max] = temp;
        percolateDown(heap, max);
    }
}

int deleteMax(Heap* heap) {
    if (heap->count == 0) {
        return -1;
    }
    int data = heap->array[0];
    heap->array[0] = heap->array[heap->count - 1];
    heap->count--;
    percolateDown(heap, 0);
    return data;
}

void resizeHeap(Heap* heap) {
    int* array_old = heap->array;
    heap->array = (int*)malloc(sizeof(int) * heap->capacity * 2);
    for (int i = 0; i < heap->capacity; i++) {
        heap->array[i] = array_old[i];
    }
    heap->capacity *= 2;
    free(array_old);
}

void insert(Heap* heap, int data) {
    if (heap->count == heap->capacity) {
        resizeHeap(heap);
    }
    heap->count++;
    int i = heap->count - 1;
    while (i > 0 && data > heap->array[(i - 1) / 2]) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = data;
}

void destroyHeap(Heap* heap) {
    if (heap == NULL) {
        return;
    }
    if (heap->array != NULL) {
        free(heap->array);
    }
    free(heap);
}

int main() {
    Heap* heap = createHeap(1, 0);
    insert(heap, 10);
    insert(heap, 20);
    insert(heap, 15);
    insert(heap, 40);
    insert(heap, 50);
    insert(heap, 100);
    insert(heap, 25);
    insert(heap, 45);
    insert(heap, 12);
    insert(heap, 6);
    insert(heap, 8);
    insert(heap, 35);
    insert(heap, 5);
    insert(heap, 2);
    insert(heap, 1);
    insert(heap, 3);
    insert(heap, 4);
    insert(heap, 7);
    insert(heap, 9);
    insert(heap, 11);
    insert(heap, 13);
    insert(heap, 14);
    insert(heap, 16);
    insert(heap, 17);
    insert(heap, 18);
    insert(heap, 19);
    insert(heap, 21);
    insert(heap, 22);
    insert(heap, 23);
    insert(heap, 24);
    insert(heap, 26);
    insert(heap, 27);
    insert(heap, 28);
    insert(heap, 29);
    insert(heap, 30);
    insert(heap, 31);
    insert(heap, 32);
    insert(heap, 33);
    insert(heap, 34);
    insert(heap, 36);
    insert(heap, 37);
    insert(heap, 38);
    insert(heap, 39);
    insert(heap, 41);
    insert(heap, 42);
    insert(heap, 43);
    insert(heap, 44);
    insert(heap, 46);
    insert(heap, 47);
    insert(heap, 48);
    insert(heap, 49);
    insert(heap, 51);
    insert(heap, 52);
    insert(heap, 53);
    insert(heap, 54);
    insert(heap, 55);
    insert(heap, 56);
    insert(heap, 57);
    insert(heap, 58);
    insert(heap, 59);
    insert(heap, 60);
    insert(heap, 61);
    insert(heap, 62);
    insert(heap, 63);
    insert(heap, 64);
    insert(heap, 65);
    insert(heap, 66);
    insert(heap, 67);
    insert(heap, 68);
    insert(heap, 69);

    printf("Max: %d\n", getMax(heap));
    printf("Deleted: %d\n", deleteMax(heap));
    printf("Max: %d\n", getMax(heap));
    printf("Deleted: %d\n", deleteMax(heap));
    printf("Max: %d\n", getMax(heap));
    printf("Deleted: %d\n", deleteMax(heap));
    printf("Max: %d\n", getMax(heap));

    destroyHeap(heap);
    return 0;
}
