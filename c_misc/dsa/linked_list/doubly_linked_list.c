//program to implement doubly linked list
#include<stdio.h>
#include<stdlib.h>
#define p(x) printf("%d\n", x)
#define pf(x) printf("%f\n", x)
#define ps(x) printf("%s", x)
#define s(x) scanf("%d", &x)


typedef struct node{
    int data;
    struct node *next;
    struct node *prev;
}node;

node* create(const int data){
    node* new = (node*)malloc(sizeof(node));
    if (new == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    new->data = data; // Set the data of the new node
    new->next = NULL; // Initialize the next pointer to NULL
    new->prev = NULL; // Initialize the prev pointer to NULL
    return new;
}

void insert_at_end(node* const start,const int data){
    node* n=create(data);
    node* temp=start;
    while(temp->next!=NULL){
        temp=temp->next;
        continue;
    }
    temp->next=n;
    n->next=NULL;
    n->prev=temp;
}

node* insert_at_beginning(node** const start,const int data){
    node* n=create(data);
    n->next=*start;
    (*start)->prev=n;
    *start=n;
    return n;
}

void insert_at_position(node** start,const int data,const int pos){
    node* n=create(data);
    node* temp=*start;
    if(pos==0){
        n->next=*start;
        (*start)->prev=n;
        *start=n;
        return;
    }
    for(int i=1;i<pos;i++){
        if(temp->next==NULL){
            ps("Position not found\n");
            return;
        }
        temp=temp->next;
    }
    if(temp->next==NULL){
        temp->next=n;
        n->next=NULL;
        n->prev=temp;
        return;
    }
    n->next=temp->next;
    temp->next->prev=n;
    temp->next=n;
    n->prev=temp;
}

void printll(const node* start) {
    const node* current = start;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void freell(node* start){
    node *temp=start;
    while(temp!=NULL){
        node* next=temp->next;
        free(temp);
        temp=next;
    }
}

void delete_node(node** start,const int pos){
    node* temp=*start;
    if(pos==0){
        *start=(*start)->next;
        (*start)->prev=NULL;
        free(temp);
        return;
    }
    for(int i=1;i<pos;i++){
        if(temp->next==NULL){
            ps("Position not found\n");
            return;
        }
        temp=temp->next;
    }
    if(temp->next==NULL){
        temp->prev->next=NULL;
        free(temp);
        return;
    }
    temp->prev->next=temp->next;
    temp->next->prev=temp->prev;
    free(temp);
}

void reverse(node** start){
    node* temp=NULL;
    node* current=*start;
    while(current!=NULL){
        temp=current->prev;
        current->prev=current->next;
        current->next=temp;
        current=current->prev;
    }
    if(temp!=NULL){
        *start=temp->prev;
    }
}

void update_node(node** start,const int key,const int data){
    node* temp=*start;
    while(temp){
        if(temp->data==key){
            temp->data=data;
            return;
        }
        temp=temp->next;
    }
    ps("Key not found\n");
}

int main(void){
    node* start=create(1);
    insert_at_end(start,2);
    insert_at_end(start,3);
    insert_at_end(start,4);
    insert_at_end(start,5);
    insert_at_end(start,6);
    insert_at_end(start,7);
    insert_at_end(start,8);
    insert_at_end(start,9);
    insert_at_end(start,10);
    insert_at_beginning(&start,0);
    insert_at_position(&start,11,11);
    printll(start);
    delete_node(&start,0);
    delete_node(&start,11);
    delete_node(&start,5);
    printll(start);
    reverse(&start);
    printll(start);
    update_node(&start,5,5);
    update_node(&start,6,16);
    printll(start);
    freell(start);
    return 0;

}