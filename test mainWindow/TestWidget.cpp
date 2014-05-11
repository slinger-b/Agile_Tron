#include <QtTest>
#include <QtCore>
#include <QtGui>
#include "mainwidget.h"

class TestWidget: public QObject
{
    Q_OBJECT
private slots:
    void initialisation();
 private:
    int choixNbrJoueurs;
    int numFenetre;
    dir directions[4];
    bool bonus;
};


void TestWidget::initialisation()
{
    MainWidget m;
    numFenetre = -2;
    choixNbrJoueurs=0;
    bonus = false;
    //startTimer(30);

    QCOMPARE( choixNbrJoueurs, m.choixNbrJoueurs );
    QCOMPARE( numFenetre, m.numFenetre );
    QCOMPARE( bonus, m.bonus );

    QTest::keyClick( &m, Qt::Key_Tab );
    numFenetre+=1;
    QCOMPARE( numFenetre, m.numFenetre );

    QTest::keyClick( &m, Qt::Key_W );
    bonus = true;
    QCOMPARE( bonus, m.bonus );

    choixNbrJoueurs=3;
    QTest::keyClick( &m, Qt::Key_3 );
    QCOMPARE( choixNbrJoueurs, m.choixNbrJoueurs );

    QCOMPARE( numFenetre, m.numFenetre );
    QTest::keyClick( &m, Qt::Key_Tab );
    numFenetre+=1;
    QCOMPARE( numFenetre, m.numFenetre );

}

QTEST_MAIN(TestWidget)
#include "TestWidget.moc"


