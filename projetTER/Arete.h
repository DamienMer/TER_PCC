#ifndef DEF_ARETE_H
#define DEF_ARETE_H

#include "Sommet.h"

//Forward declaration de la class Sommet
class Sommet;

class Arete{

    private :

        //Sommet de départ de l'arete (sa provenance, donne ainsi sa direction)
        Sommet *m_depart;

        //Sommet de départ de l'arete
        Sommet *m_arrivee;

        //poids de l'arete
        int m_poids;


    public :

        //Constructeur, créer une nouvelle arete partant de depart et allant vers arrivee ayant pour poids poids
        Arete(Sommet *depart, Sommet *arrivee, int poids);

        Sommet* getDepart();

        Sommet* getArrivee();

        int getPoids();
        
        //modifie le sommet de depart de l'arete courante
        void setDepart(Sommet* depart);

        //modifie le sommet d'arrivee de l'arete courante
        void setArrivee(Sommet* arrivee);

        void setPoids(int poids);
};

#endif