//
// Created by Corentin on 31/10/2017.
//

#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include "structure.h"

void solveChineseProblem(struct Graph *self) {

    int numberOddDegree = 0;
    int tabDegree[self->size];
    memset( tabDegree, 0, self->size*sizeof(int) );

    for (int i = 0; i < self->size; i++) {
        struct Neighbour *curr = self->array[i].adjList;
        while (curr) {
            tabDegree[i]++;
            curr = curr->nextNeighbour;
        }
    }

    for (int i = 0; i < self->size; i++) {
        printf("[%d] = %d\n", i, tabDegree[i]);
        if (tabDegree[i] % 2 != 0) {
            numberOddDegree++;
        }
    }

    printf("\n\nNumber odd degree : %d", numberOddDegree);


    //Eulerian
    if (numberOddDegree == 0) {

    }
    //Semi-Eulerian
    else if (numberOddDegree == 2) {

    }
    //Non-Eulerian
    else {
        
    }



    free(tabDegree);


}
