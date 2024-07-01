#include "./adjecency_list.c"

void bfs(Graph* graph, int startVertex) {
    int numVertices = graph->numVertices;
    int* visited = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    CircularQueue queue;
    initializeQueue(&queue);
    visited[startVertex] = 1;
    enqueue(&queue, startVertex);

    while (!isEmptyQueue(&queue)) {
        int currentVertex = dequeue(&queue);
        printf("Visited %d\n", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                enqueue(&queue, adjVertex);
            }
            temp = temp->next;
        }
    }
    free(visited);  
}
/*
int main() {
    int numVertices = 15;
    Graph* graph = createGraph(numVertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 5);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 6);
    addEdge(graph, 2, 6);
    addEdge(graph, 3, 9);
    addEdge(graph, 3, 7);
    addEdge(graph, 3, 8);
    addEdge(graph, 4, 10);
    addEdge(graph, 5, 11);
    addEdge(graph, 7, 12);
    addEdge(graph, 8, 13);
    addEdge(graph, 9, 13);
    addEdge(graph, 10, 14);
    addEdge(graph, 11, 12);
    addEdge(graph, 14, 13);

    // printGraph(graph);
    // bfs(graph, 6);
    bfs(graph, 0);

    return 0;
}
*/
