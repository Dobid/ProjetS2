#include "Sommet.h"
#include "string"
using namespace std;
Sommet::Sommet(string nom_animal,string nom_image,int couleur,int x,int y,int pop, bool isAnimal,float rythme_croissance)
{
    m_rythme_croissance=rythme_croissance;
    m_isAnimal = isAnimal;
    m_connexe=0;
    m_utilise=1;m_selectionne=0;
    m_nom_animal=nom_animal;m_nom_image=nom_image;m_couleur=couleur;m_x=x;m_y=y;m_popp=pop;
    m_box.set_frame(x, y, 120, 90);
    if(couleur==0)
        m_box.set_bg_color(VERT);
    if(couleur==1)
        m_box.set_bg_color(ROUGE);
    m_box.set_moveable();

    m_box.add_child(m_legende);
    m_legende.set_message(nom_animal);
    m_legende.set_gravity_y(grman::GravityY::Down );

    m_box.add_child(m_img);
    m_img.set_pic_name(nom_image);
    m_img.set_gravity_xy(grman::GravityX::Right,grman::GravityY::Up);

    m_box.add_child(m_regle);
    m_regle.set_bg_color(BLANC);
    m_regle.set_gravity_xy(grman::GravityX::Left,grman::GravityY::Center);
    m_regle.set_range(0, 100, true); // 3ème param true => valeurs entières
    m_regle.set_frame(1,31,15,48);
    m_regle.set_value(pop);

    m_box.add_child(m_regle_croissance);
    m_regle_croissance.set_bg_color(BLANC);
    m_regle_croissance.set_gravity_xy(grman::GravityX::Left,grman::GravityY::Center);
    m_regle_croissance.set_range(0.1, 1, false); // 3ème param true => valeurs entières
    m_regle_croissance.set_frame(1,1,15,29);
    m_regle_croissance.set_value(m_rythme_croissance);
    m_box.add_child(m_bouton);
    m_bouton.set_frame(110,0,10,10);
    m_bouton.set_bg_color(ROUGE);

    m_box.add_child(m_selec);
    m_selec.set_frame(110,80,10,10);
    m_selec.set_bg_color(BLANC);

    m_box.add_child(m_pop);
    m_pop.set_message("0");
    m_pop.set_gravity_xy(grman::GravityX::Left,grman::GravityY::Down);
    //ctor
}

Sommet::~Sommet()
{
    //dtor
}
void Sommet::update()
{
    m_pop.set_message(std::to_string((int)m_regle.get_value()));
    m_popp=m_regle.get_value();
    m_rythme_croissance=m_regle_croissance.get_value();
    m_box.update();
    if(m_bouton.clicked())
    {
        m_utilise=0;
    }
    if(m_selec.clicked())
    {
        if(m_selectionne==0)
        {
            m_selec.set_bg_color(BLEU);
            m_selectionne=1;
        }
        else if(m_selectionne==2)
        {
            m_selectionne=0;
            m_selec.set_bg_color(BLANC);
        }
        else
        {
            m_selectionne=2;
            m_selec.set_bg_color(MARRONCLAIR);
        }
    }
    m_y=m_box.get_posy();
    if(m_y<110)
    {
        m_y=110;
        m_box.set_posy(110);
    }
    m_x=m_box.get_posx();
}
grman::WidgetBox& Sommet::get_box()
{
    return m_box;
}
string Sommet::save()
{
    string chaine;
    chaine=m_nom_animal;
    chaine+=" ";
    chaine+=m_nom_image;
    chaine+=" ";
    chaine+=to_string(m_couleur);
    chaine+=" ";
    chaine+=to_string(m_x);
    chaine+=" ";
    chaine+=to_string(m_y);
    chaine+=" ";
    chaine+=to_string((int)m_regle.get_value());
    chaine+= " ";
    chaine+=to_string(m_isAnimal);
    chaine+=" ";
    chaine+=to_string(m_rythme_croissance);
    return chaine;
}
int Sommet::utilise()
{
    return m_utilise;
}
int Sommet::selectionne()
{
    return m_selectionne;
}
void Sommet::dynamique_pop(float k,float l)
{
    if(m_isAnimal)
    {
    float valeur;
    if(k!=0)
        valeur=m_popp+(m_rythme_croissance*(float)m_popp*(1-((float)m_popp/(k))))-l;
    else
        valeur=m_popp-l;
    if(valeur>100){valeur=100;}
    if(valeur<0){valeur=0;}
    m_regle.set_value(valeur);
    if(k==0&&l==0)
    {
        m_regle.set_value(0);
    }
}
else{m_regle.set_value(m_popp+m_popp*m_rythme_croissance-l);}
}
void Sommet::set_couleur(int i)
{
    switch(i)
    {
    case 0:m_box.set_bg_color(BLANCBLEU);break;
    case 1:m_box.set_bg_color(VERTFLUO);break;
    case 2:m_box.set_bg_color(JAUNE);break;
    case 3:m_box.set_bg_color(ROUGE);break;
    case 4:m_box.set_bg_color(VIOLET);break;
    case 5:m_box.set_bg_color(MARRONCLAIR);break;
    case 6:m_box.set_bg_color(VIOLETCLAIR);break;
    case 7:m_box.set_bg_color(ORANGE);break;
    case 8:m_box.set_bg_color(BLEU);break;
    case 9:m_box.set_bg_color(MARRON);break;
    case 10:m_box.set_bg_color(BLANC);break;
    case 11:m_box.set_bg_color(KAKI);break;
    case 12:m_box.set_bg_color(CYAN);break;
    case 13:m_box.set_bg_color(SABLE);break;
    case 14:m_box.set_bg_color(ROSE);break;
    case 15:m_box.set_bg_color(FUCHSIA);break;
    case 16:m_box.set_bg_color(NOIR);break;
    case 17:m_box.set_bg_color(BLANCJAUNE);break;
    case 18:m_box.set_bg_color(BLANCROSE);break;
    case 19:m_box.set_bg_color(VIOLETSOMBRE);break;
    }


}
