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
        int**toutesLesComposantesFortementConnexes(int** adjacence,int ordre);
        int* uneComposanteFortementConnexe(int** adjacence,int ordre,int s);

    protected:

    private:
        bool m_isAnimal;
        int temps;
        int x=0;
        int** m_tab_adjacence;
        int** result;
        grman::WidgetBox m_interface_fond;
        grman::WidgetButton m_bouton_sauvegarder;
        grman::WidgetButton m_bouton_add_ressource;
        grman::WidgetButton m_bouton_add_sommet;
        grman::WidgetButton m_bouton_add_arete;
        grman::WidgetButton m_bouton_start;
        grman::WidgetButton m_structurel;
        grman::WidgetImage m_fond_image;
        grman::WidgetImage m_start_image;
        grman::WidgetClavier m_clavier;
        grman::WidgetImage m_fond_bleu;
        grman::WidgetBox m_fonctionnel;
        std::vector< grman::WidgetBox*> m_sous_graphe;
        std::vector<grman::WidgetButton*> m_sous_graphe_bouton;
        grman::WidgetBox* m_les_sommets_sous_graphe;
        std::vector<int> m_lien_sous_graphe;
        grman::WidgetEdge* m_lien_sous_graphe_edge;

        bool ifrecup;bool start;
        std::string m_fichier;
        std::string str;
        std::string image;
        std::vector<Sommet*> Sommets;
        std::vector<Arete*> Aretes;
};

#endif // GRAPHE_H
