//
// Created by Corentin on 31/10/2017.
//

#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include <limits.h>
#include "structure.h"
#include "ManipulatingGraph.h"


void ConstructPair(int myTabOdd[], int numberOfOdd);

int ConvertToMatrix(struct Graph *self, int myMatrix[self->size][self->size]) {
    for (int i = 0; i < self->size; i++) {
        struct Neighbour *curr = self->array[i].adjList;
        while (curr) {
            myMatrix[i][findNode(self, curr->neighbour)] = curr->weight;
            curr = curr->nextNeighbour;
        }
    }
}

void FloydWarshall(struct Graph *self, int myMatrix[self->size][self->size], int distance[self->size][self->size]) {

    for(int i = 0; i < self->size; i++) {
        for(int j = 0; j < self->size; j++) {
            if (i == j) {
                distance[i][j] = 0;
            }
            else if (myMatrix[i][j] == 0) {
                distance[i][j] = INT_MAX;
            }
            else {
                distance[i][j] = myMatrix[i][j];
            }
        }
    }


    for (int i = 0; i < self->size; i++) {
        for (int j = 0; j < self->size; j++) {
            for (int k = 0; k < self->size; k++) {
                const int djk = distance[j][k];
                const int dji = distance[j][i];
                const int dik = distance[i][k];
                if (dji != INT_MAX && dik != INT_MAX && djk > dji + dik) {
                    distance[j][k] = dji + dik;
                }
            }
        }
    }

}



void solveChineseProblem(struct Graph *self) {

    int numberOddDegree = 0;
    int tabDegree[self->size];
    memset( tabDegree, 0, self->size*sizeof(int) );

    //KNOW THE DEGREE
    for (int i = 0; i < self->size; i++) {
        struct Neighbour *curr = self->array[i].adjList;
        while (curr) {
            tabDegree[i]++;
            curr = curr->nextNeighbour;
        }
    }

    //PRINT
    for (int i = 0; i < self->size; i++) {
        printf("[%d] = %d\n", i, tabDegree[i]);
        if (tabDegree[i] % 2 != 0) {
            numberOddDegree++;
        }
    }

    printf("\n\nNumber odd degree : %d\n", numberOddDegree);

    //CONSTRUCTION OF TAB THAT CONTAINS ALL THE ODD NODE
    int myTabOdd[numberOddDegree];
    memset(myTabOdd, 0, numberOddDegree*sizeof(int) );

    int j = 0;
    for (int i = 0; i < self->size; i++) {
        printf("[%d] = %d\n", i, tabDegree[i]);
        if (tabDegree[i] % 2 != 0) {
            myTabOdd[j] = i;
            j++;
        }
    }

    for (int i = 0; i < numberOddDegree; i++) {
        printf("%d ", myTabOdd[i]);
    }

    ConstructPair(myTabOdd, numberOddDegree);

    //MATRIX
    int myMatrix[self->size][self->size];
    memset(myMatrix, 0, self->size*self->size*sizeof(int) );

    for(int i = 0; i < self->size; i++) {
        for(int j = 0; j < self->size; j++) {
            myMatrix[i][j];
        }
    }
    ConvertToMatrix(self, myMatrix);


    int distance[self->size][self->size];
    memset(distance, 0, self->size*self->size*sizeof(int) );

    FloydWarshall(self, myMatrix, distance);



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
    free(myMatrix);
    free(distance);

}


void ConstructPair(int myTabOdd[], int numberOfOdd) {
    printf("\n\n");
    for(int i = 0; i < numberOfOdd; i++) {
        for(int j = i+1; j < numberOfOdd; j++) {
            printf("%d, %d\n", myTabOdd[i], myTabOdd[j]);
        }
        printf("\n");
    }

}




