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

int BestDistanceBetweenTwo(struct Graph *self, int distance[self->size][self->size], int source, int dest) {
    return distance[source][dest];
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

int GetIndexMinimumPairing (struct Graph *self, int distance[self->size][self->size],
                       int numberOfPossiblePairings, int numberOddDegreeDividedByTwo, int myTabPairing[numberOfPossiblePairings][numberOddDegreeDividedByTwo][2] ) {

    int result = 0;
    int minimumPath = INT_MAX;

    for (int i = 0; i < numberOfPossiblePairings; i++) {
        int somme = 0;

        for (int j = 0; j < numberOddDegreeDividedByTwo; j++) {
            somme += distance[myTabPairing[i][j][0]][myTabPairing[i][j][1]];
        }
        if (somme < minimumPath) {
            minimumPath = somme;
            result = i;
        }
    }

    return result;
}


long factorial(int n) {
    if (n == 0)
        return 1;
    else
        return(n * factorial(n-1));
}


int* printAllPathsUtil(int u, int d, bool visited[],
                       int path[], int path_index, struct Graph *self, int myMatrix[self->size][self->size], int valueMinimumPairing, int *sizeOfBestPath) {

    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    int myBestPath[path_index];
    memset(myBestPath, 0, path_index*sizeof(int) );

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d)
    {
        int sommePath = 0;
        for (int i = 0; i < path_index; i++) {
            printf("%d ", path[i]);

            if (i != path_index - 1) {
                sommePath += myMatrix[path[i]][path[i + 1]];
            }
        }
        if (sommePath == valueMinimumPairing) {
            *sizeOfBestPath = path_index;
            for (int i = 0; i < path_index; i++) {
                myBestPath[i] = path[i];
            }
        }
        printf("\t %d \n", sommePath);
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        struct Neighbour *n =  self->array[u].adjList;

        while(n != NULL) {
            int i = findNode(self, n->neighbour);
            if (!visited[i]) {
                printAllPathsUtil(i, d, visited, path, path_index, self, myMatrix, valueMinimumPairing, &sizeOfBestPath);
            }
            n = n->nextNeighbour;
        }

    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;

    return myBestPath;

}



int* printAllPaths(struct Graph *self, int s, int d, int myMatrix[self->size][self->size], int valueMinimumPairing, int *sizeOfBestPath) {
    bool visited[self->size];

    // Create an array to store paths
    int path[self->size];
    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < self->size; i++)
        visited[i] = false;

    // Call the recursive helper function to print all paths
    int* result;
    int pointeurOfBestPath = 0;
    result = printAllPathsUtil(s, d, visited, path, path_index, self, myMatrix, valueMinimumPairing, &pointeurOfBestPath);
    *sizeOfBestPath = 42;
    printf("ouiiiiiiiiiiiii %d", pointeurOfBestPath);
    return result;
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
        printf("]\n\n");
    }




    //MATRIX
    int myMatrix[self->size][self->size];
    memset(myMatrix, 0, self->size*self->size*sizeof(int) );

    ConvertToMatrix(self, myMatrix);

    //GET MATRIX OF SHORTEST PATH
    int distance[self->size][self->size];
    memset(distance, 0, self->size*self->size*sizeof(int) );

    FloydWarshall(self, myMatrix, distance);


    int indexMinimumPairing = GetIndexMinimumPairing(self, distance, numberOfPossiblePairings, numberOddDegree/2, myTabPairing);

    for (int i = 0; i < numberOddDegree/2; i++) {
        int valueMinimumPairing = distance[myTabPairing[indexMinimumPairing][i][0]][myTabPairing[indexMinimumPairing][i][1]];

        printf("Value minimum pairing : %d \n", valueMinimumPairing);
        int sizeOfBestPath = 0;
        int * bestPath = printAllPaths(self, myTabPairing[indexMinimumPairing][0][0], myTabPairing[indexMinimumPairing][0][1], myMatrix, valueMinimumPairing, &sizeOfBestPath);


        printf("Size of best path : %d\n\n\n\n", sizeOfBestPath);

        break;
    }



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










