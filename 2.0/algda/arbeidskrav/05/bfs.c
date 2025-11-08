// ./bfs.c
// ./bfc.bin < filnavn.txt <startnode>
#include <stdio.h>
#include <stdlib.h>

// dynamisk liste av int
typedef struct {
    int *elements;   // dynamisk array
    int count;       // antall brukte
    int capacity;    // allokert kapasitet
} IntList;

// node i urettet graf
typedef struct {
    IntList neighbors;       // naboer
    char wasVisited;         // 0/1
    int distanceFromStart;   // -1 = ikke nådd
    int predecessor;         // for sti (eller -1)
} Node;

// legg til verdi i liste
static void add_to_list(IntList *list, int value) {
    if (list->count == list->capacity) {
        list->capacity = list->capacity ? list->capacity * 2 : 4;
        list->elements = realloc(list->elements, list->capacity * sizeof(int));
        if (!list->elements) { perror("realloc"); exit(1); }
    }
    list->elements[list->count++] = value;
}

int main(int argumentCount, char **argumentValues) {
    int numberOfNodes, numberOfEdges; // init nodeantall og kantantall
    if (scanf("%d %d", &numberOfNodes, &numberOfEdges) != 2) {
        printf("Error: Could not read graph file or file is missing.\n");
        return 1;
    }

    // lag graf som array av Node
    Node *graph = calloc(numberOfNodes, sizeof(Node));
    if (!graph) { perror("calloc"); return 1; }

    // init felt på noder
    for (int i = 0; i < numberOfNodes; i++) {
        graph[i].neighbors.elements = NULL;
        graph[i].neighbors.count = 0;
        graph[i].neighbors.capacity = 0;
        graph[i].wasVisited = 0;
        graph[i].distanceFromStart = -1;
        graph[i].predecessor = -1;
    }

    // les kanter urettet
    for (int i = 0; i < numberOfEdges; i++) {
        int fromNode, toNode;
        if (scanf("%d %d", &fromNode, &toNode) != 2) return 1;
        add_to_list(&graph[fromNode].neighbors, toNode);
        add_to_list(&graph[toNode].neighbors, fromNode);
    }

    // startnode (argument eller 0)
    int startNode = 0;
    if (argumentCount > 1) startNode = atoi(argumentValues[1]);
    if (startNode < 0 || startNode >= numberOfNodes) {
        fprintf(stderr, "Invalid start node\n");
        return 1;
    }

    // kø for BFS
    int *queueArray = malloc(numberOfNodes * sizeof(int));
    if (!queueArray) { perror("malloc"); return 1; }
    int queueHead = 0, queueTail = 0;

    // start BFS
    graph[startNode].wasVisited = 1;
    graph[startNode].distanceFromStart = 0;
    graph[startNode].predecessor = -1;
    queueArray[queueTail++] = startNode;

    // BFS-løkke
    printf("BFS order:");
    while (queueHead < queueTail) {
        int currentNode = queueArray[queueHead++]; // ta fra front
        printf(" %d", currentNode);                // skriv rekkefølge

        IntList *neighbors = &graph[currentNode].neighbors;
        for (int j = 0; j < neighbors->count; j++) {
            int neighborNode = neighbors->elements[j];
            if (!graph[neighborNode].wasVisited) {
                graph[neighborNode].wasVisited = 1;                                                 // merk besøkt
                graph[neighborNode].distanceFromStart = graph[currentNode].distanceFromStart + 1;   // sett avstand
                graph[neighborNode].predecessor = currentNode;                                      // sett forelder
                queueArray[queueTail++] = neighborNode;                                             // legg i kø
            }
        }
    }
    printf("\n");

    // skriv avstander
    printf("Distances:\n");
    for (int i = 0; i < numberOfNodes; i++)
        printf("node %d: %d\n", i, graph[i].distanceFromStart);

    // skriv foreldre
    printf("Predecessors:\n");
    for (int i = 0; i < numberOfNodes; i++)
        printf("node %d: %d\n", i, graph[i].predecessor);

    // rydd minne
    for (int i = 0; i < numberOfNodes; i++) free(graph[i].neighbors.elements);
    free(graph);
    free(queueArray);
    return 0;
}
