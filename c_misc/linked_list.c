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

void insert_at_end(node* const start,const int data){
    node* n=create(data);
    node* temp=start;
    while(temp->next!=NULL){
        temp=temp->next;
        continue;
    }
    temp->next=n;
    n->next=NULL;
}

node* insert_at_beginning(node* const start,const int data){
    node* n=create(data);
    n->next=start;
    return n;
}

void printll(const node* start) {
    const node* current = start;
    while (current!= NULL) {
        printf("%d ", current->data);
        current = current->next; // Move to the next node
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

void delete(node** start,int key){
    node*temp=*start;
     if(temp->data==key){
            if(temp->next){
                *start=temp->next;
                free(temp);
                return;
            }
            else{
                free(temp);
                *start=NULL;
                return;
            }
        }
    while(temp){
        if(temp->next && temp->next->data==key){
            if(temp->next->next){
                node* tempp=temp->next;
                temp->next=temp->next->next;
                free(tempp);
                return;
            }
            else{
                free(temp->next);
                temp->next=NULL;
                return;
            }
        }
        temp=temp->next;
    }
    return;
}

int main(void){
    node* start=NULL;
    start=insert_at_beginning(start,5);
    insert_at_end(start,6);
    insert_at_end(start,8);
    node **st=&start;
    delete(st,5);
    delete(st,8);
    delete(st,6);
    p(start->data);
    printll(start);
    freell(start);
}