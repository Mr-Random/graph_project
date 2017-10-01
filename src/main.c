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

int main() {

    int maxNode = 10;
    bool directed = false;




    struct Graph *myGraph = malloc(sizeof(struct Graph));


    graph_load("F:\\Users\\Corentin\\Downloads\\file.txt", myGraph);

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
    free(myGraph);
}

void createEdgesFromLoad(struct Graph *self, char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    bool firstTime = true;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
        //stderr("Error !");
    }
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (i > 4) {
            printf("2 - %s", line);
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
    bool firstTime = true;

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
        printf("1 - %s", line);

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

}