#include "Tuyau.h"

Tuyau::Tuyau(Sommet *depart, Sommet *arrivee, int capacite, int flot ,bool sens) : m_depart(depart), m_arrivee(arrivee),m_capacite(capacite), m_flot(flot), m_sens(sens){}

Sommet* Tuyau::getDebut(){
    return m_depart;
}

Sommet* Tuyau::getFin(){
    return m_arrivee;
}

int Tuyau::getCapacite(){
    return m_capacite;
}

int Tuyau::getFlot(){
    return m_flot;
}

bool Tuyau::getSens(){
    return m_sens;
}

void Tuyau::setDebut(Sommet *depart){
    m_depart = depart;
}

void Tuyau::setFin(Sommet *arrivee){
    m_arrivee = arrivee;
}

void Tuyau::setCapacite(int capacite){
    m_capacite = capacite;
}

void Tuyau::setFlot(int flot){
    m_flot = flot;
}

void Tuyau::setSens(bool change){
    m_sens = change;
}
