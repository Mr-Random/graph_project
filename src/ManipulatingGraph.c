//
// Created by Corentin on 26/09/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingGraph.h"
#include "ManipulatingLinkedLists.h"

void graph_add_node(struct Graph *self) {

    if (self->size == self->nbMaxNodes) {
        self->nbMaxNodes *= 2;
        struct Node *data = calloc(self->nbMaxNodes, sizeof(Node));
        memcpy(data, self->array, self->size * sizeof(Node));

        //Free old tab memory 
        graph_destroy(self);

        //Affected new data to array
        self->array = data;
    }

    self->array[self->size].adjList = NULL;
    self->size += 1;
}


void graph_add_edge(struct Graph *self, int src, int dest, int weight){

    if (src < 0 || src > self->size) {
        printf("Source invalid !\n");
        return;
    }

    if (dest < 0 || dest > self->size) {
        printf("Destination invalid !\n");
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
    
    while (tmp->nextNeighbour != NULL) {
        tmp = tmp->nextNeighbour;
    }

    tmp->nextNeighbour = node;
    tmp->nextNeighbour->weight = weight;
    
    node->previousNeighbour = tmp;
}



void graph_remove_edge(struct Graph *self, int src, int dest) {

    if (src < 0 || src > self->nbMaxNodes) {
        printf("Source invalid !\n");
        return;
    }

    if (dest < 0 || dest > self->nbMaxNodes) {
        printf("Destination invalid !\n");
        return;
    }

    browseDelete(self, src, dest);

    if(!self->isDirected) {
        browseDelete(self, dest, src);
    }

}

void graph_remove_node(struct Graph *self, int node) {

}

void graph_print(struct Graph *self) {

    printf("# maximum number of nodes\n");
    printf("%d\n", self->nbMaxNodes);
    printf("# directed\n");
    printf("n\n");
    printf("node: neighbours\n");

    for (int i = 0; i < self->size; i++) {
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

void browseDelete(struct Graph *self, int src, int dest){
    int index = 0;
    struct Neighbour *n =  self->array[src].adjList;

    while(n != NULL){

        if(n->neighbour == dest){

           if (index == 0) {
                self->array[src].adjList = n->nextNeighbour;
                printf("index : %d\n\n\n", index);
           } 
           else {
                n->previousNeighbour->nextNeighbour = n->nextNeighbour; 
           }
           free(n);
           break;
        }
        /* increment */
        n = n->nextNeighbour;
        index++;
    } 
}