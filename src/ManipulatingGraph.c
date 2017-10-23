#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "ManipulatingGraph.h"
#include "ManipulatingLinkedLists.h"

void graph_add_node(struct Graph *self, int node) {

    if (self->size == self->nbMaxNodes) {
        self->nbMaxNodes *= 2;
        struct Node *data = calloc(self->nbMaxNodes, sizeof(Node));
        memcpy(data, self->array, self->size * sizeof(Node));

        //Free old tab memory 
        graph_destroy(self);

        //Affected new data to array
        self->array = data;
    }

    self->array[self->size].adjList = NULL;
    self->array[self->size].node = node;
    self->size += 1;
}

void graph_add_edge(struct Graph *self, int src, int dest, int weight, bool firstTime) {

    int indexSource = findNode(self, src);
    int indexDestination = findNode(self, dest);

    if (indexSource == -1) {
        printf("Source invalid !\n");
        return;
    }

    if (indexDestination == -1) {
        printf("Destination invalid !\n");
        return;
    }

    if (self->isDirected == false && firstTime == true) {
        graph_add_edge(self, dest, src, weight, false);
    }

    struct Neighbour *node = malloc(sizeof(struct Neighbour));
    node->neighbour = dest;
    node->nextNeighbour = NULL;

    if (self->array[indexSource].adjList == NULL) {
        self->array[indexSource].adjList = node;
        self->array[indexSource].adjList->weight = weight;
        return;
    }

    struct Neighbour *tmp  = self->array[indexSource].adjList;
    
    while (tmp->nextNeighbour != NULL) {
        tmp = tmp->nextNeighbour;
    }

    tmp->nextNeighbour = node;
    tmp->nextNeighbour->weight = weight;
    
    node->previousNeighbour = tmp;
}

void graph_remove_edge(struct Graph *self, int src, int dest) {

    int indexSource = findNode(self, src);
    int indexDestination = findNode(self, dest);

    if (indexSource == -1) {
        printf("Source invalid !\n");
        return;
    }

    if (indexDestination == -1) {
        printf("Destination invalid !\n");
        return;
    }

    browseDelete(self, indexSource, dest);

    if(!self->isDirected) {
        browseDelete(self, indexDestination, src);
    }

}

void graph_remove_node(struct Graph *self, int node) {
    int indexNode = findNode(self, node);

    if (indexNode == -1) {
        printf("Node invalid !\n");
        return;
    }

    //remove edges
    for (int i = 0; i < self->size; i++) {
        browseDelete(self, i, node);
    }

    //remove node
    if (self->array[indexNode].adjList != NULL) {

        struct Neighbour* tmp;

        while (self->array[indexNode].adjList != NULL)
        {
            tmp = self->array[indexNode].adjList;
            self->array[indexNode].adjList = self->array[indexNode].adjList->nextNeighbour;
            free(tmp);
        }
    }
    free(self->array[indexNode].adjList);

    //move back of all value from index of node in array to the end of array
    for (int i = indexNode ; i < self->size-1 ; i++) {
        self->array[i] = self->array[i + 1];
    }
    self->size--;
}

/* Function that save the  current Graph in a file using fprintf */
/* it's the same function as print_graph but instead of 
   displaying on the standard outup we write to a file */
   void save_graph(struct Graph *self, char fileString[]) {

    FILE* file;

    file = fopen(fileString,"w");

    if(!file)
        perror("fopen");

    if(file != NULL){
        
        fprintf(file,"# maximum number of nodes\n");
        fprintf(file,"%d\n", self->nbMaxNodes);
        fprintf(file,"# directed\n");
        fprintf(file,"n\n");
        fprintf(file,"# node: neighbours\n");

        for (int i = 0; i < self->size; i++) {
            fprintf (file,"%d:", self->array[i].node);
            struct Neighbour *curr = self->array[i].adjList;
            while (curr) {
                if (curr->nextNeighbour == NULL) {
                    fprintf(file," (%d/%d)", curr->neighbour, curr->weight);
                }
                else {
                    fprintf(file," (%d/%d),", curr->neighbour, curr->weight);
                }
                curr = curr->nextNeighbour;
            }
            fprintf(file,"\n");
        }

        fclose(file);

    }else{
        fprintf(stderr,"Error : Impossible to open the file\n");
        //return(-1);
    } 

}

/* Function that print the graph in stdin */
void graph_print(struct Graph *self) {
    
    printf("# maximum number of nodes\n");
    printf("%d\n", self->nbMaxNodes);
    printf("# directed\n");
    printf("n\n");
    printf("node: neighbours\n");

    for (int i = 0; i < self->size; i++) {
        printf ("%d: ", self->array[i].node);
        struct Neighbour *curr = self->array[i].adjList;
        while (curr) {
            if (curr->nextNeighbour == NULL) {
                printf("(%d/%d)", curr->neighbour, curr->weight);
            }
            else {
                printf("(%d/%d),", curr->neighbour, curr->weight);
            }
            curr = curr->nextNeighbour;
        }
        printf("\n");
    }
    
}

/* Function used to remove edges by browsing adjacent list */
/* we go through the adjency list and see if one of the neighbors 
   corresponds to the destination node of our edges to be deleted */
void browseDelete(struct Graph *self, int src, int dest){
    int index = 0;
    struct Neighbour *n =  self->array[src].adjList;

    while(n != NULL){

        if(n->neighbour == dest){

           if (index == 0) {
                self->array[src].adjList = n->nextNeighbour;
           }
           else {
                n->previousNeighbour->nextNeighbour = n->nextNeighbour; 
           }
           free(n);
           break;
        }
        /* Go to the next Neighbour */
        n = n->nextNeighbour;
        index++;
    } 
}

int findNode(struct Graph *self, int node) {
    int i;
    for (i = 0; i < self->size; i++) {
        if (self->array[i].node == node) {
            return i;
        }
    }
    return -1;
}


/* GRAPH LOAD FUNCTION */
/* Function used to load a graph from a txt file */

/* Main function that calls all the others */
void graph_load (char file[], struct Graph *self) {
    
    createGraphFromLoad(self, file);
    printf("\n");
    createEdgesFromLoad(self, file);
    printf("\n");
}

/* Function called first in graph_load to create the graph from the recovered nodes */ 
void createEdgesFromLoad(struct Graph *self, char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
        if (i > 4) {//< line greater than four are the ones that define the graph
            getEdge(self,line);
        }
        i++;
    }

    fclose(fp);        
    if (line)
        free(line);
}

/* Function called second in graph_load to create the graph from the recovered edges */
int createGraphFromLoad(struct Graph *self, char *filename) {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    int maxNode = 0;
    bool directed = false;

    int inOrderToGoBack = -1;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    int i = 0;
    /* Get each line from the file */
    while ((read = getline(&line, &len, fp)) != -1) {
        
        if (i == 1) {//< line 1 is the number of nodes
            maxNode = atoi(line);
        }
        else if(i == 3) {//< line 3 is the graph type information (directed: y/n)
            if (strcmp("y\n", line) == 0) {
                directed = true;
            } else {
                directed = false;
            }
            graph_create(self, maxNode, directed);
        }
        
        if(i > 4){//< line greater than four are the ones that define the graph
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

/* Function that retrieves nodes by reading file */
/* We retrieve each line read from the file, then we read 
   them until found ':'which means the end of the name of node */
int getNode(struct Graph *self, char* line, bool addIsActive){

    char bufNode[10];
    int i = 0;
    
    memset(bufNode,0, sizeof bufNode);

    while(line[i] != ':'){
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

/* Function that retrieves edges by reading file */
/* We retrieve each line read from the file, then we read them until 
   found '(' which means the beginning of edge delcaration then we read 
   the information between this parentheses that correspond to an edge */
void getEdge(struct Graph *self,char* line){

    /* Set char* buffer */
    char bufNeighb[10];
    char bufWeight[10];

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
            graph_add_edge(self,currentNode,neighbour,weight, false);

            printf("\n");
        }
        i++;
    }

}

