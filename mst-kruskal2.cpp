#include <iostream>
 
struct Edge {
  int src, dest, weight;
};

struct Graph {
  int V, E;

  struct Edge* edge;
};

struct Subsets {
  int parent, rank;
};

// Function Prototypes
struct Graph* createGraph(int V, int E);
int find(struct Subsets subsets[], int V);
void Union(struct Subsets subsets[], int x, int y);
void isort(struct Graph* graph);
void kruskalMst (struct Graph* graph);

int main() {
  int V = 4;  // Number of vertices in graph
  int E = 5;  // Number of edges in graph
  struct Graph* graph = createGraph(V, E);
  // add edge 0-1
  graph->edge[0].src = 0;
  graph->edge[0].dest = 1;
  graph->edge[0].weight = 10;

  // add edge 0-2
  graph->edge[1].src = 0;
  graph->edge[1].dest = 2;
  graph->edge[1].weight = 6;

  // add edge 0-3
  graph->edge[2].src = 0;
  graph->edge[2].dest = 3;
  graph->edge[2].weight = 5;

  // add edge 1-3
  graph->edge[3].src = 1;
  graph->edge[3].dest = 3;
  graph->edge[3].weight = 15;

  // add edge 2-3
  graph->edge[4].src = 2;
  graph->edge[4].dest = 3;
  graph->edge[4].weight = 4;

  // Print the Graph
  for (int i = 0; i < graph->E; ++i)
    printf("%d -- %d == %d\n", graph->edge[i].src, graph->edge[i].dest, graph->edge[i].weight);

  std::cout<<"After Kruskal"<<std::endl;
  kruskalMst(graph);
  
}

// Function Implementations

struct Graph* createGraph(int V, int E) {
  struct Graph* graph = new Graph;
  graph->V = V;
  graph->E = E;
  graph->edge = new Edge[E];
  return graph;
};

int find(struct Subsets subsets[], int V) {
  if(subsets[V].parent != V) {
    subsets[V].parent = find(subsets, subsets[V].parent);
  }
  return subsets[V].parent;
}

void Union(struct Subsets subsets[], int x, int y){
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);

  if (subsets[xroot].rank < subsets[yroot].rank)
    subsets[xroot].parent = yroot;
  else if (subsets[xroot].rank > subsets[yroot].rank)
    subsets[yroot].parent = xroot;
  else {
    subsets[yroot].parent = xroot;
    subsets[xroot].rank++;
  }
}

void isort(struct Graph* graph) {
  for(int c = 1; c < graph->E; c++) {
    for(int k =  c; k > 0; k--) {
      if(graph->edge[k].weight < graph->edge[k-1].weight) {
        struct Edge temp  = graph->edge[k];
        graph->edge[k] = graph->edge[k-1];
        graph->edge[k-1] = temp;
      }
    }
  }
}

void kruskalMst (struct Graph* graph) {
int V = graph->V;
struct Edge result[V];  // Tnis will store the resultant MST
int e = 0;  // An index variable, used for result
int i = 0;  // An index variable, used for sorted edges

isort(graph);

// Create V subsets with single elements
  struct Subsets* subsets = (struct Subsets*)malloc(V *sizeof(struct Subsets));
  for(int v = 0; v < V; v++) {
    subsets[v].parent = v;
    subsets[v].rank = 0;
  }

  // Step 3 -> repeat step #2 until edge count is V-1
  while( e < (V-1) ) {
    // Step 2: Pick the smallest edge. And increment
    // the index for next iteration
    struct Edge next = graph->edge[i++];

    int x = find(subsets, next.src);
    int y = find(subsets, next.dest);

    if(x != y) {
      result[e++] = next;
      Union(subsets, x, y);
    }
  }

  // Print the MST
  for (i = 0; i < e; ++i)
    printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

}

