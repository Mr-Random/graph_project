#include <stdbool.h>

#ifndef GRAF_STRUCTURE_H
#define GRAF_STRUCTURE_H


typedef struct Neighbour Neighbour;
struct Neighbour {
    int neighbour;
    int weight;

    struct Neighbour *nextNeighbour;
    struct Neighbour *previousNeighbour;
};

typedef struct Node Node;
struct Node {
    struct Neighbour *adjList;
};

typedef struct Graph Graph;
struct Graph {
    bool isDirected;
    int size;
    int nbMaxNodes;

    struct Node *array;
};


#endif //GRAF_STRUCTURE_H
