#ifndef DEF_GRAPHE_H
#define DEF_GRAPHE_H

#include "vector"

//Forward declaration de la class Sommet
class Sommet;

class Graphe{
    
    private :
        
        int m_iteration;

        //compteur du nombre de sommet. Egalement utilisé pour donner un identifiant unique à la création d'un sommet
        int m_nbSommet;    

        //tableau de pointeurs de Sommet associé au graphe courant
        std::vector<Sommet*> m_sommets;
    
        //Compteur du nombre d'arete dans le graphe
        int m_nbArete;
    
        //Compteur du nombre de tuyau dans le graphe
        int m_nbTuyau;

    public : 

        //constructeur du Graphe
        Graphe();        

        //retourne le nombre de sommets actuels du graphe
        int get_nbSommet();

        //ajoute un sommet de valeur val au Graphe
        void addSommet(int val, bool source=0, bool puit=0);
    
        //copy le sommet en entrée et l'ajoute au graph courant
        void copySommet(Sommet* som);

        //retourne un pointeur vers un Sommet
        Sommet* getSommet(int num);

        //Sommet* getSommetByValue(int val);

        //retourne le tableau de pointeurs de Sommet du graphe courant
        std::vector<Sommet*> getSommets();

        //affiche les sommets
        void displaySommets();

        //Augmente de 1 le nombre de Sommet
        void incrNbSommet();
    
        //retourne le nombre d'arete actuelles dans le graphe
        int get_nbArete();
    
        //augmente le nombre d'arete de j
        void set_nbArete(int j);
    
        //retourne le nombre de tuyau actuels dans le graphe
        int get_nbTuyau();
    
        //augmente le nombre de tuyau de i
        void set_nbTuyau(int i);    
};

#endif