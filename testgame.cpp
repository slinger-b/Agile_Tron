#include "liste.h"
#include "node.h"
#include "game.h"
#include <vector> //pour créer des vecteurs !!! (allocation dynamique facile!!!

#include <iostream>

#include <QtTest/QtTest>

class TestGame: public QObject
{
        Q_OBJECT

private slots:

    void creation_game();
    void start_position();
    void pos1D_between_borders();
    void pos2D_between_borders();
    void test_reinit();
    void test_reinit_player_0();

private:
    Game* testgame;
    int player, pos1[2], pos2[2], pos3[2], pos4[2];
    int a, b, c;
    bool bonus;
    dir keypressed[4];
};

void TestGame::creation_game()
{
    player = 2; bonus = false;
    Game* testgame = new Game(player,bonus);
    QVERIFY(player==testgame->getNbrJoueurs());
    delete testgame;
}

void TestGame::start_position()
{
    player = 4; bonus = false;
    Game* testgame = new Game(player,bonus);
    testgame->getMurMoto(0)->top(pos1);
    testgame->getMurMoto(1)->top(pos2);
    testgame->getMurMoto(2)->top(pos3);
    testgame->getMurMoto(3)->top(pos4);
    QVERIFY(pos1[0]==STARTPOS);
    QVERIFY(pos1[1]==STARTPOS+1);
    QVERIFY(pos2[0]==STARTPOS);
    QVERIFY(pos2[1]==STARTPOS-1);
    QVERIFY(pos3[0]==STARTPOS+1);
    QVERIFY(pos3[1]==STARTPOS);
    QVERIFY(pos4[0]==STARTPOS-1);
    QVERIFY(pos4[1]==STARTPOS);
    delete testgame;
}

// Testing condition
void TestGame::pos1D_between_borders()
{
    Game* testgame = new Game(4,false);

    a = 0; b = a; c = a;
    QVERIFY(true==testgame->entre(a,b,c));
    a = 1; b = 2; c = 3;
    QVERIFY(false==testgame->entre(a,b,c));
    a = 1; b = 3; c = 2;
    QVERIFY(false==testgame->entre(a,b,c));
    a = 2; b = 1; c = 3;
    QVERIFY(true==testgame->entre(a,b,c));
    a = 2; b = 3; c = 1;
    QVERIFY(true==testgame->entre(a,b,c));
    a = 3; b = 2; c = 1;
    QVERIFY(false==testgame->entre(a,b,c));
    a = 3; b = 1; c = 2;
    QVERIFY(false==testgame->entre(a,b,c));
    a = 1; b = 2; c = 2;
    QVERIFY(false==testgame->entre(a,b,c));
    a = 1; b = 2; c = 1;
    QVERIFY(true==testgame->entre(a,b,c));
    a = 1; b = 1; c = 2;
    QVERIFY(true==testgame->entre(a,b,c));

    delete testgame;
}

// Testing branching : not all testing because Game::entre already tested
void TestGame::pos2D_between_borders()
{
    Game* testgame = new Game(4,false);

    pos1[0] = 1; pos1[1] = 2; // cur1[0] = cur2[0] -- 3[0] = 4[0]
    pos2[0] = 0; pos2[1] = 2; // pos1[0] = cur1[0] -- 1[0] = 3[0]
    pos3[0] = 1; pos3[1] = 0; // pos1[1] = pos2[1] -- 1[1] = 2[1]
    pos4[0] = 1; pos4[1] = 0; // cur1[1] = cur2[1] < pos1[1]
    QVERIFY(testgame->verifPartielle(pos1,pos2,pos3,pos4)==false); //OK

    pos1[0] = 0; pos1[1] = 1; // cur1[0] = cur2[0] -- 3[0] = 4[0]
    pos2[0] = 0; pos2[1] = 0; // pos1[0] = cur1[0] -- 1[0] = 3[0]
    pos3[0] = 1; pos3[1] = 0; // pos1[1] != pos2[1]
    pos4[0] = 1; pos4[1] = 0;
    QVERIFY(testgame->verifPartielle(pos1,pos2,pos3,pos4)==false); //OK

    pos1[0] = 1; pos1[1] = 1; // cur1[0] != cur2[0] -- 3[0] != 4[0]
    pos2[0] = 0; pos2[1] = 0; // cur1[1] = cur2[1] -- 3[1] = 4[1]
    pos3[0] = 1; pos3[1] = 1; // pos1[1] = cur1[1] -- 1[1] = 3[1]
    pos4[0] = 0; pos4[1] = 0; // pos1[0] != pos2[0] -- 1[0] != 2[0]
    QVERIFY(testgame->verifPartielle(pos1,pos2,pos3,pos4)==false); //OK

    pos1[0] = 2; pos1[1] = 1; // cur1[0] != cur2[0] -- 3[0] != 4[0]
    pos2[0] = 2; pos2[1] = 0; // cur1[1] = cur2[1] -- 3[1] = 4[1]
    pos3[0] = 1; pos3[1] = 1; // pos1[1] = cur1[1] -- 1[1] = 3[1]
    pos4[0] = 0; pos4[1] = 0; // pos1[0] = pos2[0] -- 1[0] = 2[0]
                              // cur1[0], cur2[0] < pos1[0]
    QVERIFY(testgame->verifPartielle(pos1,pos2,pos3,pos4)==false); //OK

    pos1[0] = 0; pos1[1] = 0; // cur1[0] != cur2[0] -- 3[0] != 4[0]
    pos2[0] = 0; pos2[1] = 0; // cur1[1] != cur2[1] -- 3[1] != 4[1]
    pos3[0] = 1; pos3[1] = 1;
    pos4[0] = 0; pos4[1] = 0;
    QVERIFY(testgame->verifPartielle(pos1,pos2,pos3,pos4)==false); //OK

    pos1[0] = 0; pos1[1] = 4; // cur1[0] = cur2[0] -- 3[0] = 4[0]
    pos2[0] = 0; pos2[1] = 3; // pos1[0] = cur1[0] -- 1[0] = 3[0]
    pos3[0] = 0; pos3[1] = 1; //
    pos4[0] = 0; pos4[1] = 0;
    QVERIFY(testgame->verifPartielle(pos1,pos2,pos3,pos4)==false); //OK

    pos1[0] = 4; pos1[1] = 0; // cur1[0] != cur2[0] -- 3[0] != 4[0]
    pos2[0] = 3; pos2[1] = 0; // cur1[1] = cur2[1] -- 3[1] = 4[1]
    pos3[0] = 1; pos3[1] = 0;
    pos4[0] = 0; pos4[1] = 0;
    QVERIFY(testgame->verifPartielle(pos1,pos2,pos3,pos4)==false); //OK

    delete testgame;
}

void TestGame::test_reinit()
{
    for (player = 1;player<=4;player++)
    {
        Game* testgame = new Game(player,false);
        if (player > 0)
        {
            testgame->bike_move();
            testgame->reinitialise();
            testgame->getMurMoto(0)->top(pos1);
            QVERIFY(pos1[0]==STARTPOS);
            QVERIFY(pos1[1]==STARTPOS+1);
        }
        QVERIFY(player==testgame->getMotoGagnante());
        delete testgame;
    }
}

void TestGame::test_reinit_player_0()
{
    player = 0;
    keypressed[0] = RIEN; keypressed[1] = RIEN;
    keypressed[2] = RIEN; keypressed[3] = RIEN;
    Game* testgame = new Game(player,false);
    QVERIFY(false==testgame->suiteGame(keypressed));
    delete testgame;
}


QTEST_MAIN(TestGame)
#include "testgame.moc"
