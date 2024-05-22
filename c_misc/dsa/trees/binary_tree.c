#include<stdio.h>
#include<stdlib.h>
#define p(x) printf("%d\n", x)
#define pf(x) printf("%f\n", x)
#define ps(x) printf("%s", x)
#define s(x) scanf("%d", &x)

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}node;

node *create_node(int data){
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void inorder(node *root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    p(root->data);
    inorder(root->right);
}

void preorder(node *root){
    if(root == NULL){
        return;
    }
    p(root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(node *root){
    if(root == NULL){
        return;
    }
    postorder(root->left);
    postorder(root->right);
    p(root->data);
}

void level_order(node *root){
    if(root == NULL){
        return;
    }
    node *queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while(front < rear){
        node *current = queue[front++];
        p(current->data);
        if(current->left != NULL){
            queue[rear++] = current->left;
        }
        if(current->right != NULL){
            queue[rear++] = current->right;
        }
    }
}

void iterative_inorder(node *root){
    node *stack[100];
    int top = -1;
    node *current = root;
    while(current != NULL || top != -1){
        while(current != NULL){
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        p(current->data);
        current = current->right;
    }
}

void iterative_preorder(node *root){
    node* stack[100];
    int top = -1;
    stack[++top] = root;
    while(top != -1){
        node *current = stack[top--];
        p(current->data);
        if(current->right != NULL){
            stack[++top] = current->right;
        }
        if(current->left != NULL){
            stack[++top] = current->left;
        }
    }
}

void iterative_postorder(node *root){
    node *queue[100];
    int front = 0, rear = 0;
    node *current = root;
    while(current != NULL || front != rear){
        while(current != NULL){
            queue[rear++] = current;
            current = current->left;
        }
        node *temp = queue[rear-1];
        if(temp->right == NULL){
            p(temp->data);
            rear--;
        }else{
            current = temp->right;
        }
    }
}

void insert(node *root, int data){
    node *new_node = create_node(data);
    node *temp = root;
    node *prev = NULL;
    while(temp != NULL){
        prev = temp;
        if(data < temp->data){
            temp = temp->left;
        }else{
            temp = temp->right;
        }
    }
    if(data < prev->data){
        prev->left = new_node;
    }else{
        prev->right = new_node;
    }
}

int main(void){
    node *root = create_node(10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 3);
    insert(root, 7);
    insert(root, 12);
    insert(root, 18);
    ps("Inorder: ");
    inorder(root);
    ps("Preorder: ");
    preorder(root);
    ps("Postorder: ");
    postorder(root);
    ps("Level order: ");
    level_order(root);

return 0;
}