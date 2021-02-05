#ifndef DEF_DIJKSTRA_H
#define DEF_DIJKSTRA_H

#include <vector>
#include <map>
#include <iostream>

//Forward declaration
class Graphe;
class Sommet;
class Arete;
class PageDijkstra;

class Dijkstra{
    private :
        //Pointeur vers le graphe sur lequel s'applique l'algorithme
        Graphe *m_grapheOrigine;

        //Pointeur vers le sommet racine de l'algorithme
        Sommet *m_currentSommet;

        //Tableau de pointeurs de sommets contenant les sommets qui n'ont pas encore été traité par l'algorithme
        std::vector<Sommet*> m_left;

        //Map faisant correspondre un Id de sommet à une distance par rapport à la racine
        std::map<int, double> m_d;

        //objet représentant un historique d'éxécution pour la visualisation (jupyter notebook)
        std::vector<PageDijkstra*> m_historique;

    public :
        //Constructeur, Créer un objet Dijkstra applicable au Graphe graphe et de sommet racine init
        Dijkstra(Graphe *graphe, Sommet *init);

        //Map les id des sommets à leur distance par rapport au sommet racine
        std::map<int, double> pcc();

        //Initialise les paramètres de l'algoritme
        void initialisation();

        //met à jour les distances à partir du sommet s
        void maj(Sommet *s);
        
        //recherche le sommet dans m_left qui a la plus petite distance à la racine
        void checkForMin();

        //retourne le tableau de pointeurs de sommet qui n'ont pas encore été traité par Dijkstra
        std::vector<Sommet*> getLeft();

        //retourne le map des distances à la racine de chaque sommet
        std::map<int, double> getD();

        std::vector<PageDijkstra*> getHistorique(){
            return m_historique;
        }

        //affiche m_left
        void displayLeft();

        //affiche m_d
        void displayD();

        //retourne un vector des distances. Utilisé pour la visualisation
        std::vector<double> getConvertDist();

        //ajoute une nouvelle page à l'historique
        void addPageDijkstra(Sommet* current, Sommet* cible, std::vector<double> dist, std::string com);
};

class PageDijkstra{
    private :
        Graphe* _graphOrigine;
        Sommet* _sommetActuel;
        Sommet* _sommetCible;
        std::vector<Sommet*> _left;
        std::vector<double> _dist;
        std::string _commentaire;

    public:
        //constructeur
        PageDijkstra(Graphe *grapheOrigine, Sommet *sommetActuel, Sommet *sommetCible, std::vector<Sommet*> left, std::vector<double> dist, std::string com);

        Sommet* getSommetActuel(){
            return _sommetActuel;
        }

        Sommet* getSommetCible(){
            return _sommetCible;
        }

        std::vector<Sommet*> getLeft(){
            return _left;
        }

        std::vector<double> getDist(){
            return _dist;
        }

        std::string getCommentaire(){
            return _commentaire;
        }
};

#endif