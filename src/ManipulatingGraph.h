//
// 
//

#ifndef GRAF_MANIPULATINGGRAPH_H
#define GRAF_MANIPULATINGGRAPH_H

#include "structure.h"

void graph_create (struct Graph *self, int maxNode, bool directed);
void graph_destroy (struct Graph *self);

void graph_add_node(struct Graph *self, int node);

void graph_remove_node(struct Graph *self, int node);
void graph_print(struct Graph *self);
void save_graph(struct Graph *self, char fileString[]);

int findNode(struct Graph *self, int node);

//----- GRAPH LOAD FUNCTION ------//
void graph_load (char file[], struct Graph *self);
void createEdgesFromLoad(struct Graph *self, char *filename);
int createGraphFromLoad(struct Graph *self, char *filename);
int getNode(struct Graph *self, char* line, bool addIsActive);
void getEdge(struct Graph *self,char* line);

#endif //GRAF_MANIPULATINGGRAPH_H
