#include "FordFulkerson.h"

#include "Graphe.h"
#include "Sommet.h"
#include "Tuyau.h"
#include "CreerGraphe.h"


#include <limits>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>


FordFulkerson::FordFulkerson(Graphe *graphe) : m_grapheOrigine(graphe), m_grapheEcart(graphe), m_nbSommets(graphe->getSommets().size()){
    
    flot_max=0;
    flot_step.push_back(flot_max);
    flotEcart_step.push_back(0);
        
    for(Sommet *temp : m_grapheOrigine->getSommets()){
        if(temp -> isSource()){s_source=temp;}
        if(temp -> isPit()){s_pit=temp;}
    }

    _python_nbsubstep=0;
    _python_substep;

}



void FordFulkerson::initialisation(){
    
    Graphe *g = new Graphe();
    
    g = m_grapheEcart;
    int bottleneck = flotEcart_step.back();
    
    for(Sommet *first : g ->getSommets()){
        for(Tuyau *neighbours : first -> getTuyauSortantes()){
            neighbours -> getFin() -> setTuyau(neighbours,first,neighbours -> getCapacite(),neighbours -> getCapacite()-neighbours -> getFlot(), true);
            if( neighbours -> getCapacite() - neighbours -> getFlot() >0 && (neighbours -> getCapacite() - neighbours -> getFlot())<bottleneck){
                bottleneck=neighbours -> getCapacite() - neighbours -> getFlot();
            }
        }
    }
    flotEcart_step.push_back(bottleneck);
}

Graphe* FordFulkerson::getGrapheEcart(Graphe *graphe){
    return m_grapheEcart;
}

int FordFulkerson::getFlotMax(){
    return flot_max;
}

std::vector<int> FordFulkerson::getFlotStep(){
    return flot_step;
}


Couleur FordFulkerson::addFlotPred(std::vector<Tuyau*> predecesseur, int flot){
    for(Tuyau *parent : predecesseur){
        if(parent -> getDebut() -> isSource()){
            if(parent -> getCapacite()-parent -> getFlot()>0 && parent -> getCapacite()- parent -> getFlot()>=flot){
                parent -> setFlot(parent -> getFlot()+flot);
                return Couleur::Grey;
            }
            else{
                return Couleur::Red;
            }
        }
        else if(parent -> getCapacite() - parent -> getFlot()>0 && parent -> getCapacite() - parent -> getFlot()>=flot){
            std::vector<Tuyau*> pred = parent -> getDebut() -> getTuyauEntrantes();
            Couleur cool = addFlotPred(pred,flot);
            if(cool == Couleur::Grey){
                parent -> setFlot(parent -> getFlot()+flot);
                flot=10000000;
                return cool;
            }
        }
        else{return Couleur::Red;}
    }
    return Couleur::White;
}


Couleur FordFulkerson::addFlotSucc(std::vector<Tuyau*>  successeur, int flot){
    for(Tuyau *child : successeur){
        if(child -> getFin() -> isPit()){
            if(child -> getCapacite()-child -> getFlot()>0 && child -> getCapacite()-child -> getFlot()>=flot){
                child -> setFlot(child -> getFlot()+flot);
                return Couleur::Grey;                
            }
            else{
                return Couleur::Red;
            }
        }
        else if(child -> getCapacite()-child -> getFlot()>0 && child -> getCapacite()-child -> getFlot()>=flot){
            std::vector<Tuyau*> succ = child -> getFin() -> getTuyauSortantes();
            Couleur cool = addFlotSucc(succ,flot);
            if(cool == Couleur::Grey){                
                child -> setFlot(child -> getFlot()+flot);
                flot=10000000;
                return cool;
            }
        }
        else{return Couleur::Red;}
    }
    return Couleur::White;
}



void FordFulkerson::stepSnap(Graphe* snapgraphe){
    
    Graphe* snap = copyGraph(snapgraphe);
    
    _python_substep.push_back(snap);
    //std::cout << "Etape  : " << _python_nbsubstep << " avec le premier sommet de couleur :" << _python_substep.back() -> getSommet(0) -> getCouleur() << std::endl;
    //displayFlotStep(snap);
    _python_nbsubstep++;    
}

std::list<Graphe*> FordFulkerson::getPythonStep(){
    return _python_substep;
}

int FordFulkerson::getPythonNbStep(){
    int temp=_python_nbsubstep;
    _python_nbsubstep=0;
    return temp;
}

void FordFulkerson::findFlotMax(Graphe* m_grapheTransition,int &bottleneck, int &id_som){
    
    bool flag = false;
    
    for(Sommet *first : m_grapheTransition ->getSommets()){
        if(first -> getCouleur() == Couleur::White){
            first -> setCouleur(Couleur::Grey);
            stepSnap(m_grapheTransition);
            for(Tuyau *neighbours : first -> getTuyauSortantes()){
                if(neighbours -> getFin() -> getCouleur() == Couleur::White || neighbours -> getFin() -> getCouleur() == Couleur::Grey ){
                    if(neighbours -> getCapacite()-neighbours -> getFlot()>0 && neighbours -> getCapacite()-neighbours -> getFlot()<=bottleneck ){
                        bottleneck=neighbours -> getCapacite()-neighbours -> getFlot();
                        id_som=first -> getNum();
                        findFlotMax(m_grapheTransition,bottleneck, id_som);
                        //std::cout << "HERE ! et id : " << id_som << std::endl;
                        if(first -> getNum() == id_som){flag = true; }//std::cout << "id_som : " << id_som << std::endl;
                    }
                }
            }
            first -> setCouleur(Couleur::Green);
            stepSnap(m_grapheTransition);
        }        
    }
    
    if(flag){
        for(Sommet *som : m_grapheTransition ->getSommets()){
            if( som -> getNum() == id_som){
                std::vector<Tuyau*> pred = som -> getTuyauEntrantes();
                std::vector<Tuyau*> succ = som -> getTuyauSortantes();
                Couleur utile2 = Couleur::Red;
                Couleur utile = Couleur::Red;                
                if(som -> getCouleur() != Couleur::Pink &&
                   som -> getTuyauEntrantes().back() -> getDebut() -> isSource() &&
                   som -> getTuyauEntrantes().back() -> getCapacite() - som -> getTuyauEntrantes().back() -> getFlot()>0 && 
                   som -> getTuyauEntrantes().back() -> getCapacite() - som -> getTuyauEntrantes().back() -> getFlot()>= bottleneck ){
                    som -> setCouleur(Couleur::Pink);
                    stepSnap(m_grapheTransition);
                    utile = Couleur::Grey;
                    som -> getTuyauEntrantes().back() -> setFlot(som -> getTuyauEntrantes().back() -> getFlot()+bottleneck);
                }
                else{
                    utile = addFlotPred(pred,bottleneck);
                    stepSnap(m_grapheTransition);
                }
                if(utile != Couleur::Red){ 
                    if(som -> getCouleur() != Couleur::Pink &&
                       som -> getTuyauSortantes().back() -> getFin() -> isPit()  && 
                       som -> getTuyauSortantes().back() -> getCapacite() - som -> getTuyauSortantes().back() -> getFlot()>0 &&
                       som -> getTuyauSortantes().back() -> getCapacite() - som -> getTuyauSortantes().back() -> getFlot() >= bottleneck ){
                        som -> setCouleur(Couleur::Pink);
                        stepSnap(m_grapheTransition);
                        utile2 = Couleur::Grey;
                        som -> getTuyauSortantes().back() -> setFlot(som -> getTuyauSortantes().back() -> getFlot()+bottleneck);
                    }
                    else{                        
                        utile2 = addFlotSucc(succ,bottleneck);
                        stepSnap(m_grapheTransition);
                    }
                    if( utile2 != Couleur::Red){
                        flot_step.push_back(bottleneck+flot_step.back());
                    }
                }
            }
        }
        //m_grapheEcart = getGrapheEcart(m_grapheTransition);
    }    
}

void FordFulkerson::displayFlotStep(Graphe* m_grapheTransition){
    std::cout << " Ford Fulkerson :\n";
    for(Sommet *first : m_grapheTransition ->getSommets()){
        //std::cout << "Sommet : " << first -> getNum() << " de couleur : " << first -> getCouleur() << std::endl;  
        
        for(Tuyau *neighbours : first -> getTuyauSortantes()){
            std::cout << " flot entre i = " << first -> getNum() << " et j = " << neighbours -> getFin() -> getNum() << " : " << neighbours -> getFlot() << " / " << neighbours -> getCapacite() << std::endl;
        }
        std::cout << std::endl;
    }
    int fm=flot_step.back();
    std::cout << "Ajout Flot Max : " << fm << std::endl;
}