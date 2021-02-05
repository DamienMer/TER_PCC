#include "Dijkstra.h"

#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"

#include <limits>

Dijkstra::Dijkstra(Graphe *graphe, Sommet *init) : m_currentSommet(init), m_grapheOrigine(graphe){
    pcc();
}


std::map<int, double> Dijkstra::pcc(){
    //on initialise Dijkstra
    Dijkstra::initialisation();

    //AJOUT DE LA PREMIERE PAGE HISTORIQUE
    std::vector<double> dist = getConvertDist();
    std::string com = "Initialisation";
    addPageDijkstra(m_currentSommet, m_currentSommet, dist, com);

    //Pour chaque sommet du graphe
    for(int i = 0; i < m_grapheOrigine->getSommets().size(); i++){
        //on met à jour les distances à partir de m_currentSommet
        maj(m_currentSommet);
    }

    //AJOUT DE LA DERNIERE PAGE HISTORIQUE
    dist = getConvertDist();
    com = "FIN";
    addPageDijkstra(m_currentSommet, m_currentSommet, dist, com);

    return m_d;
}


void Dijkstra::initialisation(){
    for(Sommet *temp : m_grapheOrigine->getSommets()){
        double inf = std::numeric_limits<double>::infinity();
        //on met la distance du sommet par rapport à la racine à l'infinie
        m_d[temp->getNum()] = inf;
        //on ajoute ce sommet dans les sommets qui n'ont pas encore été traité par Dijkstra
        m_left.push_back(temp);
    }
    //On initialise la distance de la racine par rapport à elle-meme à 0
    m_d[m_currentSommet->getNum()] = 0;
}


void Dijkstra::maj(Sommet *current){
    //Pour chaque aretes sortantes de current
    for(Arete *temp : current->getAretesSortantes()){

        
        //Si la distance à la racine du sommet à l'arrivee de cette arete est supérieur à la distance à la racine de current + le poids de l'arete
        if(m_d[temp->getArrivee()->getNum()] > m_d[current->getNum()] + temp->getPoids()){
            //on met à jour la distance à la racine du sommet à l'arrivée de l'arete
            m_d[temp->getArrivee()->getNum()] = m_d[current->getNum()] + temp->getPoids();

            //AJOUT DE PAGE HISTORIQUE
            std::vector<double> dist = getConvertDist();
            std::string com = "On met à jour la distance";
            addPageDijkstra(current, temp->getArrivee(), dist, com);
        }
        else{
            //AJOUT DE PAGE HISTORIQUE
            std::vector<double> dist = getConvertDist();
            std::string com = "Pas d'amélioration";
            addPageDijkstra(current, temp->getArrivee(), dist, com);
        }   
    }
    //on recherche le sommet current dans m_left pour le retirer
    for(int i = 0; i < m_left.size(); i++){
        if(m_left[i]->getNum() == current->getNum()){
            //on supprime le sommet current de m_left
            m_left.erase(m_left.begin() + i);
        }
    }
    //on cherche le nouveau Sommet current (celui qui parmi m_left, a la plus petite distance à la racine)
    checkForMin();
}


void Dijkstra::checkForMin(){
    double min = std::numeric_limits<double>::infinity();
    //pour chaque sommet qui n'ont pas encore été traité par Dijkstra
    for(Sommet *s : m_left){
        //on cherche le plus petit
        if(m_d[s->getNum()] < min){
            m_currentSommet = s;
        }
    }
}


std::vector<Sommet*> Dijkstra::getLeft(){
    return m_left;
}

std::map<int, double> Dijkstra::getD(){
    return m_d;
}

void Dijkstra::displayLeft(){
    for(Sommet* s : m_left){
        std::cout << s->getNum();
    }
}

void Dijkstra::displayD(){
    std::cout << "DIJKSTRA :\n";
    for(std::map<int, double>::iterator it = m_d.begin(); it != m_d.end(); it++){
        std::cout << "sommet : " << it->first << " d : " << it->second << "\n";
    }
}

std::vector<double> Dijkstra::getConvertDist(){
    std::vector<double> res;
    for(std::map<int, double>::iterator it = m_d.begin(); it != m_d.end(); it++){
        res.push_back(it->second);
    }
    return res;
}


void Dijkstra::addPageDijkstra(Sommet* current, Sommet* cible, std::vector<double> dist, std::string com){
    // std::vector<int> a;
    // a.push_back(11);
    // std::cout <<"alive";
    PageDijkstra* ajout = new PageDijkstra(m_grapheOrigine, current, cible, m_left, dist, com);
    m_historique.push_back(ajout);
}



PageDijkstra::PageDijkstra(Graphe *grapheOrigine, Sommet *sommetActuel, Sommet *sommetCible, std::vector<Sommet*> left, std::vector<double> dist, std::string com) :
    _graphOrigine(grapheOrigine), _sommetActuel(sommetActuel), _sommetCible(sommetCible), _left(left), _dist(dist), _commentaire(com){}