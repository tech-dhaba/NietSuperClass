#include "./adjecency_list.c"
#include <limits.h>

void djkstra(Graph* graph, int start_vertex, int end_vertex){
    int numVertices=graph->numVertices;
    int* visited=(int*)malloc(numVertices*sizeof(int));
    int* distance=(int*)malloc(numVertices*sizeof(int));
    for(int i=0;i<numVertices;i++){
        visited[i]=0;
        distance[i]=INT_MAX;
    }
    distance[start_vertex]=0;
    
    
}