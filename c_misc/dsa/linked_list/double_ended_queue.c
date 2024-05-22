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

void enqueue_front(node** const front,node** const rear,const int data){
    node* n=create(data);
    if(*front==NULL){
        *front=n;
        *rear=n;
        return;
    }
    n->next=*front;
    *front=n;
}

void enqueue_rear(node** const front,node** const rear,const int data){
    node* n=create(data);
    if(*front==NULL){
        *front=n;
        *rear=n;
        return;
    }
    (*rear)->next=n;
    *rear=n;
}

int dequeue_front(node** const front,node** const rear){
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

int dequeue_rear(node** const front,node** const rear){
    if(*front==NULL){
        ps("Queue is empty\n");
        return -1;
    }
    node* temp=*front;
    while(temp->next!=*rear){
        temp=temp->next;
    }
    int data=(*rear)->data;
    free(*rear);
    if(temp==*front){
        *front=NULL;
        *rear=NULL;
        return data;
    }
    *rear=temp;
    temp->next=NULL;
    return data;
}

int peek_front(node* const front){
    if(front==NULL){
        ps("Queue is empty\n");
        return -1;
    }
    return front->data;
}

int peek_rear(node* const rear){
    if(rear==NULL){
        ps("Queue is empty\n");
        return -1;
    }
    return rear->data;
}

int isEmpty(node* const front){
    return front==NULL;
}

int main(void){
    node* front,*rear;
    front=rear=NULL;
    p(isEmpty(front));//1
    enqueue_front(&front,&rear, 1);//1
    enqueue_front(&front,&rear, 2);//2 1
    enqueue_front(&front,&rear, 3);//3 2 1
    p(peek_front(front));//3
    p(peek_rear(rear));//1
    p(dequeue_front(&front,&rear));//3
    p(peek_front(front));//2
    p(peek_rear(rear));//1
    p(dequeue_rear(&front,&rear));//1
    p(peek_front(front));//2
    p(peek_rear(rear));//2
    p(dequeue_rear(&front,&rear));//2
    p(isEmpty(front));//1

return 0;
}