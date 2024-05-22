//program to implement linked list

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

void insert_at_position(node** start,const int data,const int pos){
    node* n=create(data);
    node* temp=*start;
    if(pos==0){
        n->next=*start;
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
        return;
    }
    n->next=temp->next;
    temp->next=n;
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

void delete_node(node** start,int key){
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

void update_node(node** start,int key,int new_data){
    node*temp=*start;
    while(temp){
        if(temp->data==key){
            temp->data=new_data;
            return;
        }
        temp=temp->next;
    }
    ps("Key not found\n");
    return;
}

void reverse(node** start){
    node* temp=NULL;
    node* prev=NULL;
    node* current=*start;
    while(current!=NULL){
        temp=current->next;
        current->next=prev;
        prev=current;
        current=temp;
    }
    *start=prev;
}

int main(void){
    node*start=insert_at_beginning(NULL,5);
    insert_at_end(start,6);
    insert_at_end(start,8);
    insert_at_end(start,9);
    node** startp=&start;
    insert_at_position(startp,7,0);
    update_node(startp,7,10);
    // p(start->data);
    printll(start);
    freell(start);
}