#include "grman/grman.h"
#include <iostream>
#include "Graphe.h"
#include <fstream>
using namespace std;
int main()
{
    grman::init();
    grman::set_pictures_path("images");
    std::string fichier;int ok=0;

    grman::WidgetBox menu_fond;
    grman::WidgetButton nouveau;
    grman::WidgetButton charger;

    menu_fond.set_frame(0,0,1024,768);
    nouveau.set_frame(313,596,411,76);
    charger.set_frame(313,683,411,76);

    grman::WidgetImage image_fond;
    grman::WidgetClavier Clavier;
    //grman::WidgetImage image_nouveau;
    //grman::WidgetImage image_charger;

    menu_fond.add_child(image_fond);
    menu_fond.add_child(nouveau);
    menu_fond.add_child(charger);
    menu_fond.add_child(Clavier);


    //image_fond.set_gravity_xy(grman::GravityX::Left,grman::GravityY::Up);
    image_fond.set_pic_name("fond.jpg");
    //image_nouveau.set_pic_name("creer.jpg");
    //image_charger.set_pic_name("charger.jpg");

    int arret=0;
    int sauvegarder=0;
    while(!key[KEY_ESC]&&arret==0)
    {
        ok=0;
        while(ok==0)
        {
            if(sauvegarder==0)
            {
            menu_fond.update();
            nouveau.update();
            charger.update();
            grman::mettre_a_jour();
            if(nouveau.clicked())
            {
                ok=1;
                cout<<"nom du nouveau graphe?"<<endl;
                Clavier.initialiser(414-512,553-384);
                while(Clavier.bloque()!=1)
                {
                    menu_fond.update();
                    Clavier.update();
                    grman::mettre_a_jour();
                }
                fichier=Clavier.recup_chaine();
                fichier+=".txt";
                std::ofstream fic(fichier,ios::out);
                fic<<"0"<<endl<<"0";

            }
            if(charger.clicked())
            {
                cout<<"nom du graphe a charger?"<<endl;
                Clavier.initialiser(414-512,553-384);
                while(Clavier.bloque()!=1)
                {
                    menu_fond.update();
                    Clavier.update();
                    grman::mettre_a_jour();
                }
                fichier=Clavier.recup_chaine();
                fichier+=".txt";
                ok=1;
            }
            if(key[KEY_ESC])
            {
                ok=1;
                arret=1;
            }
        }
        else
        {
            sauvegarder=0;
            ok=1;
        }
        }
        if(arret!=1)
        {
            Graphe k(fichier);
            while ( !key[KEY_ESC] &&sauvegarder==0)
            {
                k.update();
                sauvegarder=k.get_sauvegarde();
                grman::mettre_a_jour();
            }
            rest(200);
        }
    }
        grman::fermer_allegro();

    return 0;
}
END_OF_MAIN();
