
#include <stdio.h>

#define MAX_VERTICES 100  // Define the maximum number of vertices

typedef struct {
    int numVertices;             // Number of vertices in the graph
    int vertices[MAX_VERTICES][MAX_VERTICES];  // Adjacency matrix
} Graph;



void initializeGraph (Graph *graph, int numVertices) {
graph->numVertices = numVertices;
int i, j;
for (i=0; i<numVertices; i++) {
for (j = 0; j < numVertices; j++) {
graph->vertices[i][j] = 0;
}
}}

void addEdge(Graph *graph, int src, int dest, int weight) {
    graph->vertices[src][dest] = weight;
}



void displayGraph(Graph *graph) {
    int i, j;
    for (i = 0; i < graph->numVertices; i++) {
        for (j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->vertices[i][j]);
        }
        printf("\n");
    }
}


int isAdjacent (Graph *graph, int vertexl, int vertex2) { 
    if (graph->vertices[vertexl][vertex2] != 0) { return 1;
} else {
return 0;
}}

int getDegree (Graph *graph, int vertex) {
int degree = 0;
int i;
for (i = 0; i < graph->numVertices; i++) {
if (graph->vertices [vertex] [i] != 0) { degree++;
}
}
return degree;
}

int main() {
    Graph graph;
    int numVertices = 5;  // Example: Number of vertices

    // Initialize the graph
    initializeGraph(&graph, numVertices);

    // Add edges
    addEdge(&graph, 0, 1, 10);  // Add an edge from vertex 0 to vertex 1 with weight 10
    addEdge(&graph, 1, 2, 20);  // Add an edge from vertex 1 to vertex 2 with weight 20

    // Display the graph
    displayGraph(&graph);

    // // Check if vertices are adjacent
    // int vertex1 = 0, vertex2 = 1;
    // if (isAdjacent(&graph, vertex1, vertex2)) {
    //     printf("Vertices %d and %d are adjacent.\n", vertex1, vertex2);
    // } else {
    //     printf("Vertices %d and %d are not adjacent.\n", vertex1, vertex2);
    // }

    // // Get the degree of a vertex
    // int vertex = 1;
    // int degree = getDegree(&graph, vertex);
    // printf("Degree of vertex %d is %d.\n", vertex, degree);

    return 0;
}
