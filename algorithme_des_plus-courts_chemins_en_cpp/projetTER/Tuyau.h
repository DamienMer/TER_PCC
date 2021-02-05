#ifndef DEF_TUYAU_H
#define DEF_TUYAU_H

#include "Sommet.h"

class Sommet;

class Tuyau{

    private :
     
        Sommet *m_depart;

        Sommet *m_arrivee;

        int m_capacite;

        int m_flot;

        bool m_sens;

    public :

        Tuyau(Sommet *depart, Sommet *arrivee, int capacite, int flot ,bool sens);

        Sommet* getDebut();

        Sommet* getFin();

        int getCapacite();

        int getFlot();

        bool getSens();

        void setDebut(Sommet* depart);

        void setFin(Sommet* arrivee);

        void setCapacite(int capacite);

        void setFlot(int flot);

        void setSens(bool change);

};

#endif
