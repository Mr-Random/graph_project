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

    struct Graph *myGraph = malloc(sizeof(struct Graph));

    graph_create(myGraph, 10, false);
    graph_load("../file.txt", myGraph);

    char test = '1';

    char *maxNode = fgets(maxNode,10,stdin);
    int intMaxNode = atoi(maxNode);
    printf("maxNode = %d",maxNode);

    /*graph_create(myGraph, 10, false);
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

    printf("\n--------------------\n");
    graph_print(myGraph);

    /* Save Graf in a file */ 
    save_graph(myGraph);    
    
    /* Destroy and Free */
    graph_destroy(myGraph);
    free(myGraph);
}

void MainMenu(){
    char choice;
    
    printf("=== Menu ===\n\n");
    printf("0 | Create Graph \n");
    printf("1 | Add node \n");
    printf("2 | Remove node \n");
    printf("3 | Add Edge \n");
    printf("4 | Remove Edge \n");
    printf("5 | Load Graph \n");
    printf("6 | Save Graph \n");

    choice = fgetc(stdin);

    switch(choice){
        case '0':;
        break;

        case '1':;
        break;

        case '2':;
        break;

        case '3':;
        break;

        case '4':;
        break;

        case '5':;
        break;
        
        case '6':;
        break;
    }
}

void MenuCreateGraph(){
    struct Graph *myGraph = malloc(sizeof(struct Graph));
}