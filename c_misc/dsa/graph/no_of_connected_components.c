#include "./adjecency_list.c"

void bfs(Graph* graph,int* visited, int startVertex) {
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
}

int noOfConnectedComponents(Graph* graph) {
    int numVertices = graph->numVertices;
    int* visited = (int*)malloc(numVertices * sizeof(int));
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
    }

    int count = 0;
    for (int i = 0; i < numVertices; i++) {
        if (visited[i] == 0) {
            bfs(graph, visited, i);
            count++;
        }
    }
    free(visited);
    return count;
}

int main() {
    int numVertices = 8;
    Graph* graph = createGraph(numVertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 4, 3);
    addEdge(graph, 5, 6);
    addEdge(graph, 5, 7);
    addEdge(graph, 6, 7);
    
    

    printf("Number of connected components: %d\n", noOfConnectedComponents(graph));

    return 0;
}