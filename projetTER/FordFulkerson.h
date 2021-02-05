#ifndef DEF_FORDFULKERSON_H
#define DEF_FORDFULKERSON_H

#include <vector>
#include <map>
#include <iostream>
#include "Couleur.h"
#include <list>
#include <iterator>

class Graphe;
class Sommet;
class Tuyau;


class FordFulkerson{
    private :
        int m_nbSommets;
        int flot_max;
        Graphe* m_grapheOrigine;
        Sommet* s_source;
        Sommet* s_pit;
        Graphe* m_grapheEcart;
        std::vector<int> flot_step;
        std::vector<int> flotEcart_step;

    public :
        FordFulkerson(Graphe *graphe);

        void initialisation();
    
        Graphe* getGrapheEcart(Graphe *graphe);

        int getFlotMax();

        std::vector<int> getFlotStep();
    
        Couleur addFlotPred(std::vector<Tuyau*> predecesseur, int flot);
    
        Couleur addFlotSucc(std::vector<Tuyau*>  successeur, int flot);    
    
        void findFlotMax(Graphe* m_grapheTransition,int &bottleneck, int &id_som);    
    
        void displayFlotStep(Graphe *graphe);
    
        //Compte le nombre de sous-etape dans un calcul de flot max
        int _python_nbsubstep;
    
        //Enrengistre tout les graphe dès qu'un changement de couleurs est fait!
        std::list<Graphe*> _python_substep;
    
        //Méthode ajoutant les etat de graphe dans _python_substep et augmentant _python_nbsubstep de 1
        void stepSnap(Graphe* snapgraphe);
    
        std::list<Graphe*> getPythonStep();
    
        int getPythonNbStep();
};

#endif
