#ifndef GRAPHE_H
#define GRAPHE_H
#include "Sommet.h"
#include "vector"
#include <fstream>
#include <sstream>
#include "Arete.h"

class Graphe
{
    public:
        Graphe(std::string fichier);
        virtual ~Graphe();
        void Charger_Graphe(std::string fichier);
        void update();
        void Sauver_Graphe();
        void Nouveau_Sommet();
        void Nouvelle_Arete();
        void la_vie_suit_son_cours();

    protected:

    private:
        int temps;
        grman::WidgetBox m_interface_fond;
        grman::WidgetButton m_bouton_sauvegarder;
        grman::WidgetButton m_bouton_supprimer;
        grman::WidgetButton m_bouton_add_sommet;
        grman::WidgetButton m_bouton_add_arete;
        grman::WidgetButton m_bouton_start;
        grman::WidgetImage m_fond_image;
        grman::WidgetImage m_start_image;
        grman::WidgetClavier m_clavier;

        bool ifrecup;bool start;
        std::string m_fichier;
        std::string str;
        std::string image;
        std::vector<Sommet*> Sommets;
        std::vector<Arete*> Aretes;
};

#endif // GRAPHE_H
