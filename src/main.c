#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingLinkedLists.h"
#include "ManipulatingGraph.h"
#include "MenuGraph.h"
#include "Chinese.h"

/*Commande valgrind:
    valgrind ./main

    options:
        --leak-check=full  : for memory leaks info
        -g                 : for debug info
*/

int main() {

    struct Graph *myGraph = malloc(sizeof(struct Graph));






    graph_create(myGraph, 12, false);

    graph_add_node(myGraph, 1);
    graph_add_node(myGraph, 2);
    graph_add_node(myGraph, 3);
    graph_add_node(myGraph, 4);
    graph_add_node(myGraph, 5);
    graph_add_node(myGraph, 6);

    graph_add_edge(myGraph, 1, 2, 45);
    graph_add_edge(myGraph, 5, 6, 54);

    //graph_print(myGraph);

    solveChineseProblem(myGraph);
    graph_destroy(myGraph);

    //MainMenu(&myGraph);

    free(myGraph);
}