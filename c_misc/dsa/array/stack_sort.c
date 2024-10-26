#include <stdio.h>
#include <stdlib.h>

#define MAX 100  

typedef struct Stack {
    int top;
    int items[MAX];
} Stack;

void initializeStack(Stack *s) {
    s->top = -1;
}

int isEmptyStack(Stack *s) {
    return s->top == -1;
}

int isFullStack(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int value) {
    if (isFullStack(s)) {
        printf("Stack is full!\n");
        return;
    }
    s->items[++s->top] = value;
    printf("%d pushed to stack\n", value);
}

int pop(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    printf("%d popped from stack\n", s->items[s->top]);
    return s->items[s->top--];
}

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

int asc(const void *x,const void *y){
  return *(int*)x>*(int*)y;
}

 int main() {
     Stack s;
     initializeStack(&s);
     push(&s,3);
     push(&s,0);
     push(&s,9);
     push(&s,8);
     push(&s,6);
     push(&s,7);
     push(&s,8);
     push(&s,5);
     push(&s,2);
     int arr[10]={0};
     int i=-1;
     while(!isEmptyStack(&s))arr[++i]=pop(&s);
     qsort(arr,sizeof(arr)/sizeof(int),sizeof(int),asc);
     for(i=0;i<10;i++)push(&s,arr[i]);
     return 0;
 }
