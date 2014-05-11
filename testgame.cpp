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

private:
    Game* testgame;
    int player, pos1[2], pos2[2], pos3[2], pos4[2];
    bool bonus;
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

QTEST_MAIN(TestGame)
#include "testgame.moc"
