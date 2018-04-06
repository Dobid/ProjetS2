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
    m_bouton_add_arete.set_frame(447,5,88,78);
    m_bouton_add_ressource.set_frame(290,5,88,78);
    m_fond_image.set_frame(0,0,1024,768);
    m_bouton_start.set_frame(560,5,88,78);
    m_structurel.set_frame(670,5,88,78);

    m_interface_fond.add_child(m_fond_image);
    m_interface_fond.add_child(m_bouton_sauvegarder);
    m_interface_fond.add_child(m_bouton_add_arete);
    m_interface_fond.add_child(m_bouton_add_sommet);
    m_interface_fond.add_child(m_bouton_add_ressource);
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
    int nbr;float facteur;
    string nom_animal, nom_image;int couleur, x, y,pop;
    bool isAnimal;
    int s1,s2;
    std::ifstream fic(fichier,ios::in);
    fic>>nbr;
    for(int i=0;i<nbr;i++)
    {
        fic>>nom_animal>>nom_image>>couleur>>x>>y>>pop>>isAnimal;
        Sommets.push_back(new Sommet(nom_animal,nom_image,couleur,x,y,pop,isAnimal));
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
    int z=0;int lolilol=0;int changement=0;
    if(m_structurel.clicked())
    {
        m_tab_adjacence=new int*[Sommets.size()];
        for(int i=0;i<(signed)Sommets.size();i++)
        {
            m_tab_adjacence[i]=new int[Sommets.size()];
        }
        for(int i=0;i<(signed)Sommets.size();i++)
        {
            for(int j=0;j<(signed)Sommets.size();j++)
            {
                m_tab_adjacence[i][j]=0;
            }
        }
        for(int i=0;i<(signed)Aretes.size();i++)
        {
            if(Aretes[i]->utilise())
                m_tab_adjacence[Aretes[i]->sommet1()][Aretes[i]->sommet2()]=1;
        }
        for(int i=0;i<(signed)Sommets.size();i++)
        {
            for(int j=0;j<(signed)Sommets.size();j++)
            {
                cout<<m_tab_adjacence[i][j];
            }
            cout<<endl;
        }
        result=toutesLesComposantesFortementConnexes(m_tab_adjacence,Sommets.size());
        m_sous_graphe.push_back(new grman::WidgetBox);
        m_sous_graphe_bouton.push_back(new grman::WidgetButton);
        m_interface_fond.add_child(*m_sous_graphe[x]);
        m_sous_graphe[x]->set_bg_color(BLEUCLAIR);
        m_sous_graphe[x]->set_moveable();
        m_sous_graphe[x]->add_child(*m_sous_graphe_bouton[x]);
        m_sous_graphe[x]->set_frame(745578451445145520,350,500,300);
        m_sous_graphe_bouton[x]->set_frame(479,1,20,20);
        m_sous_graphe_bouton[x]->set_bg_color(ROUGE);
        m_sous_graphe[x]->set_frame(520,350,500,300);
        m_lien_sous_graphe.clear();
        for(int i=0;i<(signed)Sommets.size();i++)
        {
            changement=0;
            for(int j=0;j<(signed)Sommets.size();j++)
            {
                if(result[i][j]==1)
                {
                    Sommets[j]->set_couleur(lolilol);
                    Sommets[j]->set_connexe(lolilol);
                    changement=1;
                }

            }
            if(changement==1)
                    lolilol++;
        }
            for(int i=0;i<(signed)Sommets.size();i++)
            {
                if(result[i][i]==1)
                {
                    z++;
                }
            }
            m_les_sommets_sous_graphe=new grman::WidgetBox[z];
            for(int i=0;i<z;i++)
            {
                m_sous_graphe[x]->add_child(m_les_sommets_sous_graphe[i]);
                m_les_sommets_sous_graphe[i].set_frame(40*i,40*i,40,40);
                m_les_sommets_sous_graphe[i].set_moveable();
    switch(i)
    {
    case 0:m_les_sommets_sous_graphe[i].set_bg_color(BLANCBLEU);break;
    case 1:m_les_sommets_sous_graphe[i].set_bg_color(VERTFLUO);break;
    case 2:m_les_sommets_sous_graphe[i].set_bg_color(JAUNE);break;
    case 3:m_les_sommets_sous_graphe[i].set_bg_color(ROUGE);break;
    case 4:m_les_sommets_sous_graphe[i].set_bg_color(VIOLET);break;
    case 5:m_les_sommets_sous_graphe[i].set_bg_color(MARRONCLAIR);break;
    case 6:m_les_sommets_sous_graphe[i].set_bg_color(VIOLETCLAIR);break;
    case 7:m_les_sommets_sous_graphe[i].set_bg_color(ORANGE);break;
    case 8:m_les_sommets_sous_graphe[i].set_bg_color(BLEU);break;
    case 9:m_les_sommets_sous_graphe[i].set_bg_color(MARRON);break;
    case 10:m_les_sommets_sous_graphe[i].set_bg_color(BLANC);break;
    case 11:m_les_sommets_sous_graphe[i].set_bg_color(KAKI);break;
    case 12:m_les_sommets_sous_graphe[i].set_bg_color(CYAN);break;
    case 13:m_les_sommets_sous_graphe[i].set_bg_color(SABLE);break;
    case 14:m_les_sommets_sous_graphe[i].set_bg_color(ROSE);break;
    case 15:m_les_sommets_sous_graphe[i].set_bg_color(FUCHSIA);break;
    case 16:m_les_sommets_sous_graphe[i].set_bg_color(NOIR);break;
    case 17:m_les_sommets_sous_graphe[i].set_bg_color(BLANCJAUNE);break;
    case 18:m_les_sommets_sous_graphe[i].set_bg_color(BLANCROSE);break;
    case 19:m_les_sommets_sous_graphe[i].set_bg_color(VIOLETSOMBRE);break;
    }
            }
            for(int i=0;i<Aretes.size();i++)
            {
                if(Sommets[Aretes[i]->sommet1()]->get_connexe()!=Sommets[Aretes[i]->sommet2()]->get_connexe())
                {
                    m_lien_sous_graphe.push_back(Sommets[Aretes[i]->sommet1()]->get_connexe());
                    m_lien_sous_graphe.push_back(Sommets[Aretes[i]->sommet2()]->get_connexe());
                }
                m_lien_sous_graphe_edge=new grman::WidgetEdge[m_lien_sous_graphe.size()/2];
            for(int i=0;i<m_lien_sous_graphe.size()/2;i++)
            {
                m_sous_graphe[x]->add_child(m_lien_sous_graphe_edge[i]);
                m_lien_sous_graphe_edge[i].reset_arrow_with_bullet();
                m_lien_sous_graphe_edge[i].attach_from(m_les_sommets_sous_graphe[m_lien_sous_graphe[i+1]]);
                m_lien_sous_graphe_edge[i].attach_to(m_les_sommets_sous_graphe[m_lien_sous_graphe[i]]);
            }
            }

            cout<<endl;
        x++;
        rest(500);
    }
    m_interface_fond.update();
    for(int i=0;i<x;i++)
        if(x!=0)
            if(m_sous_graphe_bouton[i]->clicked())
            {
                m_sous_graphe[i]->set_frame(745578451445145520,350,500,300);
            }
    if(m_bouton_add_ressource.clicked())
    {
        m_isAnimal=false;
        Nouveau_Sommet();
    }
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
        Sommets.push_back(new Sommet(str,image,0,100,100,1,m_isAnimal));
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
        m_isAnimal=true;
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
    string nom, image;
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
int** Graphe::toutesLesComposantesFortementConnexes(int** adjacence,int ordre)
{
    int** tabc;
    int* marques;
    int x,y;
    tabc=new int*[ordre];
    for(int i=0;i<ordre;i++)
    {
        tabc[i]=new int[ordre];
    }
    marques=new int[ordre];
    for(int i=0;i<ordre;i++)
    {
        marques[i]=0;
        for(int j=0;j<ordre;j++)
        {
            tabc[i][j]=0;
        }
    }
    for(x=0;x<ordre;x++)
    {
        if(!marques[x])
        {
            tabc[x]=uneComposanteFortementConnexe(adjacence,ordre,x);
            marques[x]=1;
            for(y=0;y<ordre;y++)
            if(tabc[x][y]&& !marques[y])
                marques[y]=1;
        }
    }
    return tabc;
}
int* Graphe::uneComposanteFortementConnexe(int** adjacence,int ordre,int s)
{
    int *c1,*c2;
    int *c;
    int* marques;
    int x,y;
    int ajoute=1;

    c=new int[ordre];
    c1=new int[ordre];
    c2=new int[ordre];
    marques=new int[ordre];
    for(int i=0;i<ordre;i++)
    {
        c[i]=0;
        c1[i]=0;
        c2[i]=0;
        marques[i]=0;
    }
    c1[s]=1;c2[s]=1;
    while(ajoute)
    {
        ajoute=0;
        for(x=0;x<ordre;x++)
        {
            if(!marques[x]&&c1[x])
                {
                marques[x]=1;
                for(y=0;y<ordre;y++)
                    {
                        if(adjacence[x][y]&&!marques[y])
                        {
                        c1[y]=1;
                        ajoute=1;
                        }
                    }
                }
        }
    }
    ajoute=1;
    for(int i=0;i<ordre;i++)
    {
        marques[i]=0;
    }
    while(ajoute)
    {
        ajoute=0;
        for(x=0;x<ordre;x++)
        {
            if(!marques[x]&&c2[x])
                {
                marques[x]=1;
                for(y=0;y<ordre;y++)
                    {
                        if(adjacence[y][x]&&!marques[y])
                        {
                        c2[y]=1;
                        ajoute=1;
                        }
                    }
                }
        }
    }
    for(x=0;x<ordre;x++)
    {
        c[x]=c1[x]&c2[x];
    }
    return c;
}
