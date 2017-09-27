//
// Created by Corentin on 24/09/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include "ManipulatingLinkedLists.h"


void graph_create(struct Graph *self, int maxNode, bool directed) {
    self->size = 0;
    self->nbMaxNodes = maxNode;

    self->array = malloc(maxNode*sizeof(struct Node));

}

void graph_destroy (struct Graph *self) {
    int i, j;

    for (i = 0; i < self->size; i++) {
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



void graph_load (char file[]) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(file, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

