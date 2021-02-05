#ifndef DEF_DMAIN_H
#define DEF_DMAIN_H


#include "Graphe.h"
#include "Tuyau.h"
#include "Sommet.h"
#include "FordFulkerson.h"
#include "Dijkstra.h"

int funA();
//int main();
Graphe* createGraphe();

int myfunction(int a){
    return a;
}

Graphe* createGraphFromUser(std::vector<int> sommets, std::vector<std::vector<int>> edges);


#endif