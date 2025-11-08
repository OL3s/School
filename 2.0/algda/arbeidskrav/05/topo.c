// ./topo.c
// ./topo.bin < filnavn.txt
#include <stdio.h>
#include <stdlib.h>

// dynamisk liste av int
typedef struct {
    int *elements;   // dynamisk array
    int count;       // antall brukte
    int capacity;    // allokert kapasitet
} IntList;

// node i rettet graf
typedef struct {
    IntList neighbors;   // utgående naboer
    int inDegreeCount;   // antall innkanter til noden
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

int main(void) {
    int numberOfNodes, numberOfEdges; // init nodeantall og kantantall
    if (scanf("%d %d", &numberOfNodes, &numberOfEdges) != 2) {
        fprintf(stderr, "Error: Could not read graph file or file is missing.\n");
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
        graph[i].inDegreeCount = 0;
    }

    // les kanter rettet
    for (int i = 0; i < numberOfEdges; i++) {
        int fromNode, toNode;
        if (scanf("%d %d", &fromNode, &toNode) != 2) {
            fprintf(stderr, "Error: Bad edge line.\n");
            for (int j = 0; j < numberOfNodes; j++) free(graph[j].neighbors.elements);
            free(graph);
            return 1;
        }
        add_to_list(&graph[fromNode].neighbors, toNode);
        graph[toNode].inDegreeCount++;
    }

    // kø for noder med inn-grad 0
    int *queueArray = malloc(numberOfNodes * sizeof(int));
    if (!queueArray) { perror("malloc"); for (int i = 0; i < numberOfNodes; i++) free(graph[i].neighbors.elements); free(graph); return 1; }
    int queueHead = 0, queueTail = 0;

    // legg alle inDegree==0 i kø
    for (int i = 0; i < numberOfNodes; i++)
        if (graph[i].inDegreeCount == 0) queueArray[queueTail++] = i;

    // resultat
    int *topologicalOrder = malloc(numberOfNodes * sizeof(int));
    if (!topologicalOrder) { perror("malloc"); for (int i = 0; i < numberOfNodes; i++) free(graph[i].neighbors.elements); free(graph); free(queueArray); return 1; }
    int outputCount = 0;

    // Kahn's algoritme
    printf("Topological order:");
    while (queueHead < queueTail) {
        int currentNode = queueArray[queueHead++];   // ta fra front
        topologicalOrder[outputCount++] = currentNode;
        printf(" %d", currentNode);

        IntList *neighbors = &graph[currentNode].neighbors;
        for (int j = 0; j < neighbors->count; j++) {
            int neighborNode = neighbors->elements[j];
            graph[neighborNode].inDegreeCount--;     // "fjern" kant
            if (graph[neighborNode].inDegreeCount == 0)
                queueArray[queueTail++] = neighborNode;
        }
    }
    printf("\n");

    // sjekk for syklus
    if (outputCount != numberOfNodes) {
        printf("Cycle detected\n");
    }

    // rydd minne
    for (int i = 0; i < numberOfNodes; i++) free(graph[i].neighbors.elements);
    free(graph);
    free(queueArray);
    free(topologicalOrder);
    return 0;
}