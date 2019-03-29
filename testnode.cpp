#include "node.h"
#include <vector> //pour crÃ©er des vecteurs !!! (allocation dynamique facile!!!

#include <iostream>

#include <QtTest/QtTest>

class TestNode: public QObject
{
        Q_OBJECT

private slots:

    void nodecopydata();
    void createnode();
    void nodecopynextNULL();
    void nodecopynext();

private:
    Node* node, nodenext;
    int pos [2];
};

void TestNode::createnode()
{
        pos[0] = 1;
        pos[1] = 0;
        Node* node = new Node(pos);

        QVERIFY(node->data[0]==pos[0]);
        QVERIFY(node->data[1]==pos[1]);

        delete node;
}

void TestNode::nodecopydata()
{
        pos[0] = 1;
        pos[1] = 0;
        Node* node = new Node();
        node->copieData(pos);

        QVERIFY(node->data[0]==pos[0]);
        QVERIFY(node->data[1]==pos[1]);
}

void TestNode::nodecopynextNULL()
{
        pos[0] = 1;
        pos[1] = 0;
        Node* node = new Node(pos,NULL);

        QVERIFY(node->data[0]==pos[0]);
        QVERIFY(node->data[1]==pos[1]);
        QVERIFY(node->next==NULL);
}

void TestNode::nodecopynext()
{
        pos[0] = 1;
        pos[1] = 0;
        Node* node = new Node(pos,NULL);
        Node* nodenext = new Node(pos,node);

        QVERIFY(node->data[0]==pos[0]);
        QVERIFY(node->data[1]==pos[1]);
        QVERIFY(nodenext->next==node);
}

QTEST_MAIN(TestNode)
#include "testnode.moc"
