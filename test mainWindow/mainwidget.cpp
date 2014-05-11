#include "mainwidget.h"
#include <QDebug>
#include <QSound>
#include <QPixmap>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setFixedSize(iSize_Height,iSize_Width);
    setPalette(QPalette(QColor(128,128,128)));
    setAutoFillBackground(true);

    fondEcran1 = QPixmap("./Tron.jpg");
    fondEcran2 = QPixmap("./piste.jpg");
    fondEcran3 = QPixmap("motosvolantes.jpg");
    fondEcran4 = QPixmap("./cadrePapillon.jpg");

    touches2 = QPixmap("./deuxJoueurs.jpg");
    touches3 = QPixmap("./troisJoueurs.jpg");
    touches4 = QPixmap("./quatreJoueurs.jpg");

    motoH.load("./hmoto.jpg");
    motoV.load("./vmoto.jpg");

    // musique = new QSound("./musiqueDeFond.WAV");

    // musique.setLoops(1000);
    // musique->play();

    //On doit récupérer le nbr de joueurs
    choixNbrJoueurs = 0;

    for (int i=0;i<4;++i)
        directions[i] = RIEN;

    pen[0]=QPen(Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pen[1]=QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pen[2]=QPen(Qt::cyan, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pen[3]=QPen(Qt::yellow, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

    numFenetre = -2;

    bonus = false;

    startTimer(30);
}


MainWidget::~MainWidget()
{
    // delete musique;
}

// Fonction appele toutes les 30 millisecondes par le timer.
void MainWidget::timerEvent ( QTimerEvent * event )
{
    if (numFenetre==2)
    {
        if(jeux->suiteGame(directions)==false)
            numFenetre++;
    }
    update();
}

void MainWidget::paintEvent (QPaintEvent * event)
{
    QPainter painter(this);

    if (numFenetre == -2)
    {
        painter.drawPixmap(0,0, fondEcran1);
        painter.drawText(420,580, QString ("Appuyer sur tab  pour continuer"));
    }

    if (numFenetre == -1)
    {
        FenetreChoixJoueurs(painter);
    }
    else if (numFenetre == 0)
    {
        FentreTouches(painter);
    }
    else if (numFenetre == 1)
    {
        jeux = new Game::Game(choixNbrJoueurs, bonus);
        numFenetre += 1;
    }
    else if (numFenetre == 2)
    {
        FenetreJeu(painter);
    }
    else if (numFenetre == 3)
    {
        FenetreScore(painter);
    }
}

void MainWidget::FenetreChoixJoueurs(QPainter &painter)
{
    painter.drawPixmap(0,0,fondEcran3);
    QFont sansFont("",25);
    QFont sansFont2("",15);
    painter.setFont(sansFont);
    painter.drawText(33,500, QString ("Nombre voulu de joueurs  : 2 - 3 - 4"));
    painter.setFont(sansFont2);
    painter.drawText(120,550, QString ("[appuyer sur 2, 3 ou 4 pour choisir]"));
    if (!bonus)
        painter.drawText(450,30, QString("Bonus W?"));
    else
        painter.drawText(450,30, QString("Bonus activé !"));

    if (choixNbrJoueurs!=0)
        numFenetre += 1;
}

void MainWidget::FentreTouches(QPainter &painter)
{
    if (choixNbrJoueurs == 2)
        painter.drawPixmap(0,0,touches2);
    else if (choixNbrJoueurs == 3)
        painter.drawPixmap(0,0,touches3);
    else if (choixNbrJoueurs == 4)
        painter.drawPixmap(0,0,touches4);
    painter.drawText(420,590, QString ("Appuyer sur tab  pour continuer"));
}

void MainWidget::FenetreJeu(QPainter &painter)
{
    painter.drawPixmap(0,0, fondEcran2);
    for (int i=0; i<choixNbrJoueurs; ++i)
    {
        if (!jeux->getPerdu(i))
        {
            Liste* murMoto = jeux->getMurMoto(i);

            murMoto->premier();//se met en début de liste
            int cur1[2];
            murMoto->getElem(cur1);
            int cur2[2];

            int *r,*g,*b;
            r = new int; g = new int; b = new int;
            pen[i].color().getRgb(r,g,b);
            int addcolor=0;

            while(murMoto->getNextElem(cur2))
            {
                QPen instantColor = QPen(QColor(abs(*r-addcolor)%256,*g,*b), 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
                painter.setPen(instantColor);
                painter.drawLine(cur1[0],cur1[1],cur2[0],cur2[1]);

                cur1[0]=cur2[0];
                cur1[1]=cur2[1];
                murMoto->suivant();
                if(addcolor<240){addcolor+=25;}
                else{}
            }
            murMoto->premier();//se met en début de liste
            murMoto->getElem(cur1);
            if (jeux->getDir(i) == DROITE)
                painter.drawPixmap(cur1[0]-20,cur1[1]-4, motoH);
            else if (jeux->getDir(i) == GAUCHE)
                painter.drawPixmap(cur1[0],cur1[1]-4, motoH);
            else if (jeux->getDir(i) == HAUT)
                painter.drawPixmap(cur1[0]-4,cur1[1], motoV);
            else if (jeux->getDir(i) == BAS)
                painter.drawPixmap(cur1[0]-4,cur1[1]-20, motoV);
        }
    }
}

void MainWidget::FenetreScore(QPainter &painter)
{
    painter.drawPixmap(0,0, fondEcran4);
    QFont sansFont("",18);
    QFont sansFont1("",10);
    painter.setFont(sansFont);
    int gagnant=jeux->getMotoGagnante();
    if(gagnant==0) painter.drawText(150,460, QString("PERSONNE N'A GAGNE..."));
    else painter.drawText(150,460,QString ("LE JOUEUR %1 A GAGNE").arg(gagnant));
    for (int i = 0; i<choixNbrJoueurs; ++i)
    {
        painter.drawText(110,75*i+160, QString ("Le score de la moto %1 est : %2").arg(i+1).arg(jeux->getScore(i)));
    }
    painter.setFont(sansFont1);
    painter.drawText(300,500, QString ("Appuyer sur tab  pour continuer"));
}

void MainWidget::keyPressEvent(QKeyEvent* event)
{
    /* CODE DE LA GESTION DU CLAVIER */

    switch(event->key())
    {
    case Qt::Key_Escape:
        close();
        break;

    case Qt::Key_W:
        if (numFenetre == -1)
        {
            if (bonus==false) bonus = true;
            else bonus = false;
        }
        break;

    case Qt::Key_2:
        if(numFenetre == -1)
            choixNbrJoueurs=2;
        break;
    case Qt::Key_3:
        if(numFenetre == -1)
            choixNbrJoueurs=3;
        break;
    case Qt::Key_4:
        if(numFenetre == -1)
            choixNbrJoueurs=4;
        break;

    case Qt::Key_Tab:
        if (numFenetre == 3)
            numFenetre-=1;
        else if (numFenetre == -2 || numFenetre == 0)
            numFenetre+=1;
        break;

        //------commandes joueur 1------
    case Qt::Key_D:
        if(numFenetre == 2)
            directions[0]=DROITE;
        break;
    case Qt::Key_S:
        if(numFenetre == 2)
            directions[0]=BAS;
        break;
    case Qt::Key_Q:
        if(numFenetre == 2)
            directions[0]=GAUCHE;
        break;
    case Qt::Key_Z:
        if(numFenetre == 2)
            directions[0]=HAUT;
        break;
        //------commandes joueur 2------
    case Qt::Key_Right:
        if(numFenetre == 2)
            directions[1]=DROITE;
        break;
    case Qt::Key_Down:
        if(numFenetre == 2)
            directions[1]=BAS;
        break;
    case Qt::Key_Left:
        if(numFenetre == 2)
            directions[1]=GAUCHE;
        break;
    case Qt::Key_Up:
        if(numFenetre == 2)
            directions[1]=HAUT;
        break;
        //------commandes joueur 3------
    case Qt::Key_J:
        if(numFenetre == 2)
            directions[2]=DROITE;
        break;
    case Qt::Key_H:
        if(numFenetre == 2)
            directions[2]=BAS;
        break;
    case Qt::Key_G:
        if(numFenetre == 2)
            directions[2]=GAUCHE;
        break;
    case Qt::Key_Y:
        if(numFenetre == 2)
            directions[2]=HAUT;
        break;
        //------commandes joueur 4------
    case Qt::Key_M:
        if(numFenetre == 2)
            directions[3]=DROITE;
        break;
    case Qt::Key_L:
        if(numFenetre == 2)
            directions[3]=BAS;
        break;
    case Qt::Key_K:
        if(numFenetre == 2)
            directions[3]=GAUCHE;
        break;
    case Qt::Key_O:
        if(numFenetre == 2)
            directions[3]=HAUT;
        break;
    default:
        break;
    }
}

