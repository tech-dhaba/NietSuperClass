#include<stdio.h>

typedef struct node{
    char* data;
    struct node *left;
    struct node *right;
}node;

node* create_node(char* data){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void push(node* stack[],int* top,node* data){
    stack[++(*top)] = data;
}

node* pop(node* stack[],int* top){
    return stack[(*top)--];
}

int is_empty(int top){
    return top == -1;
}

