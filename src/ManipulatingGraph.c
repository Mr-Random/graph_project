//
// Created by Corentin on 26/09/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingGraph.h"
#include "ManipulatingLinkedLists.h"

void graph_add_node(struct Graph *self, int node) {

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
    self->array[self->size].node = node;
    self->size += 1;
}

void graph_add_edge(struct Graph *self, int src, int dest, int weight){

    int indexSource = findNode(self, src);
    int indexDestination = findNode(self, dest);

    if (indexSource == -1) {
        printf("Source invalid !\n");
        return;
    }

    if (indexDestination == -1) {
        printf("Destination invalid !\n");
        return;
    }

    struct Neighbour *node = malloc(sizeof(struct Neighbour));
    node->neighbour = dest;
    node->nextNeighbour = NULL;

    if (self->array[indexSource].adjList == NULL) {
        self->array[indexSource].adjList = node;
        self->array[indexSource].adjList->weight = weight;
        return;
    }

    struct Neighbour *tmp  = self->array[indexSource].adjList;
    
    while (tmp->nextNeighbour != NULL) {
        tmp = tmp->nextNeighbour;
    }

    tmp->nextNeighbour = node;
    tmp->nextNeighbour->weight = weight;
    
    node->previousNeighbour = tmp;
}

void graph_remove_edge(struct Graph *self, int src, int dest) {

    int indexSource = findNode(self, src);
    int indexDestination = findNode(self, dest);

    if (indexSource == -1) {
        printf("Source invalid !\n");
        return;
    }

    if (indexDestination == -1) {
        printf("Destination invalid !\n");
        return;
    }

    browseDelete(self, indexSource, dest);

    if(!self->isDirected) {
        browseDelete(self, indexDestination, src);
    }

}

void graph_remove_node(struct Graph *self, int node) {
    int indexNode = findNode(self, node);

    if (indexNode == -1) {
        printf("Node invalid !\n");
        return;
    }

    //remove edges
    int i;
    for (i = 0; i < self->size; i++) {
        browseDelete(self, i, node);
    }

    //remove node
    if (self->array[indexNode].adjList != NULL) {

        struct Neighbour* tmp;

        while (self->array[indexNode].adjList != NULL)
        {
            tmp = self->array[indexNode].adjList;
            self->array[indexNode].adjList = self->array[indexNode].adjList->nextNeighbour;
            free(tmp);
        }
    }
    free(self->array[indexNode].adjList);

    //move back of all value from index of node in array to the end of array
    for (size_t i = indexNode ; i < self->size-1 ; i++) {
        self->array[i] = self->array[i + 1];
    }
    self->size--;
}

void graph_print(struct Graph *self) {

    printf("# maximum number of nodes\n");
    printf("%d\n", self->nbMaxNodes);
    printf("# directed\n");
    printf("n\n");
    printf("node: neighbours\n");

    for (int i = 0; i < self->size; i++) {
        printf ("%d: ", self->array[i].node);
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

int findNode(struct Graph *self, int node) {
    int i;
    for (i = 0; i < self->size; i++) {
        if (self->array[i].node == node) {
            return i;
        }
    }
    return -1;
}
