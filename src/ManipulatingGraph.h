//
// Created by Corentin on 26/09/2017.
//

#ifndef GRAF_MANIPULATINGGRAPH_H
#define GRAF_MANIPULATINGGRAPH_H

#include "structure.h"

void graph_add_node(struct Graph *self, int node);
void graph_add_edge(struct Graph *self, int src, int dest, int weight);
void graph_remove_edge(struct Graph *self, int src, int dest);
void graph_remove_node(struct Graph *self, int node);
void graph_print(struct Graph *self);
void save_graph(struct Graph *self);

void browseDelete(struct Graph *self, int src, int dest);
int findNode(struct Graph *self, int node);


#endif //GRAF_MANIPULATINGGRAPH_H
