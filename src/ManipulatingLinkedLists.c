//---------------------//
// Linked-List Library //
//---------------------//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "ManipulatingLinkedLists.h"


/* Function Create and Init Graf */
void graph_create(struct Graph *self, int maxNode, bool directed) {
    self->size = 0;
    self->nbMaxNodes = maxNode;
    self->isDirected = directed;

    self->array = malloc(maxNode*sizeof(struct Node));
}

/* Function Destroy Graf and Free memory */
void graph_destroy (struct Graph *self) {
    
    for (int i = 0; i < self->size; i++) {
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
}



