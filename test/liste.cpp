#include "liste.h"

//Construceur
Liste::Liste()
{
    Head = NULL;
    Elem = Head;
}

// Le constructeur de copie
Liste::Liste (Liste const& ListeACopier)
{

    Head = NULL;
    Node* temp = ListeACopier.Head; //attention, il ne faut pas de delete temp
    while(temp != NULL)
    {
        Head = new Node(temp->data,Head);
        temp = temp -> next;
    }
    Elem = Head;
}

//////////////////////////////CONSTRUCTEUR SURCHARGE, A VERIFIER S'IL MARCHE/////////////////////////////////
Liste::Liste(int pos[2])
{
    Head = new Node(pos);
    Elem = Head;
}

//Destructeur
Liste::~Liste()
{
    /*while(Head!=NULL)
    {
        this->delete_top();
    }*/
}

///////////////////////////////PREMIERE PARTIE : GESTION DE LA LISTE////////////////////////////////////////////:
//rajouter un élément
bool Liste::push(int pos[2])
{
    Head = new Node(pos,Head);
    return true;
}

//supprime le premier élément de la liste
bool Liste::delete_top()
{
    if (Head==NULL)
    {
        return false;
    }
    else
    {
        Node* Temp = Head->next;
        delete Head;
        Head = Temp;
        return true;
    }
}

//delete tous les éléments de la liste
bool Liste::all_delete()
{
    if (Head==NULL)
        return false;
    else
    {
        while(Head!=NULL)
            delete_top();
        return true;
    }
}

//renvoie le premier élément de la liste
bool Liste::top(int pos[2])
{
    if (Head==NULL)
        return false;
    else
        pos[0]=Head->data[0];
        pos[1]=Head->data[1];
        return true;
}


//renvoie et supprime le premier élément de la liste
bool Liste::pop(int pos[2])
{
    return top(pos)&&delete_top();
}

/////////////////DEUXIEME PARTIE : LECTURE DE LA LISTE//////////////////////////////////////////////////
//initialise cur(Elem) au premier élément
bool Liste::premier()
{
        Elem = Head;
        return true;
}

//permet à cur(Elem) d'aller à l'élément suivant
bool Liste::suivant()
{
    if (Elem == NULL)
        return false;
    else if (Elem->next == NULL)
        return false;
    else
        Elem = Elem->next;
        return true;
}

//renvoie l'élément où se trouve cur
bool Liste::getElem(int pos[2])
{
    if (Elem==NULL)
        return false;
    else
        pos[0]=Elem->data[0];
        pos[1]=Elem->data[1];
    return true;
}

//renvoie l'élément suivant de cur(Elem)
bool Liste::getNextElem(int pos[2])
{
    bool ok = true;
    Node* Save = Elem;
    ok = Liste::suivant() && Liste::getElem(pos);
    Elem = Save;
    return ok;
}
