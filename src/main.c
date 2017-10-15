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

void MainMenu(struct Graph *self);
void MenuCreateGraph(struct Graph *self);

int main() {

    struct Graph *myGraph = malloc(sizeof(struct Graph));

    MainMenu(myGraph);

    free(myGraph);
}

void MainMenu(struct Graph *self){
    char choice;

    printf("=== Menu ===\n\n");
    printf("0 | Create Graph \n");
    printf("1 | Add node \n");
    printf("2 | Remove node \n");
    printf("3 | Add Edge \n");
    printf("4 | Remove Edge \n");
    printf("5 | Load Graph \n");
    printf("6 | Save Graph \n");
    printf("7 | View Graph \n");
    printf("8 | Exit\n");

    choice = fgetc(stdin);


    switch(choice){
        case '0':
            MenuCreateGraph(self);
            MainMenu(self);
            break;

        case '1':
            MenuAddNode(self);
            MainMenu(self);
            break;

        case '2':
            MenuRemoveNode(self);
            MainMenu(self);
            break;

        case '3':
            MenuAddEdge(self);
            MainMenu(self);
            break;

        case '4':
            MenuRemoveEdge(self);
            MainMenu(self);
            break;

        case '5':
            MenuLoadGraph(self);
            MainMenu(self);
            break;

        case '6':
            MenuSaveGraph(self);
            MainMenu(self);
            break;

        case '7':
            graph_print(self);
            MainMenu(self);
            break;

        case '8':;
            graph_destroy(self);
            return;

        default:
            MainMenu(self);
            break;

    }


}


static void purger(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {}
}

static void clean (char *chaine)
{
    char *p = strchr(chaine, '\n');
    if (p) {
        *p = 0;
    }
    else {
        purger();
    }
}

void MenuCreateGraph(struct Graph *self) {

    int nombreMaxNodes;
    char maxNodes[5];
    int ret;

    printf("=== Creating Graph ===\n\n");

    printf("Number max of nodes  : \n");
    do
    {
        fgets(maxNodes, sizeof maxNodes, stdin);

        clean(maxNodes);

        ret = sscanf(maxNodes, "%d", &nombreMaxNodes);
    } while (ret != 1);

    char directed;

    bool directedBool;
    while (directed != 'y' && directed != 'n') {
        printf("Graph directed ? (y/n) : ");
        directed = fgetc(stdin);

        switch (directed) {
            case 'y':;
                directedBool = true;
                break;

            case 'n':;
                directedBool = false;
                break;

        }
    }



    graph_create(self, nombreMaxNodes, directedBool);

}

void MenuAddNode(struct Graph *self) {
    int nombreNodeToAdd;
    char nodeToAdd[5];
    int ret;

    printf("=== Add Node ===\n\n");

    printf("Node to add : \n");
    do
    {
        fgets(nodeToAdd, sizeof nodeToAdd, stdin);

        clean(nodeToAdd);

        ret = sscanf(nodeToAdd, "%d", &nombreNodeToAdd);
    } while (ret != 1);

    graph_add_node(self, nombreNodeToAdd);
}

void MenuRemoveNode(struct Graph *self) {
    int nombreNodeToRemove;
    char nodeToRemove[5];
    int ret;

    printf("=== Remove Node ===\n\n");

    printf("Node to remove : \n");
    do
    {
        fgets(nodeToRemove, sizeof nodeToRemove, stdin);

        clean(nodeToRemove);

        ret = sscanf(nodeToRemove, "%d", &nombreNodeToRemove);
    } while (ret != 1);

    graph_remove_node(self, nombreNodeToRemove);
}

void MenuAddEdge(struct Graph *self) {

    int nombreNodeSource;
    char nodeSource[5];
    int ret1;

    int nombreNodeDest;
    char nodeDest[5];
    int ret2;

    int nombreWeight;
    char weight[5];
    int ret3;

    printf("=== Add Edge ===\n\n");

    printf("Source node : \n");
    do
    {
        fgets(nodeSource, sizeof nodeSource, stdin);

        clean(nodeSource);

        ret1 = sscanf(nodeSource, "%d", &nombreNodeSource);
    } while (ret1 != 1);

    printf("Destination node : \n");
    do
    {
        fgets(nodeDest, sizeof nodeDest, stdin);

        clean(nodeDest);

        ret2 = sscanf(nodeDest, "%d", &nombreNodeDest);
    } while (ret2 != 1);

    printf("Weight of edge : \n");
    do
    {
        fgets(weight, sizeof weight, stdin);

        clean(weight);

        ret3 = sscanf(weight, "%d", &nombreWeight);
    } while (ret3 != 1);

    graph_add_edge(self, nombreNodeSource, nombreNodeDest, nombreWeight, true);
}

void MenuRemoveEdge(struct Graph *self) {
    int nombreNodeSource;
    char nodeSource[5];
    int ret1;

    int nombreNodeDest;
    char nodeDest[5];
    int ret2;

    printf("=== Remove Edge ===\n\n");

    printf("Source node : \n");
    do
    {
        fgets(nodeSource, sizeof nodeSource, stdin);

        clean(nodeSource);

        ret1 = sscanf(nodeSource, "%d", &nombreNodeSource);
    } while (ret1 != 1);

    printf("Destination node : \n");
    do
    {
        fgets(nodeDest, sizeof nodeDest, stdin);

        clean(nodeDest);

        ret2 = sscanf(nodeSource, "%d", &nombreNodeDest);
    } while (ret2 != 1);

    graph_remove_edge(self, nombreNodeSource, nombreNodeDest);
}

void MenuLoadGraph(struct Graph *self)  {
    char maxLink[256];
    int ret;

    printf("=== Loading Graph ===\n\n");

    printf("Link of load : \n");
    do
    {
        fgets(maxLink, sizeof maxLink, stdin);

        clean(maxLink);

    } while (ret != 1);

    graph_load(maxLink, self);
}

void MenuSaveGraph(struct Graph *self) {

    char maxLink[256];
    int ret;

    printf("=== Saving Graph ===\n\n");

    printf("Link of load : \n");
    do
    {
        fgets(maxLink, sizeof maxLink, stdin);

        clean(maxLink);

    } while (ret != 1);

    save_graph(self, maxLink);
}