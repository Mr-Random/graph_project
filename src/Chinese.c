//
// Created by Corentin on 31/10/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <mem.h>
#include "structure.h"
#include "ManipulatingGraph.h"
#include "ManipulatingLinkedLists.h"

struct PathNode {
    int node;
    struct PathNode *nextNode;
};

struct Path {
    int numberOfNode;
    struct PathNode *adjList;
};

struct array {
    int *data;
    int capacity;
    int size;
};


//Function for array

void array_create(struct array *self) {
    self->size = 0;
    self->capacity = 100;

    self->data = calloc(self->capacity, sizeof(int));
}

void array_destroy(struct array *self) {
    free(self->data);
}

void array_add(struct array *self, int value) {
    if (self->size == self->capacity) {
        self->capacity *= 2;
        int *data = calloc(self->capacity, sizeof(int));
        memcpy(data, self->data, self->size * sizeof(int));
        free(self->data);
        self->data = data;
    }
    self->data[self->size] = value;
    self->size += 1;

}

void array_insert(struct array *self, int value, int index) {
    array_add(self, self->data[self->size]);
    for (size_t i = self->size-1 ; i > index ; i--)
        self->data[i] = self->data[i-1];

    self->data[index] = value;
}







void path_destroy (struct Path *self) {
    if (self->adjList != NULL) {

        struct PathNode* tmp;

        for (int i = 0; i < self->numberOfNode; i++) {
            tmp = self->adjList;
            self->adjList = self->adjList->nextNode;
            free(tmp);
        }
    }
    free(self->adjList);

}

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

void add_in_structure(struct Path *myPath, int valueToInsert, int index) {
    struct PathNode *node = malloc(sizeof(struct PathNode));

    if (index == 0) {
        myPath->adjList = node;
        myPath->adjList->node = valueToInsert;
        myPath->adjList->nextNode = NULL;
        return;
    }

    struct PathNode *tmp  = myPath->adjList;

    for (int i = 0; i < index-1; i++) {
        tmp = tmp->nextNode;
    }

    tmp->nextNode = node;
    tmp->nextNode->node = valueToInsert;

}

void printAllPathsUtil(int u, int d, bool visited[],
                       int path[], int path_index, struct Graph *self, int myMatrix[self->size][self->size], int valueMinimumPairing, struct Path *myPath) {

    // Mark the current node and store it in path[]
    visited[u] = true;
    path[path_index] = u;
    path_index++;

    // If current vertex is same as destination, then print
    // current path[]
    if (u == d)
    {
        int sommePath = 0;
        for (int i = 0; i < path_index; i++) {


            if (i != path_index - 1) {
                sommePath += myMatrix[path[i]][path[i + 1]];
            }
        }
        if (sommePath == valueMinimumPairing) {

            myPath->numberOfNode = path_index;
            myPath->adjList = NULL;
            for (int i = 0; i < path_index; i++) {
                add_in_structure(myPath, path[i], i);
            }
            return;
        }
    }
    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        struct Neighbour *n =  self->array[u].adjList;

        while(n != NULL) {
            int i = findNode(self, n->neighbour);
            if (!visited[i]) {
                printAllPathsUtil(i, d, visited, path, path_index, self, myMatrix, valueMinimumPairing, myPath);
            }
            n = n->nextNeighbour;
        }

    }

    // Remove current vertex from path[] and mark it as unvisited
    path_index--;
    visited[u] = false;


}


void printAllPaths(struct Graph *self, int s, int d, int myMatrix[self->size][self->size], int valueMinimumPairing, struct Path *myPath) {
    bool visited[self->size];

    // Create an array to store paths
    int path[self->size];
    int path_index = 0; // Initialize path[] as empty

    // Initialize all vertices as not visited
    for (int i = 0; i < self->size; i++)
        visited[i] = false;

    // Call the recursive helper function to print all paths

    printAllPathsUtil(s, d, visited, path, path_index, self, myMatrix, valueMinimumPairing, myPath);
}



void exploreTheNode(struct Graph *temp, int indexStart, int start, int i, struct array *myCircuit) {

    int indexlastNodeSource;
    int lastNodeSource;

    int indexCurrentNode = indexStart;
    int currentNode = start;
    do {
        if (indexStart != indexCurrentNode) {
            array_insert(myCircuit, indexCurrentNode, i);
        }
        indexlastNodeSource = indexCurrentNode;
        lastNodeSource = currentNode;

        currentNode = temp->array[indexCurrentNode].adjList->neighbour;
        indexCurrentNode = findNode(temp, currentNode);


        browseDelete(temp, indexlastNodeSource, currentNode);
        browseDelete(temp, indexCurrentNode, lastNodeSource);
        i++;

    } while (indexCurrentNode != indexStart);

    array_insert(myCircuit, indexStart, i++);
}

void printEulerUtil(struct Graph *self, int start) {
    struct Graph *temp = self;

    struct array *myCircuit = malloc(sizeof(struct array));

    array_create(myCircuit);
    int indexSource = findNode(temp, start);
    int source = start;

    int indexlastNodeSource;
    int lastNodeSource;

    int indexCurrentNode = indexSource;
    int currentNode = source;
    do {
        array_add(myCircuit, indexCurrentNode);

        indexlastNodeSource = indexCurrentNode;
        lastNodeSource = currentNode;

        currentNode = temp->array[indexCurrentNode].adjList->neighbour;
        indexCurrentNode = findNode(temp, currentNode);

        browseDelete(temp, indexlastNodeSource, currentNode);
        browseDelete(temp, indexCurrentNode, lastNodeSource);

    } while (indexCurrentNode != indexSource);

    array_add(myCircuit, indexSource);


    for (int i = 0; i < myCircuit->size; i++) {
        if (temp->array[myCircuit->data[i]].adjList != NULL) {
            exploreTheNode(temp, myCircuit->data[i], temp->array[myCircuit->data[i]].node, i, myCircuit);
            i = -1;
        }
    }
    printf("\n\n\n");
    for (int i = 0; i < myCircuit->size; i++) {
        printf("%d / ", myCircuit->data[i]);
    }

    array_destroy(myCircuit);
}


void CaseNonEulerian (struct Graph *self, int tabDegree[self->size], int numberOddDegree, int start) {
        //CONSTRUCTION OF TAB THAT CONTAINS ALL THE ODD NODE
        int myTabOdd[numberOddDegree];
        memset(myTabOdd, 0, numberOddDegree*sizeof(int) );
    
        knowTabOdd(self, myTabOdd, tabDegree);
    
    
        int numberOfPossiblePair = factorial(numberOddDegree)/(factorial(2)*(factorial(numberOddDegree - 2)));

        int myTabPair[numberOfPossiblePair][2];
        memset(myTabPair, 0, numberOfPossiblePair*2*sizeof(int) );
    
        //CONSTRUCT PAIR
        ConstructPair(myTabOdd, numberOddDegree, numberOfPossiblePair, myTabPair);
    
    
        //ALL PAIRING POSSIBLE FOR GRAPH
        int numberOfPossiblePairings = factorial(numberOddDegree)/(pow(2, numberOddDegree/2) * (numberOddDegree / 2));

        int myTabPairing[numberOfPossiblePairings][numberOddDegree/2][2];
        memset(myTabPairing, 0, numberOfPossiblePairings*numberOddDegree/2*2*sizeof(int) );
    
    
        ConstructAllPairing(numberOfPossiblePair, myTabPair, numberOfPossiblePairings, numberOddDegree/2, myTabPairing);
    

    
        //MATRIX
        int myMatrix[self->size][self->size];
        memset(myMatrix, 0, self->size*self->size*sizeof(int) );
    
        ConvertToMatrix(self, myMatrix);
    
        //GET MATRIX OF SHORTEST PATH
        int distance[self->size][self->size];
        memset(distance, 0, self->size*self->size*sizeof(int) );
    
        FloydWarshall(self, myMatrix, distance);
    
    
        int indexMinimumPairing = GetIndexMinimumPairing(self, distance, numberOfPossiblePairings, numberOddDegree/2, myTabPairing);

        struct Graph *temp = self;
        for (int i = 0; i < numberOddDegree/2; i++) {
            struct Path *myPath = malloc(sizeof(struct Path));
            int valueMinimumPairing = distance[myTabPairing[indexMinimumPairing][i][0]][myTabPairing[indexMinimumPairing][i][1]];
    
            printAllPaths(self, myTabPairing[indexMinimumPairing][i][0], myTabPairing[indexMinimumPairing][i][1], myMatrix, valueMinimumPairing, myPath);
    

            struct PathNode *curr = myPath->adjList;
            for (int j = 0; j < myPath->numberOfNode; j++) {

                if (j != myPath->numberOfNode - 1) {
                    graph_add_edge(temp, self->array[curr->node].node, self->array[curr->nextNode->node].node, myMatrix[curr->node][curr->nextNode->node]);
                }

                curr = curr->nextNode;
            }

            path_destroy(myPath);
            free(myPath);
        }
    printEulerUtil(temp, start);
}


void printTrailSemi(struct Graph *self, int start, int end) {
    struct Graph *temp = self;

    struct array *myCircuit = malloc(sizeof(struct array));

    array_create(myCircuit);

    int indexSource = findNode(temp, start);
    int source = start;

    int indexEnd = findNode(temp, end);
    int finish = start;

    int indexlastNodeSource;
    int lastNodeSource;

    int indexCurrentNode = indexSource;
    int currentNode = source;

    do {
        array_add(myCircuit, indexCurrentNode);

        indexlastNodeSource = indexCurrentNode;
        lastNodeSource = currentNode;

        currentNode = temp->array[indexCurrentNode].adjList->neighbour;
        indexCurrentNode = findNode(temp, currentNode);

        browseDelete(temp, indexlastNodeSource, currentNode);
        browseDelete(temp, indexCurrentNode, lastNodeSource);

    } while (indexCurrentNode != indexEnd);

    array_add(myCircuit, indexEnd);

    for (int i = 0; i < myCircuit->size; i++) {
        if (temp->array[myCircuit->data[i]].adjList != NULL) {
            exploreTheNode(temp, myCircuit->data[i], temp->array[myCircuit->data[i]].node, i, myCircuit);
            i = -1;
        }
    }
    printf("\n\n\n");
    for (int i = 0; i < myCircuit->size; i++) {
        printf("%d / ", myCircuit->data[i]);
    }



    array_destroy(myCircuit);
}

void solveChineseProblem(struct Graph *self, int start) {

    int numberOddDegree = 0;

    int tabDegree[self->size];
    memset( tabDegree, 0, self->size*sizeof(int) );

    //KNOW THE DEGREE
    knowTheDegree(self, tabDegree);
    for (int i = 0; i < self->size; i++) {
        if (tabDegree[i] % 2 != 0) {
            numberOddDegree++;
        }
    }




    //Eulerian
    if (numberOddDegree == 0) {
            printEulerUtil(self, start);
    }
    else  {
        if (numberOddDegree == 2) {

            int start;
            int end;
            bool allGoodForStart = false;
            for (int i = 0; i < self->size; i++) {
                if (tabDegree[i] % 2 != 0 && allGoodForStart == false) {
                    start = self->array[i].node;
                    allGoodForStart = true;
                }
                else if (tabDegree[i] % 2 != 0 && allGoodForStart == true) {
                    end = self->array[i].node;
                }
            }

            printTrailSemi(self, start, end);

        }
        else {
            CaseNonEulerian(self, tabDegree, numberOddDegree, start);
        }
    }




}










