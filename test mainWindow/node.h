#ifndef NODE_H
#define NODE_H

#include <QtDebug>

#include <vector> //pour créer des vecteurs !!! (allocation dynamique facile!!!

#include <iostream>
using namespace std;


class Node
{
public:

    int data[2];
    Node* next;
    Node():next(NULL){};
    Node(Node const& NodeACopier); // Le prototype du constructeur de copie
    Node(int pos[2], Node* a=NULL);

    void copieData (int pos[2]);
};

#endif // NODE_H
