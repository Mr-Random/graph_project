//
// Created by Corentin on 31/10/2017.
//

#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "structure.h"
#include "ManipulatingGraph.h"



void knowTheDegree(struct Graph *self, int tabDegree[]) {
    for (int i = 0; i < self->size; i++) {
        struct Neighbour *curr = self->array[i].adjList;
        while (curr) {
            tabDegree[i]++;
            curr = curr->nextNeighbour;
        }
    }
}

void knowTabOdd(struct Graph *self, int myTabOdd[], int tabDegree[]) {
    int j = 0;
    for (int i = 0; i < self->size; i++) {
        printf("[%d] = %d\n", i, tabDegree[i]);
        if (tabDegree[i] % 2 != 0) {
            myTabOdd[j] = i;
            j++;
        }
    }
}

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


void ConstructPair(int myTabOdd[], int numberOfOdd, int numberOfPossiblePair, int myTabPair[numberOfPossiblePair][2]) {
    int k = 0;
    for(int i = 0; i < numberOfOdd; i++) {
        for(int j = i+1; j < numberOfOdd; j++) {
            myTabPair[k][0] = myTabOdd[i];
            myTabPair[k][1] = myTabOdd[j];
            k++;
        }
        printf("\n");
    }

}

void ConstructAllPairing(int numberOfPossiblePair, int myTabPair[numberOfPossiblePair][2],
                         int numberOfPossiblePairings, int numberOddDegreeDividedByTwo, int myTabPairing[numberOfPossiblePairings][numberOddDegreeDividedByTwo][2]) {


    for (int i = 0; i < numberOfPossiblePairings; i++) {
        for (int j = 0; j < numberOddDegreeDividedByTwo; j++) {

            for (int x = 0; x < numberOfPossiblePair; x++) {

                // IF J EQUALS 0 IT MEANS WE DON'T NEED TO LOOK IF WE ARE GOING TO INSERT A NUMBER TWICE
                // WE JUST TAKE THE FIRST PAIR THAT WE SEE IN "myTabPair"
                if (j == 0 && myTabPair[x][0] != -1 && myTabPair[x][1] != -1) {
                    myTabPairing[i][j][0] = myTabPair[x][0];
                    myTabPairing[i][j][1] = myTabPair[x][1];

                    myTabPair[x][0] = -1;
                    myTabPair[x][1] = -1;
                    break;
                }
                //OTHERWISE WE WILL HAVE TOO LOOK IF WE DON'T INSERT A NUMBER THAT IS ALREADY IN "myTabPairing"
                else {
                    bool insert = true;
                    if (myTabPair[x][0] != -1 && myTabPair[x][1] != -1) {
                        int currentPlaceJ = j;

                        while (currentPlaceJ != 0) {
                            currentPlaceJ--;
                            if (myTabPairing[i][currentPlaceJ][0] == myTabPair[x][0] ||
                                    myTabPairing[i][currentPlaceJ][1] == myTabPair[x][1] ||
                                    myTabPairing[i][currentPlaceJ][0] == myTabPair[x][1] ||
                                    myTabPairing[i][currentPlaceJ][1] == myTabPair[x][0]) {
                                insert = false;
                                break;
                            }

                        }


                    }
                    else {
                        insert = false;
                    }

                    if (insert == true) {
                        myTabPairing[i][j][0] = myTabPair[x][0];
                        myTabPairing[i][j][1] = myTabPair[x][1];

                        myTabPair[x][0] = -1;
                        myTabPair[x][1] = -1;
                        break;
                    }
                }
            }
        }
    }
}

long factorial(int n) {
    if (n == 0)
        return 1;
    else
        return(n * factorial(n-1));
}

void solveChineseProblem(struct Graph *self) {

    int numberOddDegree = 0;

    int tabDegree[self->size];
    memset( tabDegree, 0, self->size*sizeof(int) );

    //KNOW THE DEGREE
    knowTheDegree(self, tabDegree);

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

    knowTabOdd(self, myTabOdd, tabDegree);


    int numberOfPossiblePair = factorial(numberOddDegree)/(factorial(2)*(factorial(numberOddDegree - 2)));
    printf("Number of possible pair : %d\n\n", numberOfPossiblePair);

    int myTabPair[numberOfPossiblePair][2];
    memset(myTabPair, 0, numberOfPossiblePair*2*sizeof(int) );

    //CONSTRUCT PAIR
    ConstructPair(myTabOdd, numberOddDegree, numberOfPossiblePair, myTabPair);

    //PRINT
    for (int i = 0; i < numberOfPossiblePair; i++) {
        printf("%d, %d\n", myTabPair[i][0], myTabPair[i][1]);
    }

    //ALL PAIRING POSSIBLE FOR GRAPH
    int numberOfPossiblePairings = factorial(numberOddDegree)/(pow(2, numberOddDegree/2) * (numberOddDegree / 2));
    printf("Number of possible pair : %d\n\n", numberOfPossiblePairings);

    int myTabPairing[numberOfPossiblePairings][numberOddDegree/2][2];
    memset(myTabPairing, 0, numberOfPossiblePairings*numberOddDegree/2*2*sizeof(int) );

    ConstructAllPairing(numberOfPossiblePair, myTabPair, numberOfPossiblePairings, numberOddDegree/2, myTabPairing);


    for (int i = 0; i < numberOfPossiblePairings; i++) {
        printf("[");
        for (int j = 0; j < numberOddDegree/2; j++) {
            printf("(%d, %d)  ", myTabPairing[i][j][0], myTabPairing[i][j][1]);
        }
        printf("]\n");
    }




            //MATRIX
    int myMatrix[self->size][self->size];
    memset(myMatrix, 0, self->size*self->size*sizeof(int) );

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




}










