#ifndef DEF_BELLMANFORD_H
#define DEF_BELLMANFORD_H

#include <vector>
#include <map>
#include <iostream>

//Forward declaration
class Graphe;
class Sommet;
class Arete;
class PageBellmanFord;

class BellmanFord{
    private :
        //pointeur du sommet racine
        Sommet *m_root;

        //compteur du nombre d'itération
        int m_iteration = 0;

        //pointeur vers le graphe où s'applique l'algorithme
        Graphe *m_grapheOrigine;

        //le sommet actuellement ciblé
        Sommet *m_currentSommet;

        //map des distances de chaque sommet à la racine
        std::map<int, double> m_d;

        //objet représentant un historique d'éxécution pour la visualisation (jupyter notebook)
        std::vector<PageBellmanFord*> m_historique;


    public :
        //constructeur, créer un algorithme qui va s'appliquer sur le graphe graphe à partir du sommet initial init
        BellmanFord(Graphe *graphe, Sommet *init);

        //retourne le map des plus courts chemins
        std::map<int, double> pcc();

        //Initialise les paramètres de l'algoritme
        void initialisation();

        //met à jour les distance par rapport à la racine des successeurs de s sur le graphe
        void maj(Sommet *s);

        bool overMaj(Sommet *s);

        //retourne le nombre d'itération fait dans BellmanFord
        int getIteration();

        //retourne m_d
        std::map<int, double> getD();

        std::vector<PageBellmanFord*> getHistorique(){
            return m_historique;
        }

        //affiche m_d
        void displayD();

        //retourne un vector des distances. Utilisé pour la visualisation
        std::vector<double> getConvertDist();

        //ajoute une nouvelle page à l'historique
        void addPageBellmanFord(Sommet* current, Sommet* cible, std::vector<double> dist, std::string com);
        
};

class PageBellmanFord{
    private :
        Graphe* _graphOrigine;
        Sommet* _sommetActuel;
        Sommet* _sommetCible;
        int _iteration;
        std::vector<double> _dist;
        std::string _commentaire;

    public:
        //constructeur
        PageBellmanFord(Graphe *grapheOrigine, Sommet *sommetActuel, Sommet *sommetCible, int iteration, std::vector<double> dist, std::string com);

        Sommet* getSommetActuel(){
            return _sommetActuel;
        }

        Sommet* getSommetCible(){
            return _sommetCible;
        }

        int getIteration(){
            return _iteration;
        }

        std::vector<double> getDist(){
            return _dist;
        }

        std::string getCommentaire(){
            return _commentaire;
        }
};

#endif
