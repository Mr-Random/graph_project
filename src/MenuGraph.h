#ifndef GRAF_MENU_H
#define GRAF_MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ManipulatingGraph.h"
#include "ManipulatingLinkedLists.h"


void MainMenu(struct Graph *self);
void purger(void);
void clean (char *chaine);
void MenuCreateGraph(struct Graph *self);
void MenuAddNode(struct Graph *self);
void MenuRemoveNode(struct Graph *self);
void MenuAddEdge(struct Graph *self);
void MenuRemoveEdge(struct Graph *self);
void MenuLoadGraph(struct Graph *self);
void MenuSaveGraph(struct Graph *self);

#endif //GRAF_MENU