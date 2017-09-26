//
// Created by Corentin on 26/09/2017.
//

#ifndef GRAF_MANIPULATINGGRAPH_H
#define GRAF_MANIPULATINGGRAPH_H

#include "structure.h"

void graph_add_node(struct Graph *self);
void graph_add_edge(struct Graph *self, int src, int dest);

#endif //GRAF_MANIPULATINGGRAPH_H
