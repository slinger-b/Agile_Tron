#include "game.h"

Game::Game(int choixNbrJoueurs, bool bonus)
{
    nbrJoueurs = choixNbrJoueurs;

    posDepart[0][0]=300;
    posDepart[0][1]=301;
    posDepart[1][0]=300;
    posDepart[1][1]=299;
    posDepart[2][0]=301;
    posDepart[2][1]=300;
    posDepart[3][0]=299;
    posDepart[3][1]=300;

    dirDepart[0] = BAS;
    dirDepart[1] = HAUT;
    dirDepart[2] = DROITE;
    dirDepart[3] = GAUCHE;

    vitDepart = 3;

    motogagnante=0;

    for (int i=0;i<nbrJoueurs;++i)
    {
        motos.push_back(Bike(posDepart[i],vitDepart,dirDepart[i]));
    }

    traverseMur = bonus;

}

Liste* Game::getMurMoto(int i)const
{
    return motos[i].get_liste();
}

int Game::getNbrJoueurs()const
{
    return nbrJoueurs;
}

bool Game::suiteGame(dir keyPress[4])
{
    //verifie_tournant
    for (int i=0; i<nbrJoueurs; ++i)
    {
        if (keyPress[i]!=RIEN)
        {
            motos[i].chgDir(keyPress[i]);
            keyPress[i]=RIEN;
        }
    }

    //fait avancer toutes les motos
    for (int i=0; i<nbrJoueurs;++i)
        motos[i].avance();

    //verifie_si_collision (et appelle les fonctions de perte si necessaire)
    for (int i=0;i<nbrJoueurs;++i)
    {
        for (int j=0;j<nbrJoueurs;++j)
        {
            if(Game::collision(motos[i],motos[j]))
            {
                motos[i].perduCollision();
            }
        }
    }

    //fonction qui détruit les murs des motos qui ont perdues
    for (int i = 0; i<nbrJoueurs; ++i)
    {
        if (motos[i].getPerdu())
        {
            motos[i].perd();
        }
    }

    //regarde combien de motos il reste
    int nbrMotosRestantes = 0;
    for (int i= 0; i<nbrJoueurs;++i)
        if (!motos[i].getPerdu())
            nbrMotosRestantes++;
    if (nbrMotosRestantes<2)
    {
        motogagnante = 0;
        for (int i=0; i<nbrJoueurs; ++i)
            if (!motos[i].getPerdu())
            {
                motos[i].gagne();
                motos[i].perd(); //sert à détruire les murs
                motogagnante=i+1;
            }
        reinitialise();
        return false;
    }
    return true;
}

void Game::reinitialise()
{
    for(int i = 0; i<nbrJoueurs; ++i)
    {
        motos[i].reinitialise();
    }
}

//verifie quand une moto touche le mur d'une autre moto
bool Game::collision(Bike &motoTest, Bike &motoMur)//ATTENTION, TEST EST DEVENU UN POINTEURS
{
    //récupère les deux derniers points du mur pour le test
    bool perdu=false;
    Liste* test = motoTest.get_liste();
    dir dirTest = (motoTest.get_invers_dir());
    int vit = motoTest.get_vitesse();
    int pos1 [2],pos2[2];
    test->premier();
    test->getElem(pos1);
    pos2[0]=pos1[0];pos2[1]=pos1[1];
    ajoute_avance(pos2,dirTest,vit);

    //recupere le debut du mur de la moto "mur"
    Liste* mur = motoMur.get_liste();
    int cur1[2], cur2[2];
    mur->premier();   //se met en début de liste
    mur->getElem(cur1);

    //Si sort de l'écran
    if (traverseMur == false)
    {
        if (pos1[0]>600 || pos1[0]<0 || pos1[1]>600 || pos1[1]<0)
            return true;
    }

    if(mur->getNextElem(cur2) && pos1[0]==cur1[0] && pos1[1]==cur1[1] && motoTest.get_dir() == motoMur.get_dir())
    {
        mur->suivant();//si on a la même moto, il ne faut pas tester le premier mur sinon tjs collision !!!
        if (!mur->getNextElem(cur1))
            return false;
    }
    while(mur->getNextElem(cur2) && !perdu)
    {
        perdu = verifPartielle(pos1,pos2,cur1,cur2);
        cur1[0]=cur2[0];
        cur1[1]=cur2[1];
        mur->suivant();
    }

    if (traverseMur == true)
    {
        motoTest.traverseMur();
    }
    return perdu;
}

bool Game::verifPartielle(int pos1[2],int pos2[2],int cur1[2],int cur2[2])
{
    if(cur1[0]==cur2[0])
    {
        if (pos1[0]==cur1[0])
        {
            if(entre(pos1[1],cur1[1],cur2[1])) return true;
            if(entre(pos2[1],cur1[1],cur2[1])) return true;
            if(entre(cur1[1],pos1[1],pos2[1])) return true;

        }
        else if (pos1[1] == pos2[1])
        {
            if(entre(cur1[0],pos1[0],pos2[0]) && entre(pos1[1],cur1[1],cur2[1]))return true;
        }
    }
    else if (cur1[1] == cur2[1])
    {
        if (pos1[1]==cur1[1])
        {
            if(entre(pos1[0],cur1[0],cur2[0])) return true;
            if(entre(pos2[0],cur1[0],cur2[0])) return true;
            if(entre(cur1[0],pos1[0],pos2[0])) return true;

        }
        else if (pos1[0] == pos2[0])
        {
            if(entre(cur1[1],pos1[1],pos2[1]) && entre(pos1[0],cur1[0],cur2[0])) return true;
        }
    }
    //else il y a un problème : le serpent avance en diagonale
    return false;
}

bool Game::entre(int a, int bord1, int bord2)
{
    return (a<=bord1&&a>=bord2)||(a<=bord2&&a>=bord1);
}
