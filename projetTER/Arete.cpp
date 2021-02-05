#include "Arete.h"

Arete::Arete(Sommet *depart, Sommet *arrivee, int poids) : m_depart(depart), m_arrivee(arrivee), m_poids(poids){}

Sommet* Arete::getDepart(){
    return m_depart;
}

Sommet* Arete::getArrivee(){
    return m_arrivee;
}

int Arete::getPoids(){
    return m_poids;
}

void Arete::setDepart(Sommet *depart){
    m_depart = depart;
}

void Arete::setArrivee(Sommet *arrivee){
    m_arrivee = arrivee;
}

void Arete::setPoids(int poids){
    m_poids = poids;
}