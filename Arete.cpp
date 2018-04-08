#include "Arete.h"

using namespace std;

Arete::Arete(grman::WidgetBox& sommet1,grman::WidgetBox& sommet2,int lsommet1,int lsommet2,float facteur)
{
    m_facteur=facteur;
    m_utilise=1;
    m_sommet1=lsommet1;
    m_sommet2=lsommet2;
    m_top_box.set_frame(500, 600, 0, 0);
    m_top_box.add_child( m_lien );
    m_lien.attach_from(sommet2);
    m_lien.attach_to(sommet1);
    m_lien.reset_arrow_with_bullet();
    m_lien.add_child(m_bouton);
    m_bouton.set_dim(10,10);
    m_bouton.set_bg_color(ROUGE);
    m_lien.add_child(m_regle);
    m_regle.set_range(0, 5, false); // 3ème param true => valeurs entières
    m_regle.set_frame(10,-25,20,40);
    m_regle.set_bg_color(ROSE);
    m_regle.set_value(m_facteur);
    m_lien.add_child(m_box);
    m_box.set_bg_color(ROSE);
    m_box.set_frame(10,15,20,15);
    m_box.add_child(m_legende);
    m_legende.set_message(to_string(m_facteur));
    m_legende.set_bg_color(ROSE);
}
void Arete::update(vector<Sommet*> Sommets)
{
    m_facteur=m_regle.get_value();
    m_legende.set_message(to_string(m_facteur));
    if(m_bouton.clicked())
    {
        m_utilise=0;
    }
    if(Sommets[m_sommet1]->utilise()&&Sommets[m_sommet2]->utilise())
        m_top_box.update();
    else
        m_utilise=0;
}
std::string Arete::save(vector<int> sommets_non_utilise)
{
    string chaine;int newsommet1,newsommet2;
    newsommet1=m_sommet1;newsommet2=m_sommet2;
    for(int i=0;i<(signed)sommets_non_utilise.size();i++)
    {
        if(m_sommet1>sommets_non_utilise[i])
            newsommet1=newsommet1-1;
        if(m_sommet2>sommets_non_utilise[i])
            newsommet2=newsommet2-1;
    }
    chaine=to_string(newsommet1);
    chaine+=" ";
    chaine+=to_string(newsommet2);
    chaine+=" ";
    chaine+=to_string(m_facteur);
    return chaine;
}
Arete::~Arete()
{
    //dtor
}
int Arete::utilise()
{
    return m_utilise;
}
