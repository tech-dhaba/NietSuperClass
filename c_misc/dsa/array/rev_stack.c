#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Define the maximum size of the stack

typedef struct Stack {
    int top;
    int items[MAX];
} Stack;

// Initialize the stack
void initializeStack(Stack *s) {
    s->top = -1;
}

// Check if the stack is empty
int isEmptyStack(Stack *s) {
    return s->top == -1;
}

// Check if the stack is full
int isFullStack(Stack *s) {
    return s->top == MAX - 1;
}

// Push an element
void push(Stack *s, int value) {
    if (isFullStack(s)) {
        printf("Stack is full!\n");
        return;
    }
    s->items[++s->top] = value;
    printf("%d pushed to stack\n", value);
}

// Pop an element
int pop(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    printf("%d popped from stack\n", s->items[s->top]);
    return s->items[s->top--];
}

// Display the stack
void displayStack(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%d ", s->items[i]);
    }
    printf("\n");
}

// int main() {
//     Stack s;
//     initializeStack(&s);

//     push(&s, 10);
//     push(&s, 20);
//     push(&s, 30);
//     push(&s, 40);
//     push(&s, 50);

//     displayStack(&s);

//     pop(&s);
//     pop(&s);

//     displayStack(&s);

//     push(&s, 60);
//     push(&s, 70);

//     displayStack(&s);

//     return 0;
// }