#include "Graphe.h"
#include "Tuyau.h"
#include "Sommet.h"
#include "FordFulkerson.h"
#include <iostream>
using namespace std;



void tuyauAdded(Graphe* gggg,int source,int dest, int capa, int flot, int sens){
    gggg ->getSommet(source)->addTuyau(gggg ->getSommet(dest), capa, flot, sens);
    gggg ->set_nbTuyau(1);
}

std::vector<Couleur> listColor(Graphe* gggg){
    std::vector<Couleur> tab;
    for(Sommet* temp : gggg -> getSommets()){
        tab.push_back(temp -> getCouleur());
    }
    return tab;
}

Graphe* copyGraph(Graphe* g){
    
    Graphe* temp = new Graphe();
    
    //Copie les sommets
    for(Sommet *first : g ->getSommets()){
        temp->copySommet(first);
    }
    
    //Copie les tuyaux et les couleurs de sommets
    for(Sommet *first : g ->getSommets()){
        for(Sommet *second : temp->getSommets()){
            if(first->getNum() == second->getNum()){
                second->setCouleur(first->getCouleur());
                for(Tuyau *neighbours : first -> getTuyauSortantes()){            
                    second->copyTuyau(neighbours,temp);
                }
            }
        }
    }
    
    return temp;
}

Graphe* exampleGraph(){
    Graphe *gggg = new Graphe();

    gggg->addSommet(100,1);
    gggg->addSommet(200);
    gggg->addSommet(300);
    gggg->addSommet(400);
    gggg->addSommet(500);
    gggg->addSommet(600,0,1);


//Sommet 0 à 7
    //std::cout << "Nombre tuyau : " << gggg ->get_nbTuyau() << std::endl;
    tuyauAdded(gggg,0,1,10, 0, 1);
    tuyauAdded(gggg,0,2,10, 0, 1);
    tuyauAdded(gggg,1,4,25, 0, 1);
    tuyauAdded(gggg,2,3,15, 0, 1);
    tuyauAdded(gggg,3,1,6, 0, 1);
    tuyauAdded(gggg,3,5,10, 0, 1);
    tuyauAdded(gggg,4,5,10, 0, 1);
    //std::cout << "Nombre tuyau : " << gggg ->get_nbTuyau() << std::endl;
    return gggg;
    
}

Graphe* createGraph(int n_sommet){
    Graphe *g = new Graphe();
    int source=0;
    int puit=n_sommet-1;
    cout << "What is the number of sommet source ? (Start at 0) \nYou choose the sommet : ";
    cin >> source;
    cout << "What is the number of sommet pit ? (Start at 0) \nYou choose the sommet : ";
    cin >> puit;
    int temp=0;
    while(temp<n_sommet){
        if(source==temp){
            g->addSommet(temp,1);
        } else if(puit==temp){
            g->addSommet(temp,0,1);
        } else{
            g->addSommet(temp);
        }
        temp++;
    }
    
    bool voisin=true;
    while(voisin){
        int i=0;
        int j=0;
        int fl=0;
        int capa=0;    
        cout << "Path begin with i and finish with j. fl is the actual flood and capa is the capacity the pipe can support.\n";
        cout << " i : ";
        cin >> i;
        cout << " j (other than i) : ";
        cin >> j;
        cout << " fl : ";
        cin >> fl;
        cout << " capa (other than 0) : ";
        cin >> capa;
        if(i!=j && capa!=0){
            g ->getSommet(i)->addTuyau(g ->getSommet(j), capa, fl, 1);
        }
        cout << "Continue to create a pipe ? (1 is yes, 0 is no) ";
        cin >> voisin;
        cout << " flot entre i = " << i << " et j = " << j << " : " << fl << " / " << capa << endl;
    }
    return g;
}

void solverGraph(Graphe* gggg, FordFulkerson* ff){
    std::vector<Sommet*> list_som = gggg -> getSommets();            
    int bottle =  0;    
    int ref_sommet =-1;    
    int iter=0;    
    int modif_flot = -1;
    
    while(modif_flot!= ff -> getFlotStep().back()){
        
        list_som = gggg -> getSommets();        
        bottle = 0;        
        ref_sommet = -1;        
        for(Sommet* som : list_som){
            for(Tuyau *neighbours : som -> getTuyauSortantes()){
                if(neighbours -> getCapacite() >= bottle){
                    bottle = neighbours -> getCapacite();
                }
            }
        }        
        modif_flot = ff -> getFlotStep().back();
            
        ff -> displayFlotStep(gggg);
    
        ff -> findFlotMax( gggg, bottle, ref_sommet);
        
        for(Sommet *reset : gggg ->getSommets()){
            reset -> setCouleur(Couleur::White);
        }
        
        std::cout << "Bottle : " << bottle << " Som ref : " << ref_sommet << std::endl;                
        
        iter++;
    }
    
    ff -> displayFlotStep(gggg);
}

int conversionVal(Graphe *g, int a){
    for(int i = 0; i < g->getSommets().size(); i++){
        if(g->getSommet(i)->getVal() == a){
            std::cout << "valeur de i : " << i <<std::endl;
            return i;
        }
    }
    return -1;
}   


Graphe* createYourGraph(std::string method, std::vector<int> sommets, std::vector<std::vector<int>> edges){
    Graphe * ggggg = new Graphe();
    if(method == "Dijkstra" || method == "BellmanFord" || method == "FloydWarshall"){
        //ajout des sommets dans le graph
        for(int s : sommets){
            ggggg->addSommet(s);
        }

        //ajout des aretes dans le graph
        for(std::vector<int> a : edges){
            /*
            int _a = conversionVal(ggggg, a[0]);
            int _b = conversionVal(ggggg, a[1]);
            int _c = a[2];
            std::cout  << "a : " << _a << ", b : " << _b << ", c : " << _c << std::endl;
            */
            ggggg->getSommet(conversionVal(ggggg, a[0]))->addArete(ggggg->getSommet(conversionVal(ggggg, a[1])), a[2]);
        }
    }

    else {
        //ajout des sommets dans le graph
        int i=0;
        for(int s : sommets){         
            if(i==0){
                ggggg->addSommet(s,1);
            }            
            else{ 
                ggggg->addSommet(s);
            }
            i++;
        }
        ggggg->getSommet(ggggg->get_nbSommet()-1)->setPit();
        //ajout des aretes dans le graph
        for(std::vector<int> a : edges){
            ggggg->getSommet(a[0])->addTuyau(ggggg->getSommet(a[1]), a[2], a[3], true);
            ggggg ->set_nbTuyau(1);

        }
    }
    return ggggg;
}