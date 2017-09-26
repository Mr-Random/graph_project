//
// Created by Corentin on 24/09/2017.
//

#ifndef GRAF_MANIPULATINGLINKEDLISTS_H
#define GRAF_MANIPULATINGLINKEDLISTS_H

#include "structure.h"

void graph_create (struct Graph *self, int maxNode, bool directed);
void graph_destroy (struct Graph *self);
void graph_load (char file[]);



#endif //GRAF_MANIPULATINGLINKEDLISTS_H
