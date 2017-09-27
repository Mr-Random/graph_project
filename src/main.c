#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingLinkedLists.h"
#include "ManipulatingGraph.h"

int main() {

    int maxNode = 10;
    bool directed = false;

    struct Graph *myGraph = malloc(sizeof(struct Graph));
    graph_create(myGraph, 10, directed);

    graph_add_node(myGraph);
    graph_add_node(myGraph);
    graph_add_node(myGraph);

    graph_add_edge(myGraph, 0, 1, 30);

    graph_print(myGraph);
    //graph_load("F:\\Users\\Corentin\\Downloads\\file.txt");


    graph_destroy(myGraph);

}