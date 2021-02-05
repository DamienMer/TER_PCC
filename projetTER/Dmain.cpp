#include <iostream>

#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include "Dijkstra.h"
#include "FloydWarshall.h"
#include "BellmanFord.h"
#include "FordFulkerson.h"

using namespace std;

/**
 * Compilation avec g++
 *  g++ *.h
 *  g++ *.cpp
 *  ./a.out
 * */



Graphe* createGraphe(){
    Graphe* g = new Graphe();

    
//     g->addSommet(10);
//     g->addSommet(20);
//     g->addSommet(30);
//     g->addSommet(40);

// //sommet 0    
//     g->getSommet(0)->addArete(g->getSommet(1), 50);


// //sommet 1
//     g->getSommet(1)->addArete(g->getSommet(2), 85);

//     return g;

    g->addSommet(10);
    g->addSommet(20);
    g->addSommet(30);
    g->addSommet(40);
    g->addSommet(50);

//sommet 0    
    g->getSommet(0)->addArete(g->getSommet(2), 18);
    g->getSommet(0)->addArete(g->getSommet(4), 3);

//sommet 1
    g->getSommet(1)->addArete(g->getSommet(0), 8);
    g->getSommet(1)->addArete(g->getSommet(2), 4);

//sommet 2

//sommet 3
    g->getSommet(3)->addArete(g->getSommet(1), 1);

//sommet 4
    g->getSommet(4)->addArete(g->getSommet(1), 10);
    g->getSommet(4)->addArete(g->getSommet(3), 2);
    return g;
} 

Graphe* createGraphFromUser(std::vector<int> sommets, std::vector<std::vector<int>> edges){
    Graphe * ggggg = new Graphe();

    //ajout des sommets dans le graph
    for(int s : sommets){
        ggggg->addSommet(s);
    }

    //ajout des aretes dans le graph
    for(std::vector<int> a : edges){
        ggggg->getSommet(a[0])->addArete(ggggg->getSommet(a[1]), a[2]);
    }

    return ggggg;
}

/*
int main(){


                                            //DIJKSTRA
//     Graphe *g = new Graphe();

//     g->addSommet(10);
//     g->addSommet(20);
//     g->addSommet(30);
//     g->addSommet(40);
//     g->addSommet(50);

// //sommet 0/a    
//     g->getSommet(0)->addArete(g->getSommet(2), 18);
//     g->getSommet(0)->addArete(g->getSommet(4), 3);

// //sommet 1
//     g->getSommet(1)->addArete(g->getSommet(0), 8);
//     g->getSommet(1)->addArete(g->getSommet(2), 4);

// //sommet 2

// //sommet 3
//     g->getSommet(3)->addArete(g->getSommet(1), 1);

// //sommet 4
//     g->getSommet(4)->addArete(g->getSommet(1), 10);
//     g->getSommet(4)->addArete(g->getSommet(3), 2);

//     Dijkstra *d = new Dijkstra(g, g->getSommet(0));
    
//     d->displayD();

//     for(int i = 0; i < d->getHistorique().size(); i++){
//         int actuel = d->getHistorique()[i]->getSommetActuel()->getNum();
//         int cible = d->getHistorique()[i]->getSommetCible()->getNum();
//         std::string commentaire = d->getHistorique()[i]->getCommentaire();
//         std::cout << "actuel : " << actuel << " cible : " << cible << " COM : " << commentaire << " dist : ";
//         for(int j = 0; j < d->getHistorique()[i]->getDist().size(); j++){
//             double di = d->getHistorique()[i]->getDist()[j];
//             std::cout << di << " ";    
//         }
//         std::cout << std::endl;
//     }






                                            //BELLMAN FORD
//     Graphe *g = new Graphe();

//     g->addSommet(10);
//     g->addSommet(20);
//     g->addSommet(30);
//     g->addSommet(40);
//     g->addSommet(50);
//     g->addSommet(60);

// //sommet 0
//     g->getSommet(0)->addArete(g->getSommet(1), 10);
//     g->getSommet(0)->addArete(g->getSommet(5), 8);

// //sommet 1
//     g->getSommet(1)->addArete(g->getSommet(3), 2);

// //sommet 2
//     g->getSommet(2)->addArete(g->getSommet(1), 1);

// //sommet 3
//     g->getSommet(3)->addArete(g->getSommet(2), -2);

// //sommet 4
//     g->getSommet(4)->addArete(g->getSommet(1), -4);
//     g->getSommet(4)->addArete(g->getSommet(3), -1);

// //sommet 5
//     g->getSommet(5)->addArete(g->getSommet(4), 1);

//     BellmanFord *b = new BellmanFord(g, g->getSommet(0));

//     b->displayD();

//     for(int i = 0; i < b->getHistorique().size(); i++){
//         int actuel = b->getHistorique()[i]->getSommetActuel()->getNum();
//         int cible = b->getHistorique()[i]->getSommetCible()->getNum();
//         int iteration = b->getHistorique()[i]->getIteration();
//         std::string commentaire = b->getHistorique()[i]->getCommentaire();
//         std::cout << "actuel : " << actuel << " cible : " << cible << " iteration : " << iteration <<  " COM : " << commentaire << " dist : ";
//         for(int j = 0; j < b->getHistorique()[i]->getDist().size(); j++){
//             double di = b->getHistorique()[i]->getDist()[j];
//             std::cout << di << " ";    
//         }
//         std::cout << std::endl;
//     }




                                            //FLOYD WARSHALL

//     Graphe *gg = new Graphe();

//     gg->addSommet(10);
//     gg->addSommet(20);
//     gg->addSommet(30);
//     gg->addSommet(40);

// //sommet 0    
//     gg->getSommet(0)->addArete(gg->getSommet(2), -2);

// //sommet 1
//     gg->getSommet(1)->addArete(gg->getSommet(0), 4);
//     gg->getSommet(1)->addArete(gg->getSommet(2), 3);

// //sommet 2
//     gg->getSommet(2)->addArete(gg->getSommet(3), 2);

// //sommet 3
//     gg->getSommet(3)->addArete(gg->getSommet(1), -1);

//     FloydWarshall *f = new FloydWarshall(gg);

//     f->displayDist();

//     for(int i = 0; i < f->getHistorique().size(); i++){
//         int _k = f->getHistorique()[i]->getK()->getNum();
//         int _i = f->getHistorique()[i]->getI()->getNum();
//         int _j = f->getHistorique()[i]->getJ()->getNum();
//         std::string commentaire = f->getHistorique()[i]->getCommentaire();
//         std::cout << " k : " << _k << " i : " << _i << " j : " << _j << " COM : " << commentaire << " dist : ";
//         std::cout << std::endl;
//         for(int j = 0; j < f->getHistorique()[i]->getDist().size(); j++){
//             for(int k = 0; k < f->getHistorique()[i]->getDist()[j].size(); k++){
//                 double di = f->getHistorique()[i]->getDist()[j][k];
//                 std::cout << di << " ";
//             }
//             std::cout << std::endl;
//         }
//         std::cout << std::endl;
//     }

    
    return 0;
}
*/