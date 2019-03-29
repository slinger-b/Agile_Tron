#ifndef BIKE_H
#define BIKE_H

#include <liste.h>

enum dir {HAUT, DROITE, BAS, GAUCHE, RIEN};

void ajoute_avance(int pos[2], dir direct, int vit);

class Bike
{
public:

    Bike(); //constructeur par defaut
    Bike(int pos_depart[], int vitesse_depart, dir dir_depart);
    Bike(Bike const& BikeACopier); // Le prototype du constructeur de copie
    ~Bike();

    void chgDir (dir nv_dir);
    void avance();
    void traverseMur();
    void traverseMur_up(int pos[2]);
    void traverseMur_down(int pos[2]);
    void traverseMur_left(int pos[2]);
    void traverseMur_right(int pos[2]);

    void gagne();
    void deletewall();
    void perduCollision();

    void reinitialise();

    int get_vitesse()const;
    Liste* get_liste()const;
    dir get_dir()const;
    dir get_invers_dir()const;
    int getScore()const{return score;}
    bool getPerdu()const{return perdu;}

private:

    int posDep[2];
    int vitDep;
    dir dirDep;

    Liste* PosSuccessives;

    int vitesse;
    dir direction;

    bool chgmt_dir;

    int score;
    bool perdu;
};

#endif // BIKE_H
