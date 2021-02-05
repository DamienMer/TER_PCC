#include "FloydWarshall.h"

#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"
#include <string>

#include <limits>

FloydWarshall::FloydWarshall(Graphe *graphe) : m_grapheOrigine(graphe), m_nbSommets(graphe->getSommets().size()){
    //création d'un tableau de taille m_nbSommet de tableau d'int
    m_dist = new int* [m_nbSommets];
    //pour chaque case, on créer un tableau de taille m_nbSommet
    for(int i = 0; i < m_nbSommets; i++){
        m_dist[i] = new int[m_nbSommets];
    }

    pcc();
}


int** FloydWarshall::pcc(){
    //initialisation des paramètre de l'algorithme
    initialisation();

    //triple boucle de mise à jour
    for(int k = 0; k < m_nbSommets; k++){
        for(int i = 0; i < m_nbSommets; i++){
            for(int j = 0; j < m_nbSommets; j++){

                if(m_dist[i][j] > m_dist[i][k] + m_dist[k][j]){
                    m_dist[i][j] = m_dist[i][k] + m_dist[k][j];

                    //AJOUT DE PAGE HISTORIQUE
                    std::vector<std::vector<double>> dist = getConvertDist();
                    std::string com = "On met à jour la case (ligne : " + std::to_string(j) + " colonne : " + std::to_string(i) + ")";
                    addPageFloydWarshall(m_grapheOrigine->getSommet(k), m_grapheOrigine->getSommet(i), m_grapheOrigine->getSommet(j), dist, com);
                }
                else{
                    //AJOUT DE PAGE HISTORIQUE
                    std::vector<std::vector<double>> dist = getConvertDist();
                    std::string com = "Pas d'amélioration";
                    addPageFloydWarshall(m_grapheOrigine->getSommet(k), m_grapheOrigine->getSommet(i), m_grapheOrigine->getSommet(j), dist, com);
                }
            }
        }
    }
    return m_dist;
}


void FloydWarshall::initialisation(){
    
    double inf = std::numeric_limits<int>::infinity();

    //on initialise toutes les distances d'un sommet à un autre
    
    for(int i = 0; i < m_nbSommets; i++){
        for(int j = 0; j < m_nbSommets; j++){
            //la distance d'un sommet à lui même est 0
            if(i == j){
                m_dist[i][j] = 0;
            }
            //la distance d'un sommet à un autre est initialisé à l'infini pour le moment
            else{
                m_dist[i][j] = 99;
            }
        }
    }
    //on modifie les valeurs initialisées précédemment en fonction des poids des aretes de notre graphe
    for(int i = 0; i < m_grapheOrigine->getSommets().size(); i++){
        for(Arete *a : m_grapheOrigine->getSommet(i)->getAretesSortantes()){
            m_dist[a->getArrivee()->getNum()][a->getDepart()->getNum()] = a->getPoids();
        }
    }
}

int** FloydWarshall::getDist(){
    return m_dist;
}

void FloydWarshall::displayDist(){
    std::cout << "FLOYDWARSHALL :\n";
    for(int i = 0; i < m_nbSommets; i++){
        for(int j = 0; j < m_nbSommets; j++){
            std::cout << m_dist[j][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "done";
}


std::vector<std::vector<double>> FloydWarshall::getConvertDist(){
    std::vector<std::vector<double>> res;
    for(int i = 0; i < m_nbSommets; i++){
        std::vector<double> temp;
        for(int j = 0; j < m_nbSommets; j++){
            temp.push_back(m_dist[j][i]);
        }
        res.push_back(temp);
    }
    return res;
}

void FloydWarshall::addPageFloydWarshall(Sommet *k, Sommet *i, Sommet *j, std::vector<std::vector<double>> dist, std::string com){
    PageFloydWarshall *temp = new PageFloydWarshall(m_grapheOrigine, k, i, j, dist, com);
    m_historique.push_back(temp);
}

PageFloydWarshall::PageFloydWarshall(Graphe *grapheOrigine, Sommet *k, Sommet *i, Sommet *j, std::vector<std::vector<double>> dist, std::string com) :
    _graphOrigine(grapheOrigine), _k(k), _i(i), _j(j), _dist(dist), _commentaire(com){}