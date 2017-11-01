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






    graph_create(myGraph, 12, true);

    graph_add_node(myGraph, 0);
    graph_add_node(myGraph, 1);
    graph_add_node(myGraph, 2);
    graph_add_node(myGraph, 3);

    graph_add_edge(myGraph, 0, 2, -2);
    graph_add_edge(myGraph, 1, 2, 3);
    graph_add_edge(myGraph, 1, 0, 4);
    graph_add_edge(myGraph, 2, 3, 2);
    graph_add_edge(myGraph, 3, 1, -1);


    //graph_print(myGraph);

    solveChineseProblem(myGraph);
    graph_destroy(myGraph);

    //MainMenu(&myGraph);

    free(myGraph);
}