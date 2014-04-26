#include "bike.h"

Bike::Bike() //consructeur par defaut
{
    PosSuccessives = new Liste ();
    score = 0;
    vitesse = 0;
    direction = RIEN;
    chgmt_dir = false;
    perdu = false;

    posDep[0] = 0;
    posDep[1] = 0;
    vitDep = 0;
    dirDep = RIEN;
}

Bike::Bike(int pos_depart[], int vitesse_depart, dir dir_depart)
{
    PosSuccessives = new Liste(pos_depart);
    PosSuccessives->push(pos_depart);
    score = 0;

    vitesse = vitesse_depart;
    direction = dir_depart;
    chgmt_dir = false;

    posDep[0] = pos_depart[0];
    posDep[1] = pos_depart[1];
    vitDep = vitesse_depart;
    dirDep = dir_depart;

    perdu = false;
}


Bike::Bike (Bike const& BikeACopier) // Le constructeur de copie
{
    int pos [2];
    const Liste* listeACopier = BikeACopier.get_liste();
    Liste* liste = new Liste(*listeACopier);

    liste->premier();
    PosSuccessives = new Liste();

    if (liste!=NULL)
    {
        liste->getElem(pos);
        PosSuccessives->push(pos);
    }
    while (liste->suivant())
    {
        liste->getElem(pos);
        PosSuccessives->push(pos);
    }
    score = BikeACopier.score;

    vitesse = BikeACopier.vitesse;
    direction =  BikeACopier.direction;
    chgmt_dir = BikeACopier.chgmt_dir;

    perdu = BikeACopier.perdu;

    posDep[0] = BikeACopier.posDep[0];
    posDep[1] = BikeACopier.posDep[1];
    vitDep = BikeACopier.vitDep;
    dirDep = BikeACopier.dirDep;
}

Bike::~Bike()
{
    (this->get_liste())->all_delete();
}


void Bike::reinitialise()
{
    PosSuccessives->push(posDep);
    PosSuccessives->push(posDep);

    vitesse = vitDep;
    direction = dirDep;

    perdu = false;
}

//fonction qui permet de faire avancer dans la dir la liste
void Bike::avance()
{
    int postemp[2];
    if(chgmt_dir==true)
    {
        PosSuccessives->top(postemp);
        ajoute_avance(postemp, direction, vitesse);
        PosSuccessives->push(postemp);
        chgmt_dir=false;
    }
    else
    {
        PosSuccessives->pop(postemp);
        ajoute_avance(postemp, direction, vitesse);
        PosSuccessives->push(postemp);
    }
}

void ajoute_avance(int pos[2], dir direct, int vit)
{
    if (direct == DROITE)
        pos[0]+=vit;
    else if (direct == GAUCHE)
        pos[0]-=vit;
    else if (direct == BAS)
        pos[1]+=vit;
    else if (direct == HAUT)
        pos[1]-=vit;
}

void Bike::gagne()
{
    score+=1;
}

void Bike::perduCollision()
{
    perdu=true;
}

void Bike::perd()
{
    PosSuccessives->all_delete();
}

//permet de changer de direction, d'incrémenter la vitesse ou de la diminuer
void Bike::chgDir (dir nv_dir)
{
    if(nv_dir==direction)
        vitesse++;
    else if(nv_dir == get_invers_dir())
    {
        if (vitesse>2)
            vitesse--;
    }
    else
    {
        direction = nv_dir;
        chgmt_dir = true;
    }
}

void Bike::traverseMur()
{
    int pos[2];
    PosSuccessives->premier();
    PosSuccessives->getElem(pos);
    if (pos[0]<0)
    {
        int temp[2] = {pos[0]-50,pos[1]};
        PosSuccessives->push(temp);
        temp[1] = temp[1]-1000;
        PosSuccessives->push(temp);
        temp[0]=temp[0]+1000;
        PosSuccessives->push(temp);
        temp[1] = temp[1]+1000;
        PosSuccessives->push(temp);
        temp[0]=600;temp[1]=pos[1];
        PosSuccessives->push(temp);
    }
    else if (pos[0]>600)
    {
        int temp[2] = {pos[0]+50,pos[1]};
        PosSuccessives->push(temp);
        temp[1] = temp[1]-1000;
        PosSuccessives->push(temp);
        temp[0]=temp[0]-1000;
        PosSuccessives->push(temp);
        temp[1] = temp[1]+1000;
        PosSuccessives->push(temp);
        temp[0]=0;temp[1]=pos[1];
        PosSuccessives->push(temp);
    }
    else if (pos[1]>600)
    {
        int temp[2] = {pos[0],pos[1]+50};
        PosSuccessives->push(temp);
        temp[0] = temp[0]-1000;
        PosSuccessives->push(temp);
        temp[1]=temp[1]-1000;
        PosSuccessives->push(temp);
        temp[0] = temp[0]+1000;


        PosSuccessives->push(temp);
        temp[1]=0;temp[0]=pos[0];
        PosSuccessives->push(temp);
    }
    else if (pos[1]<0)
    {
        int temp[2] = {pos[0],pos[1]-50};
        PosSuccessives->push(temp);
        temp[0] = temp[0]+1000;
        PosSuccessives->push(temp);
        temp[1]=temp[1]+1000;
        PosSuccessives->push(temp);
        temp[0] = temp[0]-1000;
        PosSuccessives->push(temp);
        temp[0]=pos[0];temp[1]=600;
        PosSuccessives->push(temp);
    }

}

int Bike::get_vitesse()const
{
    return vitesse;
}

Liste* Bike::get_liste()const
{
    return PosSuccessives;
}

dir Bike::get_dir()const
{
    return direction;
}

dir Bike::get_invers_dir()const
{
    if (direction==HAUT)
        return BAS;
    else if (direction == BAS)
        return HAUT;
    else if (direction == DROITE)
        return GAUCHE;
    else
        return DROITE;
}
