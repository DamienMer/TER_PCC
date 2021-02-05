#include "Graphe.h"

#include "Sommet.h"
#include <iostream>
using namespace std;

Graphe::Graphe() : m_iteration(0) {m_nbSommet=0;m_nbTuyau=0;}

/*int Graphe::getIteration(){
    return m_iteration;
}*/

/*void Graphe::incrIteration(){
    m_iteration ++;
}*/

int Graphe::get_nbSommet(){
    return m_nbSommet;
}

void Graphe::addSommet(int val, bool source, bool puit){
    m_sommets.push_back(new Sommet(this, val,source,puit));    
    return;
}

void Graphe::copySommet(Sommet* som){
    m_sommets.push_back(new Sommet(this, som->getVal(),som->isSource(),som->isPit()));
    return;
}

Sommet* Graphe::getSommet(int num){
    for(Sommet* temp : m_sommets){
        if(temp->getNum() == num){
            return temp;
        }
    }
    //We create a fake graphe for return an error-Sommet with val -1 and stock in the fake graph.
    //This is to dodge the warning when we compile.
    //Graphe *fake = new Graphe();
    return NULL;
}

// Sommet* Graphe::getSommetByValue(int val){
//     for(Sommet* temp : m_sommets){
//         if(temp->getVal() == val){
//             return temp;
//         }
//     }
// }

std::vector<Sommet*> Graphe::getSommets(){
    return m_sommets;
}

void Graphe::displaySommets(){
    for(int i = 0; i < m_sommets.size(); i++){
        std::cout << m_sommets[i]->getNum() << "\n";
    }
     std::cout << "\n";
}

void Graphe::incrNbSommet(){
    m_nbSommet++;
}

int Graphe::get_nbArete(){
    return m_nbArete;
}    

void Graphe::set_nbArete(int j){
    m_nbArete+=j;
}    

int Graphe::get_nbTuyau(){
    return m_nbTuyau;
}

void Graphe::set_nbTuyau(int i){
    m_nbTuyau+=i;
}