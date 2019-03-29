#include "game.h"

Game::Game(int choixNbrJoueurs, bool bonus)
{
    if (choixNbrJoueurs >= MAXPLAYERS)
        nbrJoueurs = MAXPLAYERS;
    else
        nbrJoueurs = choixNbrJoueurs;

    vitDepart = STARTVELOCITY;
    motogagnante = 0;
    traverseMur = bonus;

    //Player 1
    dirDepart[0] = BAS;
    posDepart[0][0]=STARTPOS;
    posDepart[0][1]=STARTPOS+1;
    //Player 2
    dirDepart[1] = HAUT;
    posDepart[1][0]=STARTPOS;
    posDepart[1][1]=STARTPOS-1;
    //Player 3
    dirDepart[2] = DROITE;
    posDepart[2][0]=STARTPOS+1;
    posDepart[2][1]=STARTPOS;
    //Player 4
    dirDepart[3] = GAUCHE;
    posDepart[3][0]=STARTPOS-1;
    posDepart[3][1]=STARTPOS;

    if (choixNbrJoueurs > 0)
        for (int i=0;i<nbrJoueurs;++i)
            motos.push_back(Bike(posDepart[i],vitDepart,dirDepart[i]));
}

// Main function of the class
// return false if there is one bike left (so the game is finished)
bool Game::suiteGame(dir keyPress[4])
{
    if (nbrJoueurs > 0)
    {
        bike_turn(keyPress);
        bike_move();
        bike_collision();
        bike_loose();

        int nbrMotosRestantes = bike_surviving();

        if (nbrMotosRestantes<2)
        {
            reinitialise();
            return false;
        }
        return true;
    }
    else
        return false;
}

void Game::bike_collision()
{
    for (int i=0;i<nbrJoueurs;++i)
        for (int j=0;j<nbrJoueurs;++j)
            if(Game::collision(motos[i],motos[j]))
                motos[i].perduCollision();
}

bool Game::collision(Bike &motoTest, Bike &motoMur)
{
    // return true when there is a collision
    bool perdu = false;
    int pos1 [2],pos2[2]; //positions of the motoTest and the motoMur respectively
    int cur1[2], cur2[2];
    int vit = motoTest.get_vitesse();

    Liste* test = motoTest.get_liste();
    Liste* mur = motoMur.get_liste();

    dir dirTest = (motoTest.get_invers_dir());

    test->premier();
    test->getElem(pos1);

    mur->premier();
    mur->getElem(cur1);

    pos2[0]=pos1[0];
    pos2[1]=pos1[1];
    ajoute_avance(pos2,dirTest,vit);

    // If the bonus is inactive, the moto loose when touch the wall
    if (traverseMur == false)
        if (pos1[0]>BORDERMAX || pos1[0]<BORDERMIN || pos1[1]>BORDERMAX || pos1[1]<BORDERMIN)
            return true;

    // Otherwise test if motoTest crossed/collided motoMur
    // Test if the indexes are the same. So we're testing if motoTest collides with itself.
    // If yes, we have to fetch the second position of the list in order to do the comparison
    if(mur->getNextElem(cur2) && pos1[0]==cur1[0] && pos1[1]==cur1[1] && motoTest.get_dir() == motoMur.get_dir())
    {
        mur->suivant();
        if (!mur->getNextElem(cur1)) // if the next element of list is null then no collision
            return false;
    }

    // Test over all the list if there is a collision
    // End of the condition when the list of motoMur is empty or there is a collision
    while(mur->getNextElem(cur2) && !perdu)
    {
        perdu = verifPartielle(pos1,pos2,cur1,cur2);
        cur1[0]=cur2[0];
        cur1[1]=cur2[1];
        mur->suivant();
    }
    
    // If the bonus is active, the position of the motoTest has to be changed
    if (traverseMur == true)
        motoTest.traverseMur();
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
            if(entre(cur1[0],pos1[0],pos2[0]) && entre(pos1[1],cur1[1],cur2[1]))return true;
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
            if(entre(cur1[1],pos1[1],pos2[1]) && entre(pos1[0],cur1[0],cur2[0])) return true;
    }
    return false;
}

bool Game::entre(int a, int bord1, int bord2)
{
    return (a<=bord1&&a>=bord2)||(a<=bord2&&a>=bord1);
}

void Game::bike_turn(dir keyPress[4])
{
    for (int i=0; i<nbrJoueurs; ++i)
        if (keyPress[i]!=RIEN)
        {
            motos[i].chgDir(keyPress[i]);
            keyPress[i]=RIEN;
        }
}

void Game::bike_move()
{
    for (int i=0; i<nbrJoueurs;++i)
        motos[i].avance();
}

int Game::bike_surviving()
{
    int nbrMotosRestantes = 0;
    for (int i= 0; i<nbrJoueurs;++i)
        if (!motos[i].getPerdu())
            nbrMotosRestantes++;
    return nbrMotosRestantes;
}

void Game::bike_loose()
{
    for (int i = 0; i<nbrJoueurs; ++i)
        if (motos[i].getPerdu())
            motos[i].deletewall();
}

void Game::reinitialise()
{
    motogagnante = 0;
    for (int i=0; i<nbrJoueurs; ++i)
    {
        if (!motos[i].getPerdu())
        {
            motos[i].gagne();
            motogagnante=i+1;
        }
        motos[i].deletewall();
    }
    for(int i = 0; i<nbrJoueurs; ++i)
        motos[i].reinitialise();
}

// ------------- FETCH THE PRIVATE PARAMETERS -------------
Liste* Game::getMurMoto(int i)const
{
    return motos[i].get_liste();
}

int Game::getNbrJoueurs()const
{
    return nbrJoueurs;
}
