//
// Created by Corentin on 26/09/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingGraph.h"

void graph_add_node(struct Graph *self) {

    if (self->size == self->nbMaxNodes) {
        self->nbMaxNodes *= 2;
        int *data = calloc(self->nbMaxNodes, sizeof(Node));
        memcpy(data, self->array, self->size * sizeof(Node));

        //libération de la mémoire de l'ancien tableau
        int i;
        for (i = 0; i < self->nbMaxNodes; i++) {
            if (self->array[i].adjList != NULL) {

                struct Neighbour* tmp;

                while (self->array[i].adjList != NULL)
                {
                    tmp = self->array[i].adjList;
                    self->array[i].adjList = self->array[i].adjList->nextNeighbour;
                    free(tmp);
                }
            }
            free(self->array[i].adjList);
        }
        free(self->array);

        //nouveau tableau que l'on a créé
        self->array = data;
    }

    self->array[self->size].adjList = NULL;
    self->size += 1;
}


void graph_add_edge(struct Graph *self, int src, int dest, int weight){

    if (src < 0 || src > self->size) {
        printf("Source invalid");
        return;
    }
    if (dest < 0 || dest > self->size) {
        printf("Source invalid");
        return;
    }

    struct Neighbour *node = malloc(sizeof(struct Neighbour));
    node->neighbour = dest;
    node->nextNeighbour = NULL;

    if (self->array[src].adjList == NULL) {
        self->array[src].adjList = node;
        self->array[src].adjList->weight = weight;
        return;
    }

    struct Neighbour *tmp  = self->array[src].adjList;

    while (tmp != NULL) {
        tmp = tmp->nextNeighbour;
    }

    tmp->nextNeighbour = node;
    tmp->nextNeighbour->weight = weight;
}

void graph_remove_edge(struct Graph *self, int src, int dest) {
    if (src < 1 || src > self->nbMaxNodes) {
        printf("Source invalid");
        return;
    }
    if (dest < 1 || dest > self->nbMaxNodes) {
        printf("Source invalid");
        return;
    }
}

void graph_print(struct Graph *self) {

    printf("# maximum number of nodes\n");
    printf("%d\n", self->nbMaxNodes);
    printf("# directed\n");
    printf("n\n");
    printf("node: neighbours\n");

    int i, j;
    for (i = 0; i < self->size; i++) {
        printf ("%d: ", i);
        struct Neighbour *curr = self->array[i].adjList;
        while (curr) {
            if (curr->nextNeighbour == NULL) {
                printf("(%d/%d)", curr->neighbour, curr->weight);
            }
            else {
                printf("(%d/%d),", curr->neighbour, curr->weight);
            }
            curr = curr->nextNeighbour;
        }
        printf("\n");
    }


}
