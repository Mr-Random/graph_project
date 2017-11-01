//---------------------//
// Linked-List Library //
//---------------------//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingGraph.h"
#include "ManipulatingLinkedLists.h"

void graph_add_edge(struct Graph *self, int src, int dest, int weight) {
    
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

    browseAdd(self, src, dest, weight);
    if(!self->isDirected) {
        browseAdd(self, dest, src, weight);
    }


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

/* Function used to remove edges by browsing adjacent list */
/* we go through the adjency list and see if one of the neighbors 
   corresponds to the destination node of our edges to be deleted */
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
        /* Go to the next Neighbour */
        n = n->nextNeighbour;
        index++;
    } 
}

void browseAdd(struct Graph *self, int src, int dest, int weight) {
    int indexSource = findNode(self, src);
    int indexDestination = findNode(self, dest);

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

