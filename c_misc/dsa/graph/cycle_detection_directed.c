#include "adjecency_list.c"

int isCyclicRec(Graph* graph, int i, int visited[], int visitedStack[]){
  if(!visited[i]){
    visited[i]=1;
    visitedStack[i]=1;
    Node* temp = graph->adjLists[i];
    while(temp){
      if(!visited[temp->vertex]&&isCyclicRec(graph,temp->vertex,visited,visitedStack))return 1;
      else if(visitedStack[temp->vertex])return 1;
      temp=temp->next;
    }
  }
    visitedStack[i]=0;
    return 0;
  }

int isCyclic(Graph* graph){

  int numVertices = graph->numVertices;
  int* visited = malloc(sizeof(int)*numVertices);
  int* visitedStack = malloc(sizeof(int)*numVertices);
  for(int i=0;i<numVertices;i++){
    visited[i]=0;
    visitedStack[i]=0;
    if(isCyclicRec(graph,i,visited,visitedStack))return 1;
  }

  return 0;
}

int main(){
  Graph* graph= createGraph(10);
  for(int i=0;i<graph->numVertices;i++)graph->adjLists[i]=0;
  addEdgeDir(graph,0,1);
  addEdgeDir(graph,2,1);
  addEdgeDir(graph,2,0);
  addEdgeDir(graph,1,7);
  addEdgeDir(graph,6,7);
  addEdgeDir(graph,6,2);
  addEdgeDir(graph,4,3);
  addEdgeDir(graph,6,5);
  addEdgeDir(graph,2,3);
  addEdgeDir(graph,4,5);
  addEdgeDir(graph,2,4);
  
  //addEdgeDir(graph,0,1);
  //addEdgeDir(graph,0,1);
  int cyc= isCyclic(graph);
  printf("%d\n",cyc);
}
  
  
