#include<stdio.h>
#include<stdlib.h>
#define p(x) printf("%d\n", x)
#define pf(x) printf("%f\n", x)
#define ps(x) printf("%s", x)
#define s(x) scanf("%d", &x)

typedef struct node{
    int data;
    struct node *next;
}node;

node* create(int data) {
    node* new = (node*)malloc(sizeof(node));
    if (new == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new->data = data; // Set the data of the new node
    new->next = NULL; // Initialize the next pointer to NULL
    return new;
}

node* push(node** const top,const int data){
    node* n=create(data);
    n->next=*top;
    *top=n;
    return n;
}

int pop(node** const top){
    if(*top==NULL){
        ps("Stack is empty\n");
        return -1;
    }
    node* temp=*top;
    *top=(*top)->next;
    int data=temp->data;
    free(temp);
    return data;
}

int peek(node* const top){
    if(top==NULL){
        ps("Stack is empty\n");
        return -1;
    }
    return top->data;
}

int isEmpty(node* const top){
    return top==NULL;
}


int main(void){
    node* top=NULL;
    // p(isEmpty(top));
    push(&top, 1);
    push(&top, 2);
    push(&top, 3);
    p(peek(top));
    p(pop(&top));
    p(peek(top));
    p(pop(&top));
    p(peek(top));
    p(pop(&top));
    p(isEmpty(top));
    p(pop(&top));

return 0;
}