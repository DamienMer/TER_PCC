#include "BellmanFord.h"

#include "Graphe.h"
#include "Sommet.h"
#include "Arete.h"

#include <limits>

BellmanFord::BellmanFord(Graphe *graphe, Sommet *init) : m_root(init), m_currentSommet(init), m_grapheOrigine(graphe){
    pcc();
}


std::map<int, double> BellmanFord::pcc(){
    BellmanFord::initialisation();

    //AJOUT DE LA PREMIERE PAGE HISTORIQUE
    std::vector<double> dist = getConvertDist();
    std::string com = "Initialisation";
    addPageBellmanFord(m_currentSommet, m_currentSommet, dist, com);

    //on fait autant de tours de boucle qu'il y a de sommets dans le graphe (-1)
    while(m_iteration < m_grapheOrigine->getSommets().size() - 1){
        //pour chaque sommet du graphe, on met à jour les successeurs de ce sommet
        for(int i = 0; i < m_grapheOrigine->getSommets().size(); i++){
            //on retient le sommet courant
            m_currentSommet = m_grapheOrigine->getSommet(i);
            //on met à jour avec ce sommet
            maj(m_currentSommet);
        }
        m_currentSommet = m_root;
        //on incrémente m_iteration
        m_iteration ++;
    }

    //AJOUT DE PAGE HISTORIQUE
    dist = getConvertDist();
    com = "Fin de l'éxécution sans vérification de cycles absorbants";
    addPageBellmanFord(m_currentSommet, m_currentSommet, dist, com);

    //last
    bool flag = false;
    for(int i = 0; i < m_grapheOrigine->getSommets().size(); i++){
            //on retient le sommet courant
            m_currentSommet = m_grapheOrigine->getSommet(i);
            //on met à jour avec ce sommet
            if(overMaj(m_currentSommet)){
                flag = true;
                break;
            }
    }

    //AJOUT DE LA DERNIERE PAGE HISTORIQUE
    dist = getConvertDist();
    com = "Fin";

    if(flag){
        com = "Fin, cycle absorbant détécté";
    }
    
    addPageBellmanFord(m_currentSommet, m_currentSommet, dist, com);
    return m_d;
}


void BellmanFord::initialisation(){
    //pour chaque sommet du graphe
    for(Sommet *temp : m_grapheOrigine->getSommets()){
        double inf = std::numeric_limits<double>::infinity();
        //on met la distance du sommet par rapport à la racine à l'infinie
        m_d[temp->getNum()] = inf;
    }
    //On initialise la distance de la racine par rapport à elle-meme à 0
    m_d[m_currentSommet->getNum()] = 0;
}


void BellmanFord::maj(Sommet *current){
    //Pour chaque aretes sortantes de current
    for(Arete *temp : current->getAretesSortantes()){

        //Si la distance à la racine du sommet à l'arrivee de cette arete est supérieur à la distance à la racine de current + le poids de l'arete
        if(m_d[temp->getArrivee()->getNum()] > m_d[current->getNum()] + temp->getPoids()){
            //on met à jour la distance à la racine du sommet à l'arrivée de l'arete
            m_d[temp->getArrivee()->getNum()] = m_d[current->getNum()] + temp->getPoids();
            
            //AJOUT DE PAGE HISTORIQUE
            std::vector<double> dist = getConvertDist();
            std::string com = "On met à jour la distance";
            addPageBellmanFord(current, temp->getArrivee(), dist, com);
        }
        else{
            //AJOUT DE PAGE HISTORIQUE
            std::vector<double> dist = getConvertDist();
            std::string com = "Pas d'amélioration";
            addPageBellmanFord(current, temp->getArrivee(), dist, com);
        }
    }
}


bool BellmanFord::overMaj(Sommet *current){
    //Pour chaque aretes sortantes de current
    for(Arete *temp : current->getAretesSortantes()){

        //Si la distance à la racine du sommet à l'arrivee de cette arete est supérieur à la distance à la racine de current + le poids de l'arete
        if(m_d[temp->getArrivee()->getNum()] > m_d[current->getNum()] + temp->getPoids()){
            //on met à jour la distance à la racine du sommet à l'arrivée de l'arete
            m_d[temp->getArrivee()->getNum()] = m_d[current->getNum()] + temp->getPoids();

            //AJOUT DE PAGE HISTORIQUE
            std::vector<double> dist = getConvertDist();
            std::string com = "MISE A JOUR DANS L'OVERMAJ, CYCLE ABSORBANT DETECTE !!!";
            addPageBellmanFord(current, temp->getArrivee(), dist, com);
            return true;
        }
        else{
            //AJOUT DE PAGE HISTORIQUE
            std::vector<double> dist = getConvertDist();
            std::string com = "Pas d'amélioration";
            addPageBellmanFord(current, temp->getArrivee(), dist, com);
        }
    }
    return false; 
}


int BellmanFord::getIteration(){
    return m_iteration;
}

std::map<int, double> BellmanFord::getD(){
    return m_d;
}

void BellmanFord::displayD(){
    std::cout << "BELLMAN FORD :\n";
    for(std::map<int, double>::iterator it = m_d.begin(); it != m_d.end(); it++){
        std::cout << "sommet : " << it->first << " d : " << it->second << "\n";
    }
}

void BellmanFord::addPageBellmanFord(Sommet* current, Sommet* cible, std::vector<double> dist, std::string com){
    PageBellmanFord* ajout = new PageBellmanFord(m_grapheOrigine, current, cible, m_iteration, dist, com);
    m_historique.push_back(ajout);
}

std::vector<double> BellmanFord::getConvertDist(){
    std::vector<double> res;
    for(std::map<int, double>::iterator it = m_d.begin(); it != m_d.end(); it++){
        res.push_back(it->second);
    }
    return res;
}


PageBellmanFord::PageBellmanFord(Graphe *grapheOrigine, Sommet *sommetActuel, Sommet *sommetCible, int iteration, std::vector<double> dist, std::string com):
        _graphOrigine(grapheOrigine), _sommetActuel(sommetActuel), _sommetCible(sommetCible), _iteration(iteration), _dist(dist), _commentaire(com){}