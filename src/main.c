#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingLinkedLists.h"
#include "ManipulatingGraph.h"
#include "MenuGraph.h"

/*Commande valgrind:
    valgrind ./main

    options:
        --leak-check=full  : for memory leaks info
        -g                 : for debug info
*/

int main() {

    struct Graph *myGraph = malloc(sizeof(struct Graph));

    MainMenu(myGraph);

    free(myGraph);
}