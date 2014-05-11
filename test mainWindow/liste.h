#ifndef LISTE_H
#define LISTE_H

#include <QPoint>
#include <node.h>

class Liste
{
public:
    //Constructeurs et Destructeurs
    Liste();
    Liste(Liste const& ListeACopier); // Le prototype du constructeur de copie
    ~Liste();
    Liste(int pos[2]);

    //Fonctions liées à la liste en elle-même
    bool push(int pos[2]);//rajoute un élément
    bool delete_top();
    bool top(int pos[2]);//renvoie le premier élément de la liste
    bool pop(int pos[2]);//renvoie et supprime le premier élément de la liste
    bool all_delete();

    //Fonctions liées à la lecture de la liste
    bool premier();//réinitialise la lecture de la liste en son début (Elem revient au début de la liste)
    bool suivant();//se place au prochain élément sur la liste (Eleme va au rpochain élément)
    bool getElem(int pos[2]);//renvoie le point où se trouve le curseur Elem.
    bool getNextElem(int pos[2]);//renvoie le point suivant de l'endroit où se trouve le curseur Elem.


private:
    Node* Head;
    //se déplace sur la liste et joue le rôle de "cur", mais dans la partie auquel on ne peut pas avoir accès dans une classe (private)
    Node* Elem;
};

#endif // LISTE_H
