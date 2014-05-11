#include <QtGui/QApplication>
#include "mainwidget.h"

//typedef int pos2 [2];//dit que pos est un type "tableau de 2 int"
//Bike (*motos)[4]; //déclaration d'un pointeur sur un tableua de 4 éléms
//Bike * motos [4]; //déclaration d'un tab de 4 pointeurs

//pointeurs et tableaux :
//http://www.siteduzero.com/tutoriel-3-321485-tableaux-pointeurs-et-allocation-dynamique.html

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWidget w;
    w.show();

    return a.exec();
}
