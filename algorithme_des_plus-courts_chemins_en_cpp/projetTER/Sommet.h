#ifndef DEF_SOMMET_H
#define DEF_SOMMET_H

#include "Graphe.h"
#include "Tuyau.h"
#include "Couleur.h"

#include <vector>

//Forward declaration de la class Arete
class Arete;
class Tuyau;

class Sommet{

    private :

        //pointeur de Graphe auquel se rattache le sommet
        Graphe *m_grapheOrigine;

        //numéro d'identification
        int m_num;

        //valeur du sommet
        int m_val;

        //Color link to the Sommet.
        Couleur m_couleur;

        //tableau de pointeur d'aretes entrantes
        std::vector<Arete*> m_aretesEntrantes;

        //tableau de pointeur d'aretes sortantes
        std::vector<Arete*> m_aretesSortantes;

        //tableau de pointeur de Sommets sortants
        std::vector<Sommet*> m_successeurs;

        //tableau de pointeur de Sommets entrants
        std::vector<Sommet*> m_predecesseurs;
    
//Ajout pour tuyau

        std::vector<Tuyau*> m_tuyauEntrantes;

        std::vector<Tuyau*> m_tuyauSortantes;

        bool m_source;

        bool m_pit;


    public :

        //Constructeur, créer un sommet attaché au graphe grapheOrigine, de valeur val
        Sommet(Graphe *grapheOrigine, int val, bool source, bool puit);

        int getNum();

        int getVal();

        Couleur getCouleur();

        std::vector<Arete*> getAretesEntrantes();

        std::vector<Arete*> getAretesSortantes();

        std::vector<Sommet*> getSucesseurs();

        std::vector<Sommet*> getPredecesseurs();


        void setNum(int i);

        void setVal(int i);

        void setCouleur(Couleur couleur);

        //ajoute une arete au sommet de poids poids
        void addArete(Sommet *arrivee, int poids);
    
//Ajout pour tuyau

        std::vector<Tuyau*> getTuyauEntrantes();

        std::vector<Tuyau*> getTuyauSortantes();

        bool isSource();

        bool isPit();
    
        void setTuyau(Tuyau* te, Sommet *arrivee, int capacite, int flot, bool sens);

        void setSource();

        void setPit();

        void addTuyau(Sommet *arrivee, int capacite, int flot, bool sens);
    
        //Copie un tuyau dans notre graphe g
        void copyTuyau(Tuyau* tuy, Graphe* g);
    
};

#endif