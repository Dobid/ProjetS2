#ifndef ARETE_H
#define ARETE_H
#include "grman/grman.h"
#include "vector"
#include "Sommet.h"


class Arete
{
    public:
        Arete(grman::WidgetBox& sommet1,grman::WidgetBox& sommet2,int lsommet1,int lsommet2);
        virtual ~Arete();
        void update(std::vector<Sommet*> Sommets);
        std::string save(std::vector<int> sommets_non_utilise);
        int utilise();

    protected:

    private:
        int m_sommet1,m_sommet2,m_utilise;
        grman::WidgetButton m_bouton;
        grman::WidgetBox m_top_box;
        grman::WidgetEdge m_lien;
};

#endif // ARETE_H
