#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

int visited[MAX_VERTICES];

typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;  // This is important, see the enqueue function
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

void enqueue(Queue* queue, int item) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

void BFS(int graph[MAX_VERTICES][MAX_VERTICES], int start, int vertices) {
    Queue* queue = createQueue(vertices);

    visited[start] = 1;
    printf("%d ", start);
    enqueue(queue, start);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);

        for (int i = 0; i < vertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                printf("%d ", i);
                enqueue(queue, i);
            }
        }
    }

    free(queue->array);
    free(queue);
}

int main() {
    int vertices, edges;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    int graph[MAX_VERTICES][MAX_VERTICES];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    // Initialize visited array
    for (int i = 0; i < MAX_VERTICES; i++) {
        visited[i] = 0;
    }

    printf("BFS starting from vertex 0: ");
    BFS(graph, 0, vertices);

    return 0;
}
