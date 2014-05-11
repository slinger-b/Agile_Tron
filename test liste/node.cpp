#include "node.h"

Node::Node(int pos[2], Node* a)
{
    data[0] = pos[0];
    data[1] = pos[1];
    next = a;
}

Node::Node(Node const& NodeACopier) // Le constructeur de copie
{
    next = NodeACopier.next;
    data[0]=NodeACopier.data[0];
    data[1]=NodeACopier.data[1];
}

void Node::copieData (int pos[2])
{
    pos[0]=data[0];
    pos[1]=data[1];
}

