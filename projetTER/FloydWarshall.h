#ifndef DEF_FLOYDWARSHALL_H
#define DEF_FLOYDWARSHALL_H

#include <vector>
#include <map>
#include <iostream>

//Forward declaration
class Graphe;
class Sommet;
class Arete;
class PageFloydWarshall;

class FloydWarshall{
    private :
        //nombre de sommet du graphe
        int m_nbSommets;

        //pointeur vers le graphe sur lequel s'applique Floyd-Warshall
        Graphe* m_grapheOrigine;
        
        //pointeur de tableaux d'int pour les distances
        int** m_dist;

        std::vector<PageFloydWarshall*> m_historique;

    public :
        //constructeur, créer FloydWarshall sur le graphe graphe
        FloydWarshall(Graphe *graphe);

        //effectue l'algorithme
        int** pcc();

        //Initialise les paramètres de l'algoritme
        void initialisation();

        //retourne le tableau des distances
        int** getDist();

        std::vector<PageFloydWarshall*> getHistorique(){
            return m_historique;
        }

        //affiche le tableau des distances
        void displayDist();

        std::vector<std::vector<double>> getConvertDist();

        void addPageFloydWarshall(Sommet *k, Sommet *i, Sommet *j, std::vector<std::vector<double>> dist, std::string com);

};


class PageFloydWarshall{
    private :
        Graphe* _graphOrigine;
        Sommet* _k;
        Sommet* _i;
        Sommet* _j;
        std::vector<std::vector<double>> _dist;
        std::string _commentaire;

    public:
        //constructeur
        PageFloydWarshall(Graphe *grapheOrigine, Sommet *k, Sommet *i, Sommet *j, std::vector<std::vector<double>> dist, std::string com);

        Sommet* getK(){
            return _k;
        }

        Sommet* getI(){
            return _i;
        }

        Sommet* getJ(){
            return _j;
        }

        std::vector<std::vector<double>> getDist(){
            return _dist;
        }

        std::string getCommentaire(){
            return _commentaire;
        }
};

#endif