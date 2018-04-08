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
        bool connexe(int** adj,int ordre);
        virtual ~Graphe();
        void Charger_Graphe(std::string fichier);
        void update();
        void Sauver_Graphe();
        void Nouveau_Sommet();
        void Nouvelle_Arete();
        void la_vie_suit_son_cours();
        int**toutesLesComposantesFortementConnexes(int** adjacence,int ordre);
        int* uneComposanteFortementConnexe(int** adjacence,int ordre,int s);
        int* k_connexe(int**adjacence,int ordre);
        void k_parmi_n(int combinaisons[200][10],int n,int k);
        int factoriel(int lol);
        int get_sauvegarde(){return m_sauvegarde;}


    protected:

    private:
        bool m_isAnimal;
        int temps;
        int m_sauvegarde=0;
        int x=0;int y=0;
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

        grman::WidgetButton m_graphique_bouton;
        std::vector< grman::WidgetBox*> m_graphe_fenetre;
        std::vector<grman::WidgetText*>m_Text;
        std::vector<grman::WidgetButton*> m_graphe_bouton;
        std::vector<grman::WidgetCheckBox*> m_graphe_point;
        std::vector<grman::WidgetEdge*> m_segment;
        std::vector<grman::WidgetText*> m_legende1;
        std::vector<grman::WidgetText*> m_legende2;

        bool ifrecup;bool start;
        std::string m_fichier;
        std::string str;
        std::string image;
        std::vector<Sommet*> Sommets;
        std::vector<Arete*> Aretes;
};

#endif // GRAPHE_H
