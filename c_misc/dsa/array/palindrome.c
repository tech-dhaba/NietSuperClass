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
    //printf("%c pushed to stack\n", value);
}

int pop(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    //printf("%c popped from stack\n", s->items[s->top]);
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

 int main() {
     Stack s;
     initializeStack(&s);
     char *str="sabccbas";
     for(int i=0;str[i]!='\0';i++)push(&s,str[i]);
     for(int i=0;str[i]!='\0';i++){
       if(pop(&s)!=str[i]){
         printf("not palindrome");
         return 0;
       }
     }
     printf("palindrome");
     return 0;
 }
