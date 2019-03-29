#include "node.h"
#include "liste.h"
#include "bike.h"
#include <vector> //pour créer des vecteurs !!! (allocation dynamique facile!!!

#include <iostream>

#include <QtTest/QtTest>

class TestBike: public QObject
{
        Q_OBJECT

private slots:

    void create_bike_empty();
    void directiondown();
    void directionup();
    void directionleft();
    void directionright();
    void velocity_increase();
    void velocity_decrease();
    void velocity_unchanged_decrease();
    void bike_move_up();
    void bike_move_down();
    void bike_move_left();
    void bike_move_right();
    void bike_no_move();
    void delete_listbike();
    void reinit_listbike();
    void dir_chng_up_left();
    void dir_chng_up_right();
    void dir_chng_up_none();
    void dir_chng_down_left();
    void dir_chng_down_right();
    void dir_chng_down_none();
    void dir_chng_left_down();
    void dir_chng_left_up();
    void dir_chng_left_none();
    void dir_chng_right_down();
    void dir_chng_right_up();
    void dir_chng_right_none();
    void through_wall_left();
    void through_wall_right();
    void through_wall_up();
    void through_wall_down();
    void through_wall_down_none();
    void score_win();
    void test_loose();

private:
    Bike* testbike;
    Liste* listbike;
    int pos [2], newpos[2], vel, score, winorloose;
    dir dirct, dirctinv;
};

void TestBike::create_bike_empty()
{
    Bike* testbike = new Bike();  
    QVERIFY(RIEN==testbike->get_dir());
    QVERIFY(RIEN==testbike->get_invers_dir());
    QVERIFY(0==testbike->get_vitesse());
    QVERIFY(0==testbike->getScore());
    QVERIFY(false==testbike->getPerdu());
    delete testbike;
}

void TestBike::directiondown()
{
    pos[0]=0; pos[1]=0; vel=0;
    Bike* testbike = new Bike(pos,vel,BAS);
    QVERIFY(BAS==testbike->get_dir());
    QVERIFY(HAUT==testbike->get_invers_dir());
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::directionup()
{
    pos[0]=0; pos[1]=0; vel=0;
    Bike* testbike = new Bike(pos,vel,HAUT);
    QVERIFY(HAUT==testbike->get_dir());
    QVERIFY(BAS==testbike->get_invers_dir());
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::directionleft()
{
    pos[0]=0; pos[1]=0; vel=0;
    Bike* testbike = new Bike(pos,vel,GAUCHE);
    QVERIFY(GAUCHE==testbike->get_dir());
    QVERIFY(DROITE==testbike->get_invers_dir());
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::directionright()
{
    pos[0]=0; pos[1]=0; vel=0;
    Bike* testbike = new Bike(pos,vel,DROITE);
    QVERIFY(DROITE==testbike->get_dir());
    QVERIFY(GAUCHE==testbike->get_invers_dir());
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::velocity_increase()
{
    pos[0]=0; pos[1]=0; vel=0;
    Bike* testbike = new Bike(pos,vel,HAUT);
    testbike->chgDir(HAUT);
    QVERIFY(1==testbike->get_vitesse());
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::velocity_decrease()
{
    pos[0]=0; pos[1]=0; vel=4;
    Bike*testbike = new Bike(pos,vel,HAUT);
    testbike->get_liste()->top(newpos);
    testbike->chgDir(BAS);
    QVERIFY(vel-1==testbike->get_vitesse());
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::velocity_unchanged_decrease()
{
    pos[0]=0; pos[1]=0; vel=0;
    Bike* testbike = new Bike(pos,vel,HAUT);
    testbike->chgDir(BAS);
    testbike->get_liste()->top(newpos);
    QVERIFY(vel==testbike->get_vitesse());
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::bike_move_up()
{
    pos[0]=0; pos[1]=0; vel=2;
    Bike* testbike = new Bike(pos,vel,HAUT);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]-vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::bike_move_down()
{
    pos[0]=0; pos[1]=0; vel=2;
    Bike* testbike = new Bike(pos,vel,BAS);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]+vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::bike_move_left()
{
    pos[0]=0; pos[1]=0; vel=2;
    Bike* testbike = new Bike(pos,vel,GAUCHE);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]-vel);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::bike_move_right()
{
    pos[0]=0; pos[1]=0; vel=2;
    Bike* testbike = new Bike(pos,vel,DROITE);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]+vel);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::bike_no_move()
{
    pos[0]=0; pos[1]=0; vel=2;
    Bike* testbike = new Bike(pos,vel,RIEN);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::delete_listbike()
{
    pos[0]=10; pos[1]=5; vel=1;
    Bike* testbike = new Bike(pos,vel,HAUT);
    Liste* listbike = new Liste();
    testbike->avance();
    testbike->deletewall();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==0);
    QVERIFY(newpos[1]==0);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete listbike;
    delete testbike;

}

void TestBike::reinit_listbike()
{
    pos[0]=10; pos[1]=5; vel=1;
    Bike* testbike = new Bike(pos,vel,HAUT);
    testbike->avance();
    testbike->deletewall();
    testbike->reinitialise();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_up_left()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,HAUT);
    testbike->avance();
    testbike->chgDir(GAUCHE);
    QVERIFY(testbike->get_dir()==GAUCHE);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]-vel);
    QVERIFY(newpos[1]==pos[1]-vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_up_right()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,HAUT);
    testbike->avance();
    testbike->chgDir(DROITE);
    QVERIFY(testbike->get_dir()==DROITE);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]+vel);
    QVERIFY(newpos[1]==pos[1]-vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_up_none()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,HAUT);
    testbike->avance();
    testbike->chgDir(RIEN);
    QVERIFY(testbike->get_dir()==RIEN);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]-vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_down_left()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,BAS);
    testbike->avance();
    testbike->chgDir(GAUCHE);
    QVERIFY(testbike->get_dir()==GAUCHE);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]-vel);
    QVERIFY(newpos[1]==pos[1]+vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_down_right()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,BAS);
    testbike->avance();
    testbike->chgDir(DROITE);
    QVERIFY(testbike->get_dir()==DROITE);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]+vel);
    QVERIFY(newpos[1]==pos[1]+vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_down_none()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,BAS);
    testbike->avance();
    testbike->chgDir(RIEN);
    QVERIFY(testbike->get_dir()==RIEN);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==pos[1]+vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_left_up()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,GAUCHE);
    testbike->avance();
    testbike->chgDir(HAUT);
    QVERIFY(testbike->get_dir()==HAUT);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]-vel);
    QVERIFY(newpos[1]==pos[1]-vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_left_down()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,GAUCHE);
    testbike->avance();
    testbike->chgDir(BAS);
    QVERIFY(testbike->get_dir()==BAS);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]-vel);
    QVERIFY(newpos[1]==pos[1]+vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_left_none()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,GAUCHE);
    testbike->avance();
    testbike->chgDir(RIEN);
    QVERIFY(testbike->get_dir()==RIEN);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]-vel);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_right_up()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,DROITE);
    testbike->avance();
    testbike->chgDir(HAUT);
    QVERIFY(testbike->get_dir()==HAUT);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]+vel);
    QVERIFY(newpos[1]==pos[1]-vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_right_down()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,DROITE);
    testbike->avance();
    testbike->chgDir(BAS);
    QVERIFY(testbike->get_dir()==BAS);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]+vel);
    QVERIFY(newpos[1]==pos[1]+vel);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::dir_chng_right_none()
{
    pos[0]=0; pos[1]=0; vel=1;
    Bike* testbike = new Bike(pos,vel,DROITE);
    testbike->avance();
    testbike->chgDir(RIEN);
    QVERIFY(testbike->get_dir()==RIEN);
    testbike->avance();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]+vel);
    QVERIFY(newpos[1]==pos[1]);
    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::through_wall_left()
{
    pos[0]=-1; pos[1]=50; vel=1;
    Bike* testbike = new Bike(pos,vel,GAUCHE);
    testbike->traverseMur();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==600);
    QVERIFY(newpos[1]==pos[1]);

    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::through_wall_right()
{
    pos[0]=601; pos[1]=50; vel=1;
    Bike* testbike = new Bike(pos,vel,DROITE);
    testbike->traverseMur();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==0);
    QVERIFY(newpos[1]==pos[1]);

    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::through_wall_up()
{
    pos[0]=50; pos[1]=-1; vel=1;
    Bike* testbike = new Bike(pos,vel,HAUT);
    testbike->traverseMur();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==600);

    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::through_wall_down()
{
    pos[0]=50; pos[1]=601; vel=1;
    Bike* testbike = new Bike(pos,vel,BAS);
    testbike->traverseMur();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==0);

    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::through_wall_down_none()
{
    pos[0]=50; pos[1]=601; vel=1;
    Bike* testbike = new Bike(pos,vel,RIEN);
    testbike->traverseMur();
    testbike->get_liste()->top(newpos);
    QVERIFY(newpos[0]==pos[0]);
    QVERIFY(newpos[1]==0);

    QVERIFY(testbike->get_vitesse()==vel);
    QVERIFY(testbike->getScore()==0);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::score_win()
{
    Bike* testbike = new Bike();
    testbike->gagne();
    QVERIFY(testbike->getScore()==1);
    QVERIFY(testbike->getPerdu()==false);
    delete testbike;
}

void TestBike::test_loose()
{
    Bike* testbike = new Bike();
    testbike->perduCollision();
    QVERIFY(testbike->getPerdu()==true);
    QVERIFY(testbike->getScore()==0);
    delete testbike;
}


QTEST_MAIN(TestBike)
#include "testbike.moc"
