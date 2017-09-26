//
// Created by Corentin on 26/09/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingGraph.h"

void graph_add_node(struct Graph *self) {

}


void graph_add_edge(struct Graph *self, int src, int dest){

    if (src < 1 || src > self->nbMaxNodes) {
        printf("Source invalid");
        return;
    }
    if (dest < 1 || dest > self->nbMaxNodes) {
        printf("Source invalid");
        return;
    }

    struct Neighbour *node = malloc(sizeof(struct Neighbour));
    node->neighbour = dest;
    node->nextNeighbour = NULL;

    if (self->array[src-1].adjList == NULL) {
        self->array[src-1].adjList = node;
        return;
    }

    struct Neighbour *tmp  = self->array[src-1].adjList;

    while (tmp != NULL) {
        tmp = tmp->nextNeighbour;
    }

    tmp->nextNeighbour = node;
}
