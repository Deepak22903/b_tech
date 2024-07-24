#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in adjacency list
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Structure to represent the adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure to represent the graph
struct Graph {
    int V;
    struct AdjList* array;
};

// Create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode =
        (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add an edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Add an edge from dest to src
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Structure to represent a node in queue
struct QueueNode {
    int value;
    struct QueueNode* next;
};

// Structure to represent a queue
struct Queue {
    struct QueueNode *front, *rear;
};

// Create an empty queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

// Enqueue a value to the queue
void enqueue(struct Queue* q, int value) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->value = value;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

// Dequeue a value from the queue
int dequeue(struct Queue* q) {
    if (q->front == NULL) return -1;
    struct QueueNode* temp = q->front;
    int value = temp->value;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    return value;
}

// Check if queue is empty
int isEmpty(struct Queue* q) {
    return q->front == NULL;
}

// Breadth First Search traversal
void traverseBFS(struct Graph* graph, int start) {
    int visited[graph->V];
    for (int i = 0; i < graph->V; ++i)
        visited[i] = 0;

    struct Queue* queue = createQueue();
    visited[start] = 1;
    enqueue(queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);

        struct AdjListNode* temp = graph->array[current].head;
        while (temp != NULL) {
            int adjNode = temp->dest;
            if (!visited[adjNode]) {
                visited[adjNode] = 1;
                enqueue(queue, adjNode);
            }
            temp = temp->next;
        }
    }
}

// Depth First Search traversal utility function
void DFSUtil(struct Graph* graph, int start, int visited[]) {
    visited[start] = 1;
    printf("%d ", start);

    struct AdjListNode* temp = graph->array[start].head;
    while (temp != NULL) {
        int adjNode = temp->dest;
        if (!visited[adjNode]) {
            DFSUtil(graph, adjNode, visited);
        }
        temp = temp->next;
    }
}

// Depth First Search traversal
void traverseDFS(struct Graph* graph, int start) {
    int visited[graph->V];
    for (int i = 0; i < graph->V; ++i)
        visited[i] = 0;
    DFSUtil(graph, start, visited);
}

// Structure to represent a subset for union-find
struct Subset {
    int parent;
    int rank;
};

// Find set of an element i
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union of two sets
void Union(struct Subset subsets[], int x, int y) {
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

// Compare function for qsort
int compare(const void* a, const void* b) {
    struct AdjListNode* aNode = (struct AdjListNode*)a;
    struct AdjListNode* bNode = (struct AdjListNode*)b;
    return aNode->weight - bNode->weight;
}


// Kruskal's algorithm to find Minimum Spanning Tree
void KruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct AdjListNode** result = (struct AdjListNode**)malloc(V * sizeof(struct AdjListNode*)); // Array to store the result MST
    int e = 0; // An index variable used for result[]
    int i = 0; // An index variable, used for sorted edges
    qsort(graph->array, V, sizeof(struct AdjList), compare);

    struct Subset* subsets =
        (struct Subset*)malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    while (e < V - 1 && i < V) {
        struct AdjListNode* temp = graph->array[i].head;
        while (temp != NULL) {
            struct AdjListNode* next_edge = temp;
            temp = temp->next;
            
            int x = find(subsets, next_edge->dest);
            int y = find(subsets, graph->array[i].head->dest);

            if (x != y) {
                result[e++] = next_edge;
                Union(subsets, x, y);
            }
        }
        i++;
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (i = 0; i < e; ++i)
        printf("%d - %d Weight: %d\n", result[i]->dest, result[i]->next->dest, result[i]->weight);

    free(result);
}



// Driver program to test above functions
int main() {
    int V = 4;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 2, 20);
    addEdge(graph, 1, 2, 30);
    addEdge(graph, 1, 3, 40);
    addEdge(graph, 2, 3, 50);

    printf("BFS traversal starting from vertex 0: ");
    traverseBFS(graph, 0);
    printf("\nDFS traversal starting from vertex 0: ");
    traverseDFS(graph, 0);
    printf("\n");
    KruskalMST(graph);

    return 0;
}
