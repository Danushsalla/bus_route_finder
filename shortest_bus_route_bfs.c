
/*
 Project Title : Shortest Bus Route Finder using BFS
 Description   : Finds the shortest route between two bus stops using
                 Breadth First Search (BFS) in an unweighted graph.
 Language      : C
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Adjacency list node
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Queue structure for BFS
typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is empty
int isEmpty(Queue *q) {
    return q->rear == -1;
}

// Insert an element into the queue
void enqueue(Queue *q, int value) {
    if (q->rear == MAX - 1) {
        printf("Queue overflow! Cannot enqueue.\n");
        return;
    }
    if (q->front == -1)
        q->front = 0;

    q->rear++;
    q->items[q->rear] = value;
}

// Remove an element from the queue
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }

    int value = q->items[q->front];
    q->front++;

    if (q->front > q->rear)
        q->front = q->rear = -1;

    return value;
}

// Create new adjacency list node
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Add an undirected edge
void addEdge(Node* adj[], int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = adj[src];
    adj[src] = newNode;

    newNode = createNode(src);
    newNode->next = adj[dest];
    adj[dest] = newNode;
}

// BFS to find shortest path
void bfs(Node* adj[], int start, int end, int n) {

    if (start == end) {
        printf("\nShortest Bus Route: %d\nTotal Stops: 0\n", start);
        return;
    }

    int visited[MAX] = {0};
    int parent[MAX];

    for (int i = 0; i < n; i++)
        parent[i] = -1;

    Queue q;
    initQueue(&q);

    visited[start] = 1;
    enqueue(&q, start);

    while (!isEmpty(&q)) {
        int current = dequeue(&q);

        if (current == end)
            break;

        Node* temp = adj[current];
        while (temp != NULL) {
            int v = temp->vertex;

            if (!visited[v]) {
                visited[v] = 1;
                parent[v] = current;
                enqueue(&q, v);
            }
            temp = temp->next;
        }
    }

    if (parent[end] == -1) {
        printf("\nNo route found between stops.\n");
        return;
    }

    int path[MAX];
    int idx = 0;
    int crawl = end;

    while (crawl != -1) {
        path[idx++] = crawl;
        crawl = parent[crawl];
    }

    printf("\nShortest Bus Route: ");
    for (int i = idx - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i != 0) printf(" -> ");
    }

    printf("\nTotal Stops: %d\n", idx - 1);
}

int main() {
    int n, e, src, dest;

    printf("Enter number of bus stops: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of stops.\n");
        return 0;
    }

    Node* adj[MAX];
    for (int i = 0; i < n; i++)
        adj[i] = NULL;

    printf("Enter number of direct routes: ");
    scanf("%d", &e);

    printf("Enter the routes (src dest):\n");
    for (int i = 0; i < e; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(adj, a, b);
    }

    printf("Enter source bus stop: ");
    scanf("%d", &src);

    printf("Enter destination bus stop: ");
    scanf("%d", &dest);

    bfs(adj, src, dest, n);

    return 0;
}
