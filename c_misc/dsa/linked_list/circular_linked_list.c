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
    n->next=start;
    node* temp=start;
    while(temp->next!=start){
        temp=temp->next;
        continue;
    }
    temp->next=n;
}

node* insert_at_beginning(node* const start,const int data){
    node* n=create(data);
    if(start)
    n->next=start;
    else
    n->next=n;
    return n;
}

void insert_at_position(node** start,const int data,const int pos){
    node* n=create(data);
    node* temp=*start;
    if(pos==0){
        n->next=*start;
        // *start=n;
        if(temp->next==temp)temp->next=n;
        else{
            while(temp->next!=*start){
                temp=temp->next;
            }
            temp->next=n;
        }
        *start=n;
        return;
    }
    for(int i=1;i<pos;i++){
        if(temp->next==*start){
            ps("Position not found\n");
            return;
        }
        temp=temp->next;
    }
    if(temp->next==*start){
        temp->next=n;
        n->next=*start;
        return;
    }
    n->next=temp->next;
    temp->next=n;
}

void printll(const node* start) {
    const node* current = start;
    if (start == NULL) {
        ps("List is empty\n");
        return;
    }
    do {
        printf("%d ", current->data);
        current = current->next; // Move to the next node
    } while (current != start);
    printf("\n");
}

void freell(node* start){
    node *temp=start;
    do{
        node* next=temp->next;
        free(temp);
        temp=next;
    }
    while(temp!=start);
}

void delete_node(node** start,int key){
    node*temp=*start;
     if(temp->data==key){
            if(temp->next){
                while(temp->next!=*start){
                    temp=temp->next;
                }
                temp->next=(*start)->next;
                temp=*start;
                *start=(*start)->next;
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
        if(temp->next==*start){
            ps("Key not found\n");
            return;
        }
        if(temp->next && temp->next->data==key){
            if(temp->next->next){
                node* tempp=temp->next;
                temp->next=temp->next->next;
                free(tempp);
                return;
            }
            else{
                free(temp->next);
                temp->next=*start;
                return;
            }
        }
        temp=temp->next;
    }
    return;
}

int main(void){
    node* start=NULL;
    start=insert_at_beginning(start,1);
    insert_at_end(start,2);
    insert_at_end(start,3);
    insert_at_end(start,4);
    insert_at_end(start,5);
    insert_at_end(start,6);
    insert_at_end(start,7);
    insert_at_end(start,8);
    insert_at_end(start,9);
    insert_at_end(start,10);
    printll(start);
    insert_at_position(&start,11,0);
    printll(start);
    insert_at_position(&start,12,5);
    printll(start);
    insert_at_position(&start,13,12);
    printll(start);
    delete_node(&start,1);
    printll(start);
    delete_node(&start,6);
    printll(start);
    delete_node(&start,13);
    printll(start);
    freell(start);
return 0;
}