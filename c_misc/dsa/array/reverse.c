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
    //printf("%c", value);
}

int pop(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty!\n");
        return -1;
    }
    printf("%c", s->items[s->top]);
    return s->items[s->top--];
}

void displayStack(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= s->top; i++) {
        printf("%c", s->items[i]);
    }
    printf("\n");
}

void rev(Stack *s1,Stack *s2){
  if(isEmptyStack(s1))return;
  push(s2,pop(s1));
  rev(s1,s2);
}

 int main() {
     Stack s1,s2;
     initializeStack(&s1);
     initializeStack(&s2);
     char *str="hello";
     for(int i=0;str[i]!='\0';i++)push(&s1,str[i]);
     displayStack(&s1);
     rev(&s1,&s2);
     displayStack(&s2);
     return 0;
 }
