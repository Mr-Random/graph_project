#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingLinkedLists.h"
#include "ManipulatingGraph.h"

/*Commande valgrind:
    valgrind ./main

    options:
        --leak-check=full  : for memory leaks info
        -g                 : for debug info
*/

void graph_load (char file[], struct Graph *self);
int getNode(struct Graph *self, char* line, bool addIsActive);

int main() {

    //int maxNode = 10;
    //bool directed = false;

    struct Graph *myGraph = malloc(sizeof(struct Graph));

    graph_load("../file.txt", myGraph);

    char test = '1';

    printf("test char %d",test);
    /*graph_create(myGraph, maxNode, directed);
    graph_add_node(myGraph, 7);
    graph_add_node(myGraph, 5);
    graph_add_node(myGraph, 3);
    graph_add_node(myGraph, 1);
    graph_add_node(myGraph, 6);


    graph_add_edge(myGraph, 7, 5, 30);
    graph_add_edge(myGraph, 7, 3, 30);

    graph_remove_edge(myGraph, 7, 5);

    graph_add_edge(myGraph, 7, 6, 30);
    graph_add_edge(myGraph, 6, 5, 30);

    graph_remove_edge(myGraph, 7, 6);

    graph_add_edge(myGraph, 3, 5, 40);
    graph_add_edge(myGraph, 5, 3, 40);

    graph_remove_node(myGraph, 3);*/

    //graph_print(myGraph);


    //graph_destroy(myGraph);
    

    printf("\n--------------------\n");
    graph_print(myGraph);

    /* Save Graf in a file */ 
    //save_graph(myGraph);    
    graph_destroy(myGraph);
    free(myGraph);
}

void createEdgesFromLoad(struct Graph *self, char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
        //stderr("Error !");
    }
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (i > 4) {
            //printf("2 - %s", line);
            getEdge(self,line);
        }
        i++;
    }

    fclose(fp);        
    if (line)
        free(line);
}


int createGraphFromLoad(struct Graph *self, char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int maxNode = 0;
    bool directed = false;

    int inOrderToGoBack;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
        //stderr("Error !");
    }

    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        
        if (i == 1) {
            maxNode = atoi(line);
        }
        else if(i == 3) {
            if (strcmp("y\n", line) == 0) {
                directed = true;
            } else {
                directed = false;
            }
            graph_create(self, maxNode, directed);
        }
        
        if(i > 4){
            getNode(self,line,true);
            printf("\n");
        }
        
        if (i < 5) {
            inOrderToGoBack += read + 1;
        }
        i++;
    }

    fclose(fp);
    if (line)
        free(line);

    return inOrderToGoBack;
}

/* Function : Load a GRAF from a txt file */
void graph_load (char file[], struct Graph *self) {

    createGraphFromLoad(self, file);
    printf("\n");
    createEdgesFromLoad(self, file);
    printf("\n");
}

int getNode(struct Graph *self, char* line, bool addIsActive){

    char bufNode[10];
    int i = 0;
    
    memset(bufNode,0, sizeof bufNode);//< test de clean mem

    while(line[i] != ':'){
        //printf("line[%d] = %c\n",i,line[i]);
        i++;
    } 
    strncpy(bufNode,line,i);
    
    int node = atoi(bufNode);
    printf("Node = %d\n",node);

    /* Add Node */
    if(addIsActive)
        graph_add_node(self,node); 

    return node;
}

void getEdge(struct Graph *self,char* line){

    /* Set char* buffer */
    char bufNeighb[10];
    char bufWeight[10];

    //memset(bufWeight,0, sizeof bufWeight);

    /* Init var */
    int size = 0;
    int i = 0;
    int neighbour = 0;
    int weight = 0;
    
    int currentNode = getNode(self,line,false);

    while(line[i] != '\0'){
        if(line[i] == '('){
            
            /* Clear Buffer */
            memset(bufNeighb,0, sizeof bufNeighb);
            memset(bufWeight,0, sizeof bufWeight);

            /* Reset size */
            size = 0;
            i++;//< inc 1 for get the first number of the neighbour

            while(line[i] != '/'){
                bufNeighb[size] = line[i];
                size++;
                i++;
            }
            neighbour = atoi(bufNeighb);
            printf("Neighbour = %d\n",neighbour);

            /* Reset size */
            size = 0;
            i++;//< inc 1 for get the first number of the weight

            while(line[i] != ')'){
                bufWeight[size] = line[i];
                size++;
                i++;
            }
            weight = atoi(bufWeight);
            printf("Weight = %d\n",weight);
            
            /* Add new Edge */
            graph_add_edge(self,currentNode,neighbour,weight);

            

            printf("\n");
        }
        i++;
    }

}
