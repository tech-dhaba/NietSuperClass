#include "./adjecency_list.c"

// Check if there is a cycle in the graph
int hasCycle(Graph* graph, int v, int visited[], int parent) {
    visited[v] = 1; // Mark the current node as visited

    // Traverse the adjacent vertices
    Node* temp = graph->adjLists[v];
    while (temp != NULL) {
        int i = temp->vertex;

        // If the adjacent vertex is not visited, then recur for it
        if (!visited[i]) {
            if (hasCycle(graph, i, visited, v)) {
                return 1;
            }
        }

        // If the adjacent vertex is visited and not the parent of the current vertex, then there is a cycle
        else if (i != parent) {
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

int main(){
  int vertices =10;
  Graph* graph = createGraph(vertices);
  addEdge(graph, 0, 1);
  addEdge(graph, 0, 2);
  addEdge(graph, 3, 1);
  addEdge(graph, 1, 4);
  addEdge(graph, 2, 5);
  addEdge(graph, 2, 6);
  addEdge(graph, 4, 7);
  addEdge(graph, 4, 8);
  addEdge(graph, 6, 9);
  addEdge(graph, 7, 2);

  int visited[vertices];
  for(int i = 0; i < vertices; i++){
    visited[i] = 0;
  }

  if(hasCycle(graph, 0, visited, -1)){
    printf("The graph has a cycle\n");
  } else {
    printf("The graph does not have a cycle\n");
  }

  return 0;
}
