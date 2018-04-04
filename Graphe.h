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

    protected:

    private:
        grman::WidgetBox m_interface_fond;
        grman::WidgetButton m_bouton_sauvegarder;
        grman::WidgetButton m_bouton_supprimer;
        grman::WidgetButton m_bouton_add_sommet;
        grman::WidgetButton m_bouton_add_arete;
        grman::WidgetImage m_fond_image;

        std::string m_fichier;
        std::vector<Sommet*> Sommets;
        std::vector<Arete*> Aretes;
};

#endif // GRAPHE_H
