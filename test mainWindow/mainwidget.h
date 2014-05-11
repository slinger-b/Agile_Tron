#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QPixmap>

#include <QtGui/QWidget>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <liste.h>
#include <QPushButton>
#include <QSound>
#include <QTextEdit>

#include <game.h>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();

    QPixmap fondEcran1;
    QPixmap fondEcran2;
    QPixmap fondEcran3;
    QPixmap fondEcran4;
    QPixmap motoH;
    QPixmap motoV;
    QPixmap touches2;
    QPixmap touches3;
    QPixmap touches4;

    // QSound* musique;

    void paintEvent(QPaintEvent * event);
    QPen pen[4];

    void keyPressEvent(QKeyEvent * event);

    void timerEvent(QTimerEvent * event);

    void FenetreChoixJoueurs(QPainter &painter);
    void FentreTouches(QPainter &painter) ;
    void FenetreJeu(QPainter &painter);
    void FenetreScore(QPainter &painter);

    Game* jeux;

    int choixNbrJoueurs;

    dir directions[4];

    const int static iSize_Height = 600;
    const int static iSize_Width = 600;

    int numFenetre;

    bool bonus;

};

#endif // MAINWIDGET_H

