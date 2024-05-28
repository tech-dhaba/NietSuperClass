#include <stdio.h>
#include <stdlib.h>
#include "../array/circular_queue.c"
#include "../array/stack.c"

// Node structure for adjacency list
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Graph structure using adjacency list
typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Create a new node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with given number of vertices
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // Create an array of adjacency lists
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));

    // Initialize each adjacency list as empty
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// Add an edge to an undirected graph
void addEdge(Graph* graph, int src, int dest) {
    // Add an edge from src to dest
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Since the graph is undirected, add an edge from dest to src as well
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// Print the graph
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        printf("Adjacency list of vertex %d\n", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// int main() {
//     int numVertices = 15;
//     Graph* graph = createGraph(numVertices);
//     addEdge(graph, 0, 1);
//     addEdge(graph, 0, 2);
//     addEdge(graph, 0, 3);
//     addEdge(graph, 1, 5);
//     addEdge(graph, 1, 4);
//     addEdge(graph, 1, 6);
//     addEdge(graph, 2, 6);
//     addEdge(graph, 3, 9);
//     addEdge(graph, 3, 7);
//     addEdge(graph, 3, 8);
//     addEdge(graph, 4, 10);
//     addEdge(graph, 5, 11);
//     addEdge(graph, 7, 12);
//     addEdge(graph, 8, 13);
//     addEdge(graph, 9, 13);
//     addEdge(graph, 10, 14);
//     addEdge(graph, 11, 12);
//     addEdge(graph, 14, 13);

//     // printGraph(graph);
//     // bfs(graph, 6);
//     dfs(graph, 0);

//     return 0;
// }
