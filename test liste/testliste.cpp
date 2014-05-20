#include "liste.h"
#include "node.h"
//#include <vector> //pour cr√©er des vecteurs !!! (allocation dynamique facile!!!

//#include <iostream>

#include <QtTest/QtTest>

class TestListe: public QObject
{
        Q_OBJECT

private slots:

    //Fonctions liÈes ‡ la liste en elle-mÍme
    void push_and_top();
    void delete_top_and_pop();

    ////Fonctions liÈes ‡ la lecture de la liste
    void getElem_suivant_premier_getNextElem();

private:
    Node* node1,node2;
    int pos1 [2],pos2 [2],posTchek [2];
};


void TestListe::push_and_top()
{
        pos1[0]= 4;
        pos1[1]= 10;

        Liste* Liste1 = new Liste();
        Liste1->push(pos1);

        Liste1->top(posTchek);

        QVERIFY(posTchek[0]==pos1[0]);
        QVERIFY(posTchek[1]==pos1[1]);

        delete Liste1;
}

void TestListe::delete_top_and_pop()
{
        pos1[0]= 4;
        pos1[1]= 10;
        pos2[0]= 11;
        pos2[1]= 11;

        Liste* Liste1 = new Liste();
        Liste1->push(pos1); // put 2 new node in the liste
        Liste1->push(pos2);

        Liste1->delete_top(); //remove the last node
        Liste1->top(posTchek);

        QVERIFY(posTchek[0]==pos1[0]); //tchek if the top is the first node
        QVERIFY(posTchek[1]==pos1[1]);
        Liste1->push(pos2); //reput the second node

        Liste1->pop(posTchek);
        QVERIFY(posTchek[0]==pos2[0]); //tchek if the position is the old first node
        QVERIFY(posTchek[1]==pos2[1]);

        Liste1->top(posTchek);

        QVERIFY(posTchek[0]==pos1[0]); //tchek if the old first node was removed
        QVERIFY(posTchek[1]==pos1[1]);

        delete Liste1;
}
void TestListe::getElem_suivant_premier_getNextElem()
{
        pos1[0]= 4;
        pos1[1]= 10;
        pos2[0]= 11;
        pos2[1]= 11;

        Liste* Liste1 = new Liste();
        Liste1->push(pos1); // put 2 new node in the liste
        Liste1->push(pos2);

        Liste1->getElem(posTchek);
        QVERIFY(posTchek[0]==pos1[0]); //tchek getElem
        QVERIFY(posTchek[1]==pos1[1]);

        Liste1->premier();
        Liste1->getElem(posTchek);

        QVERIFY(posTchek[0]==pos2[0]); //tchek if position Head = position Elem
        QVERIFY(posTchek[1]==pos2[1]);

        Liste1->getNextElem(posTchek);

        QVERIFY(posTchek[0]==pos1[0]); //tchek getNext_Elem
        QVERIFY(posTchek[1]==pos1[1]);

        Liste1->suivant();
        Liste1->getElem(posTchek);

        QVERIFY(posTchek[0]==pos1[0]); //tchek suivant
        QVERIFY(posTchek[1]==pos1[1]);

        delete Liste1;
}

QTEST_MAIN(TestListe)
#include "testliste.moc"

