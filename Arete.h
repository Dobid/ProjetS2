#ifndef ARETE_H
#define ARETE_H
#include "grman/grman.h"
#include "vector"
#include "Sommet.h"


class Arete
{
    public:
        Arete(grman::WidgetBox& sommet1,grman::WidgetBox& sommet2,int lsommet1,int lsommet2,float facteur);
        virtual ~Arete();
        void update(std::vector<Sommet*> Sommets);
        std::string save(std::vector<int> sommets_non_utilise);
        int utilise();
        int sommet1(){return m_sommet1;}
        int sommet2(){return m_sommet2;}
        float facteur(){return m_facteur;}

    protected:

    private:
        int m_sommet1,m_sommet2,m_utilise;
        float m_facteur;
        grman::WidgetBox m_box;
        grman::WidgetVSlider m_regle;
        grman::WidgetButton m_bouton;
        grman::WidgetBox m_top_box;
        grman::WidgetEdge m_lien;
        grman::WidgetText m_legende;
};

#endif // ARETE_H
