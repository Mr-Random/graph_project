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
int main() {

    int maxNode = 10;
    bool directed = false;

    struct Graph *myGraph = malloc(sizeof(struct Graph));
    graph_create(myGraph, maxNode, directed);

    graph_add_node(myGraph);
    graph_add_node(myGraph);
    graph_add_node(myGraph);
    graph_add_node(myGraph);
    graph_add_node(myGraph);


    graph_add_edge(myGraph, 0, 1, 30);
    graph_add_edge(myGraph, 0, 2, 30);

    graph_remove_edge(myGraph, 0, 1);

    graph_add_edge(myGraph, 0, 3, 30);
    graph_add_edge(myGraph, 0, 4, 30);

    graph_remove_edge(myGraph, 0, 3);
    graph_print(myGraph);
    //graph_load("F:\\Users\\Corentin\\Downloads\\file.txt");

    graph_destroy(myGraph);
    free(myGraph);
}