#include "Graphe.h"
using namespace std;
Graphe::Graphe(std::string fichier)
{
    temps=0;
    ifrecup = true;
    start=false;
    m_fichier=fichier;
    Charger_Graphe(fichier);

    m_fonctionnel.add_child(m_fond_bleu);
    m_fonctionnel.set_frame(0,0,1024,768);
    m_fond_bleu.set_frame(0,0,1024,768);
    m_fond_bleu.set_pic_name("fond_bleu.jpg");

    m_interface_fond.set_frame(0,0,1024,110);
    m_bouton_sauvegarder.set_frame(6,5,88,78);
    m_bouton_add_sommet.set_frame(116,5,88,78);
    m_bouton_add_arete.set_frame(273,5,88,78);
    m_bouton_supprimer.set_frame(418,5,88,78);
    m_fond_image.set_frame(0,0,1024,768);
    m_bouton_start.set_frame(520,5,88,78);
    m_structurel.set_frame(620,5,88,78);

    m_interface_fond.add_child(m_fond_image);
    m_interface_fond.add_child(m_bouton_sauvegarder);
    m_interface_fond.add_child(m_bouton_add_arete);
    m_interface_fond.add_child(m_bouton_add_sommet);
    m_interface_fond.add_child(m_bouton_supprimer);
    m_interface_fond.add_child(m_clavier);
    m_interface_fond.add_child(m_bouton_start);
    m_interface_fond.add_child(m_structurel);
    m_bouton_start.add_child(m_start_image);
    m_start_image.set_pic_name("lecture.jpg");




    //m_bouton_sauvegarder.set_bg_color(FUCHSIA);

    m_fond_image.set_pic_name("interface.jpg");
    //m_bouton_sauvegarder_image.set_pic_name("sauvegarder.jpg");
    //m_bouton_supprimer_image.set_pic_name("supprimer.jpg");
    //m_bouton_ajouter_image.set_pic_name("ajouter.jpg");
}
Graphe::~Graphe()
{

}
void Graphe::Charger_Graphe(std::string fichier)
{
    int nbr;int facteur;
    string nom_animal, nom_image;int couleur, x, y,pop;
    int s1,s2;
    std::ifstream fic(fichier,ios::in);
    fic>>nbr;
    for(int i=0;i<nbr;i++)
    {
        fic>>nom_animal>>nom_image>>couleur>>x>>y>>pop;
        Sommets.push_back(new Sommet(nom_animal,nom_image,couleur,x,y,pop));
    }
    fic>>nbr;
    for(int i=0;i<nbr;i++)
    {
        fic>>s1>>s2>>facteur;
        Aretes.push_back(new Arete(Sommets[s1]->get_box(),Sommets[s2]->get_box(),s1,s2,facteur));
    }

}
void Graphe::update()
{
    if(m_structurel.clicked())
    {
        while(!key[KEY_ESC])
        {
            m_fonctionnel.update();
            grman::mettre_a_jour();
        }
    }
    m_interface_fond.update();

    if(m_bouton_start.clicked())
    {
        if(start==false)
        {
            start=true;
            m_start_image.set_pic_name("pause.jpg");
        }
        else if(start==true)
        {
            start=false;
            m_start_image.set_pic_name("lecture.jpg");
        }
    }
    if(m_clavier.bloque()==1 && ifrecup == false)
    {
        str = m_clavier.recup_chaine();
        ifrecup = true;
        image = str;
        image+= ".jpg";
        Sommets.push_back(new Sommet(str,image,0,100,100,1));
        m_clavier.initialiser(10000,100000);
    }

    if ( m_bouton_sauvegarder.clicked())
        {
            Sauver_Graphe();
        }

    if(m_clavier.bloque()!=1 && ifrecup == false)
    {
       m_clavier.update();
    }

    if(m_bouton_add_sommet.clicked())
    {
        Nouveau_Sommet();
    }
    if(m_bouton_add_arete.clicked())
    {
        Nouvelle_Arete();
    }
    for(int i=0;i<(signed)Sommets.size();i++)
    {
        if(Sommets[i]->utilise())
            Sommets[i]->update();
    }
    for(int i=0;i<(signed)Aretes.size();i++)
    {
        if(Aretes[i]->utilise())
            Aretes[i]->update(Sommets);
    }
    if(start==true)
        temps++;
    if(temps==10)
    {
        temps=0;
        la_vie_suit_son_cours();
    }
}
void Graphe::Sauver_Graphe()
{
    vector<int> sommets_non_utilise;
    int nbr_sommets=0,nbr_aretes=0;
    for(int i=0;i<(signed)Sommets.size();i++)
    {
        nbr_sommets=nbr_sommets+Sommets[i]->utilise();
    }
    std::ofstream fichier(m_fichier,ios::out);
    fichier<<nbr_sommets<<endl;
    for(int i=0;i<(signed)Sommets.size();i++)
    {
        if(Sommets[i]->utilise())
            fichier<<Sommets[i]->save()<<endl;
        else
            sommets_non_utilise.push_back(i);
    }
    for(int i=0;i<(signed)Aretes.size();i++)
    {
        nbr_aretes=nbr_aretes+Aretes[i]->utilise();
    }
    fichier<<nbr_aretes<<endl;
    for(int i=0;i<(signed)Aretes.size();i++)
    {
        if(Aretes[i]->utilise())
        fichier<<Aretes[i]->save(sommets_non_utilise)<<endl;
    }

}
void Graphe::Nouveau_Sommet()
{
    string nom, image;int type;
    m_clavier.initialiser(18-512,744-384);
    ifrecup = false;

}
void Graphe::Nouvelle_Arete()
{
    int nbr_selec1=0,nbrselec2=0;int lsommet1=0;int lsommet2=0;
    for(int i=0;i<(signed)Sommets.size();i++)
    {
        if(Sommets[i]->utilise()==1&&Sommets[i]->selectionne()==1)
        {
            nbr_selec1++;
            lsommet1=i;

        }
        if(Sommets[i]->utilise()==1&&Sommets[i]->selectionne()==2)
        {
            nbrselec2++;
            lsommet2=i;
        }
    }
    if(nbr_selec1!=1||nbrselec2!=1)
    {
        cout<<"Il n'y a pas 2 sommets de couleur differente selectionnes, creation d arete impossible"<<endl;
    }
    else
    {
        Aretes.push_back(new Arete(Sommets[lsommet1]->get_box(),Sommets[lsommet2]->get_box(),lsommet1,lsommet2,0));
    }
}
void Graphe::la_vie_suit_son_cours()
{
    float k=0;float l=0;
    for(int i=0;i<(signed)Sommets.size();i++)
    {
        if(Sommets[i]->utilise())
        {

            for(int j=0;j<(signed)Aretes.size();j++)
            {

                if(Aretes[j]->utilise())
                {
                    if(Aretes[j]->sommet1()==i)
                    {
                        k=k+(((float)Aretes[j]->facteur())*((float)Sommets[Aretes[j]->sommet2()]->population()));
                    }
                    if(Aretes[j]->sommet2()==i)
                    {
                        l=l+(((float)Aretes[j]->facteur())*((float)Sommets[Aretes[j]->sommet1()]->population()));
                    }
                }
            }
            cout<<k<<" "<<l<<endl;
            Sommets[i]->dynamique_pop(k,l);
            k=0;l=0;
        }
    }
}
