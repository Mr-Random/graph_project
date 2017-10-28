//
// 
//

#ifndef GRAF_MANIPULATINGLINKEDLISTS_H
#define GRAF_MANIPULATINGLINKEDLISTS_H

#include "structure.h"

void graph_add_edge(struct Graph *self, int src, int dest, int weight, bool firstTime);
void graph_remove_edge(struct Graph *self, int src, int dest);
void browseDelete(struct Graph *self, int src, int dest);

#endif //GRAF_MANIPULATINGLINKEDLISTS_H
