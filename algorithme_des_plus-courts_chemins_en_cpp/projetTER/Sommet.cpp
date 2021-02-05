#include "Sommet.h"
#include "Tuyau.h"
#include "Arete.h"

Sommet::Sommet(Graphe *grapheOrigine, int val, bool source=0, bool puit=0) : m_grapheOrigine(grapheOrigine), m_val(val), m_source(source), m_pit(puit){
    m_num = grapheOrigine->get_nbSommet();
    grapheOrigine->incrNbSommet();
    m_couleur = Couleur::White;
}

int Sommet::getNum(){
    return m_num;
}

int Sommet::getVal(){
    return m_val;
}

Couleur Sommet::getCouleur(){
    return m_couleur;
}

std::vector<Arete*> Sommet::getAretesEntrantes(){
    return m_aretesEntrantes;
}

std::vector<Arete*> Sommet::getAretesSortantes(){
    return m_aretesSortantes;
}

std::vector<Sommet*> Sommet::getSucesseurs(){
    return m_successeurs;
}

std::vector<Sommet*> Sommet::getPredecesseurs(){
    return m_predecesseurs;
}

void Sommet::setNum(int i){
    m_num = i;
}

void Sommet::setVal(int i){
    m_val = i;
}

void Sommet::setCouleur(Couleur couleur){
    m_couleur = couleur;
}

void Sommet::addArete(Sommet *arrivee, int poids)
{
    Arete* temp = new Arete(this, arrivee, poids);

    m_aretesSortantes.push_back(temp);
    m_successeurs.push_back(arrivee);

    arrivee->m_predecesseurs.push_back(this);
    arrivee->getAretesEntrantes().push_back(temp);
}

//Ajout pour tuyau

std::vector<Tuyau*> Sommet::getTuyauEntrantes(){
    return m_tuyauEntrantes;
}

std::vector<Tuyau*> Sommet::getTuyauSortantes(){
    return m_tuyauSortantes;
}

bool Sommet::isSource(){
    return m_source;
}

bool Sommet::isPit(){
    return m_pit;
}

void Sommet::setTuyau(Tuyau* te, Sommet *arrivee, int capacite, int flot, bool sens){
    te -> setFin(arrivee);
    te -> setCapacite(capacite);
    te -> setFlot(flot);
    te -> setSens(sens);
}

void Sommet::setSource(){
    m_source = 1;
}

void Sommet::setPit(){
    m_pit = 1;
}

void Sommet::addTuyau(Sommet *arrivee, int capacite, int flot, bool sens){

    Tuyau* temp = new Tuyau(this, arrivee, capacite, flot, sens);

    m_tuyauSortantes.push_back(temp);
    m_successeurs.push_back(arrivee);

    arrivee -> m_tuyauEntrantes.push_back(temp);
    //arrivee -> getTuyauEntrantes().push_back(temp);
        
}

void Sommet::copyTuyau(Tuyau* tuy,Graphe* g){
    
    Sommet* arrivee;
    for(Sommet* som : g->getSommets()){
        if(som->getNum()==tuy->getFin()->getNum()){
            arrivee=som;
        }
    }
    
    Tuyau* temp = new Tuyau(this, arrivee, tuy->getCapacite(), tuy->getFlot(), tuy->getSens());

    m_tuyauSortantes.push_back(temp);
    m_successeurs.push_back(arrivee);

    arrivee -> m_tuyauEntrantes.push_back(temp);
}