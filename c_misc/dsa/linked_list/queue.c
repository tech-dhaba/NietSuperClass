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

void enqueue(node** const front,node** const rear,const int data){
    node* n=create(data);
    if(*front==NULL){
        *front=n;
        *rear=n;
        return;
    }
    (*rear)->next=n;
    *rear=n;
}

int dequeue(node** const front,node** const rear){
    if(*front==NULL){
        ps("Queue is empty\n");
        return -1;
    }
    node* temp=*front;
    *front=(*front)->next;
    int data=temp->data;
    free(temp);
    return data;
}

int peek(node* const front){
    if(front==NULL){
        ps("Queue is empty\n");
        return -1;
    }
    return front->data;
}

int isEmpty(node* const front){
    return front==NULL;
}


int main(void){
    node* front,*rear;
    front=rear=NULL;
    p(isEmpty(front));
    enqueue(&front,&rear, 1);
    enqueue(&front,&rear, 2);
    enqueue(&front,&rear, 3);
    p(peek(front));
    p(dequeue(&front,&rear));
    p(peek(front));
    p(dequeue(&front,&rear));
    p(peek(front));
    p(dequeue(&front,&rear));
    p(isEmpty(front));


return 0;
}