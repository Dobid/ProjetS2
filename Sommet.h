#ifndef SOMMET_H
#define SOMMET_H
#include "grman/grman.h"
#include <iostream>

class Sommet
{
    public:
        Sommet(std::string nom_animal,std::string nom_image,int couleur,int x,int y,int pop);
        virtual ~Sommet();
        void update();
        grman::WidgetBox& get_box();
        int utilise();
        int selectionne();
        std::string save();


    protected:

    private:
        std::string m_nom_animal,m_nom_image;int m_couleur,m_x,m_y,m_popp,m_utilise;
        int m_selectionne;
        grman::WidgetButton m_bouton;
        grman::WidgetButton m_selec;
        grman::WidgetBox m_box;
        grman::WidgetImage m_img;
        grman::WidgetText m_legende;
        grman::WidgetText m_pop;
        grman::WidgetVSlider m_regle;
};

#endif // SOMMET_H
