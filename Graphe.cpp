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
    m_interface_fond.add_child(m_graphique_bouton);
    m_graphique_bouton.set_frame(780,5,88,78);

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
    int nbr;float facteur;float rythme_croissance;
    string nom_animal, nom_image;int couleur, x, y,pop;
    bool isAnimal;
    int s1,s2;
    std::ifstream fic(fichier,ios::in);
    if(fic)
    {
    fic>>nbr;
    for(int i=0;i<nbr;i++)
    {
        fic>>nom_animal>>nom_image>>couleur>>x>>y>>pop>>isAnimal>>rythme_croissance;
        Sommets.push_back(new Sommet(nom_animal,nom_image,couleur,x,y,pop,isAnimal,rythme_croissance));
    }
    fic>>nbr;
    for(int i=0;i<nbr;i++)
    {
        fic>>s1>>s2>>facteur;
        Aretes.push_back(new Arete(Sommets[s1]->get_box(),Sommets[s2]->get_box(),s1,s2,facteur));
    }
    }
    else{allegro_message("Fichier non trouvé");}

}
void Graphe::update()
{
    int z=0;int lolilol=0;int changement=0;std::vector<int> historique;std::string ecriture;
    if(m_graphique_bouton.clicked())
    {
        m_graphe_fenetre.push_back(new grman::WidgetBox);
        m_graphe_bouton.push_back(new grman::WidgetButton);
        m_legende1.push_back(new grman::WidgetText);
        m_legende2.push_back(new grman::WidgetText);
        m_interface_fond.add_child(*m_graphe_fenetre[y]);
        m_graphe_fenetre[y]->add_child(*m_legende1[y]);
        m_graphe_fenetre[y]->add_child(*m_legende2[y]);
        m_graphe_fenetre[y]->set_bg_color(BLEUCLAIR);
        m_graphe_fenetre[y]->set_moveable();
        m_graphe_fenetre[y]->add_child(*m_graphe_bouton[y]);
        m_graphe_bouton[y]->set_frame(479,1,20,20);
        m_legende1[y]->set_frame(5,5,20,20);
        m_legende1[y]->set_text_color(ROUGE);
        m_legende2[y]->set_text_color(BLEU);
        m_legende2[y]->set_frame(5,15,20,20);
        m_graphe_bouton[y]->set_bg_color(ROUGE);
        m_graphe_fenetre[y]->set_frame(520,350,500,300);
        for(int i=0;i<(signed)Sommets.size();i++)
        {
            if(Sommets[i]->selectionne()==2&&Sommets[i]->utilise())
            {
                historique=Sommets[i]->get_historique();
                if(historique.size()!=0)
                {
                    m_graphe_point.clear();
                    m_segment.clear();
                    m_legende1[y]->set_message(Sommets[i]->get_nom());
                    for(int j=0;j<(signed)historique.size();j++)
                    {
                        m_graphe_point.push_back(new grman::WidgetCheckBox);
                        m_graphe_fenetre[y]->add_child(*m_graphe_point[j]);
                        m_graphe_point[j]->set_frame((500*j)/historique.size(),300-(historique[j]*3),5,5);
                        if(j!=0)
                        {
                            m_segment.push_back(new grman::WidgetEdge);
                            m_graphe_fenetre[y]->add_child(*m_segment[j-1]);
                            m_segment[j-1]->reset_no_items();
                            m_segment[j-1]->attach_to(*m_graphe_point[j]);
                            m_segment[j-1]->attach_from(*m_graphe_point[j-1]);
                            m_segment[j-1]->set_m_color(ROUGE);
                        }
                    }
                }
            }

            if(Sommets[i]->selectionne()==1&&Sommets[i]->utilise())
            {
                historique=Sommets[i]->get_historique();
                if(historique.size()!=0)
                {
                    m_graphe_point.clear();
                    m_segment.clear();
                    m_legende2[y]->set_message(Sommets[i]->get_nom());
                    for(int j=0;j<(signed)historique.size();j++)
                    {
                        m_graphe_point.push_back(new grman::WidgetCheckBox);
                        m_graphe_fenetre[y]->add_child(*m_graphe_point[j]);
                        m_graphe_point[j]->set_frame((500*j)/historique.size(),300-(historique[j]*3),5,5);
                        if(j!=0)
                        {
                            m_segment.push_back(new grman::WidgetEdge);
                            m_graphe_fenetre[y]->add_child(*m_segment[j-1]);
                            m_segment[j-1]->reset_no_items();
                            m_segment[j-1]->attach_to(*m_graphe_point[j]);
                            m_segment[j-1]->attach_from(*m_graphe_point[j-1]);
                            m_segment[j-1]->set_m_color(BLEU);
                        }
                    }
                }
            }
        }
        y++;
    }
    if(m_structurel.clicked())
    {
        int itsok=0;
        for(int i=0;i<(signed)Sommets.size();i++)
        {
            if(!Sommets[i]->utilise())
                itsok=1;
        }
        if(itsok==1)
        {
            allegro_message("Veuillez sauvegarder avant de faire cette action");
        }
        else
        {
        int* rep;
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
        rep=k_connexe(m_tab_adjacence,Sommets.size());
        ecriture="c'est un ";
        ecriture+=to_string(rep[0]);
        ecriture+="-uplet. ";
        ecriture+="nbr combi:";
        ecriture+=to_string(rep[1]);
        for(int i=0;i<rep[1]*rep[0];i++)
        {
            ecriture+=" ";
            if((rep[i+2])<(signed)Sommets.size()&&(rep[i+2])>=0)
                ecriture+=Sommets[rep[(i)+2]]->get_nom();
        }
        result=toutesLesComposantesFortementConnexes(m_tab_adjacence,Sommets.size());
        m_sous_graphe.push_back(new grman::WidgetBox);
        m_Text.push_back(new grman::WidgetText);
        m_sous_graphe_bouton.push_back(new grman::WidgetButton);
        m_interface_fond.add_child(*m_sous_graphe[x]);
        m_sous_graphe[x]->set_bg_color(BLEUCLAIR);
        m_sous_graphe[x]->set_moveable();
        m_sous_graphe[x]->add_child(*m_sous_graphe_bouton[x]);
        m_sous_graphe[x]->add_child(*m_Text[x]);
        m_Text[x]->set_message(ecriture);
        m_Text[x]->set_frame(10,290,10000,10000);
        m_sous_graphe[x]->set_frame(7455,350,500,300);
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
            for(int i=0;i<(signed)Aretes.size();i++)
            {
                if(Sommets[Aretes[i]->sommet1()]->get_connexe()!=Sommets[Aretes[i]->sommet2()]->get_connexe())
                {
                    m_lien_sous_graphe.push_back(Sommets[Aretes[i]->sommet1()]->get_connexe());
                    m_lien_sous_graphe.push_back(Sommets[Aretes[i]->sommet2()]->get_connexe());
                }
                m_lien_sous_graphe_edge=new grman::WidgetEdge[m_lien_sous_graphe.size()/2];
            for(int i=0;i<(signed)m_lien_sous_graphe.size()/2;i++)
            {
                m_sous_graphe[x]->add_child(m_lien_sous_graphe_edge[i]);
                m_lien_sous_graphe_edge[i].reset_arrow_with_bullet();
                m_lien_sous_graphe_edge[i].attach_from(m_les_sommets_sous_graphe[m_lien_sous_graphe[2*i]]);
                m_lien_sous_graphe_edge[i].attach_to(m_les_sommets_sous_graphe[m_lien_sous_graphe[2*i+1]]);
            }
            }
        x++;

        rest(500);
    }
    }
    m_interface_fond.update();
    for(int i=0;i<x;i++)
        if(x!=0)
            if(m_sous_graphe_bouton[i]->clicked())
            {
                m_sous_graphe[i]->set_frame(7450,350,500,300);
            }
    for(int i=0;i<y;i++)
        if(y!=0)
            if(m_graphe_bouton[i]->clicked())
            {
                m_graphe_fenetre[i]->set_frame(7450,350,500,300);
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
        Sommets.push_back(new Sommet(str,image,0,100,100,1,m_isAnimal,1));
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
        for(int i=0;i<(signed)Sommets.size();i++)
        {
            Sommets[i]->set_historique();
        }
    }
    for(int i=0;i<x;i++)
    m_sous_graphe[i]->update();
    for(int i=0;i<y;i++)
        m_graphe_fenetre[i]->update();
}
void Graphe::Sauver_Graphe()
{
    m_sauvegarde=1;
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
        allegro_message("Il n'y a pas 2 sommets de couleur differente selectionnes, creation d arete impossible");
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
int* Graphe::k_connexe(int** adj,int ordre)
{
    int combinaisons[200][10];int vrai;int nombre=0;int i_reel;int j_reel;
    int** matrice={0};
    int stock[300];
    int curseur=0;
    int*resulat;
    if(!connexe(adj,ordre))
    {
        allegro_message("le graphe n'est pas connexe");
        resulat=new int;
        resulat[0]=0;
    }
    else
    {
        vrai=0;
        while(vrai==0)
        {
            nombre++;
            k_parmi_n(combinaisons,ordre,nombre);
            for(int i=0;i<ordre-nombre;i++)
            {
                matrice=new int*[ordre-nombre];
                for(int j=0;j<ordre-nombre;j++)
                {
                    matrice[j]=new int[ordre-nombre];
                }
            }
            for(int k=0;k<(factoriel(ordre)/(factoriel(nombre)*(factoriel(ordre-nombre))));k++)
            {
                for(int j=0;j<nombre;j++)
                {
                    stock[(curseur*(nombre))+j]=combinaisons[k*(nombre)][j]-1;
                }
                for(int i=0;i<ordre;i++)
                {
                    for(int j=0;j<ordre;j++)
                    {
                        i_reel=i;
                        j_reel=j;
                        for(int l=0;l<nombre;l++)
                        {
                            if(combinaisons[k][l]<=i)
                            {
                                i_reel--;
                            }
                            if(combinaisons[k][l]<=j)
                            {
                                j_reel--;
                            }
                            if(i_reel<ordre-nombre&&j_reel<ordre-nombre)
                                matrice[i_reel][j_reel]=adj[i][j];

                        }
                    }
                }
                if(!connexe(matrice,ordre-nombre))
                {
                    vrai=1;
                    curseur++;

                }
            }
            delete matrice;
        }
        resulat=new int [2+curseur*(nombre+1)];
        resulat[0]=nombre;
        resulat[1]=curseur;
        for(int i=0;i<curseur*nombre;i++)
        {
            resulat[i+2]=stock[i];
        }
    }
    return resulat;
}
//source rendu tp 2 Mongault Quentin Da Costa Soares Romain
bool Graphe::connexe(int** adj,int ordre)
{
    std::vector<int> sommets;
    int* marquage;int fait=0;
    marquage=new int[ordre];
    for(int i=0;i<ordre;i++)
    {
        marquage[i]=0;
    }
    for(int i=0;i<ordre;i++)
    {
        for(int j=0;j<ordre;j++)
        {
            if(adj[i][j]==1&& fait==0)
            {
                fait=i;
            }
        }
    }

            sommets.push_back(fait);
            marquage[fait]=1;
            int changement=1;
            while(changement!=0)
            {
                changement=0;
                for(int i=0;i<(signed)sommets.size();i++)
                {
                    for(int j=0;j<ordre;j++)
                    {
                        if(marquage[j]!=1&&(adj[sommets[i]][j]==1||adj[j][sommets[i]]==1))
                        {
                            marquage[j]=1;
                            sommets.push_back(j);
                            changement=1;
                        }
                    }
                }
            }
        if(ordre==(signed)sommets.size())
            return true;
        else
            return false;
    }
//source:http://www.commentcamarche.net/forum/affich-4567474-algo-affichage-combinaison-de-p-elemt-parmi-n
void Graphe::k_parmi_n(int combinaisons[200][10],int n,int k)
{
int comb[40] = {0};
int i = 0;int m=0;
while (i >= 0) {
if (comb[i] < n + i - k + 1)
    {
        comb[i]++;
        if (i == k - 1)
        {
            for (int j = 0; j < k; j++)
            {
                combinaisons[m][j]= comb[j];
            }
            m++;
        }
        else { comb[++i] = comb[i - 1]; }
    }
    else i--; }
}
int Graphe::factoriel(int lol)
{
    int resultat=lol;
    while(lol!=1)
    {
        lol--;
        resultat=resultat*lol;
    }
    return resultat;
}
