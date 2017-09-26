#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingLinkedLists.h"
#include "ManipulatingGraph.h"

int main() {

    printf("test !!");
    int maxNode = 10;
    bool directed = false;

    struct Graph *myGraph = malloc(sizeof(struct Graph));
    /*graph_create(myGraph, 10, directed);

    graph_add_node(myGraph);
    graph_add_edge(myGraph, 1, 2);*/

    //graph_load("F:\\Users\\Corentin\\Downloads\\file.txt");

    graph_destroy(myGraph);

    //Simple Test of Menu
    printf("\nEnter a number :\n");
    printf("1: graph load\n");

    char choice = fgetc(stdin);
    
    switch(choice){
        case '1':; //do something
        break;
    }
}