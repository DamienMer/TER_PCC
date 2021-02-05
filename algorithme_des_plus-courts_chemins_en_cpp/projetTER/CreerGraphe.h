#ifndef DEF_CREERGRAPHE_H
#define DEF_CREERGRAPHE_H


#include "Graphe.h"
#include "Tuyau.h"
#include "Sommet.h"
#include "FordFulkerson.h"

void tuyauAdded(Graphe* gggg,int source,int dest, int capa, int flot, int sens);

std::vector<Couleur> listColor(Graphe* gggg);

Graphe* copyGraph(Graphe* g);

Graphe* exampleGraph();

Graphe* createGraph(int n_sommet);

void solverGraph(Graphe* gggg, FordFulkerson* ff);

Graphe* createYourGraph(std::string method, std::vector<int> sommets, std::vector<std::vector<int>> edges);

#endif