#ifndef SOMMET_H
#define SOMMET_H
#include "grman/grman.h"
#include <iostream>
#include <vector>
class Sommet
{
    public:
        Sommet(std::string nom_animal,std::string nom_image,int couleur,int x,int y,int pop, bool isAnimal,float rythme_croissance);
        virtual ~Sommet();
        void update();
        grman::WidgetBox& get_box();
        int utilise();
        int selectionne();
        int population(){return m_popp;}
        void dynamique_pop(float k,float l);
        void set_couleur(int i);
        int get_connexe(){return m_connexe;}
        void set_connexe(int connexe){m_connexe=connexe;}
        std::string get_nom(){return m_nom_animal;}
        std::vector<int> m_historique;
        void set_historique(){m_historique.push_back(m_popp);}
        std::vector<int> get_historique(){return m_historique;}
        std::string save();


    protected:

    private:
        std::string m_nom_animal,m_nom_image;int m_couleur,m_x,m_y,m_popp,m_utilise;
        int m_selectionne;
        int m_connexe;
        bool m_isAnimal;
        float m_rythme_croissance;
        grman::WidgetButton m_bouton;
        grman::WidgetButton m_selec;
        grman::WidgetBox m_box;
        grman::WidgetImage m_img;
        grman::WidgetText m_legende;
        grman::WidgetText m_pop;
        grman::WidgetVSlider m_regle;
        grman::WidgetVSlider m_regle_croissance;
};

#endif // SOMMET_H
