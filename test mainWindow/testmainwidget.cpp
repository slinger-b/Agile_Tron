#include <QtTest>
#include <QtCore>
#include <QtGui>
Q_DECLARE_METATYPE(QDate)

class testDateEdit: public QObject
{
    Q_OBJECT
private slots:
    void testChanges();
    void testValidator_data();
    void testValidator();
};

void testDateEdit::testChanges()
{
    // 11 March 1967
    QDate date( 1967, 3, 11 );
    QDateEdit dateEdit( date );

    // up-arrow should increase day by one
    QTest::keyClick( &dateEdit, Qt::Key_Up );
    QCOMPARE( dateEdit.date(), date.addDays(1) );

    // we click twice on the "reduce" arrow at the bottom RH corner
    // first we need the widget size to know where to click
    QSize editWidgetSize = dateEdit.size();
    QPoint clickPoint(editWidgetSize.rwidth()-2, editWidgetSize.rheight()-2);
    // issue two clicks
    QTest::mouseClick( &dateEdit, Qt::LeftButton, 0, clickPoint);
    QTest::mouseClick( &dateEdit, Qt::LeftButton, 0, clickPoint);
    // and we should have decreased day by two (one less than original)
    QCOMPARE( dateEdit.date(), date.addDays(-1) );

    QTest::keyClicks( &dateEdit, "25122005" );
    QCOMPARE( dateEdit.date(), QDate( 2005, 12, 25 ) );

    QTest::keyClick( &dateEdit, Qt::Key_Tab, Qt::ShiftModifier );
    QTest::keyClicks( &dateEdit, "08" );
    QCOMPARE( dateEdit.date(), QDate( 2005, 8, 25 ) );
}

void testDateEdit::testValidator_data()
{
    qRegisterMetaType<QDate>("QDate");

    QTest::addColumn<QDate>( "initialDate" );
    QTest::addColumn<QString>( "keyclicks" );
    QTest::addColumn<QDate>( "finalDate" );

    QTest::newRow( "1968/4/12" ) << QDate( 1967, 3, 11 )
                                 << QString( "12041968" )
                                 << QDate( 1968, 4, 12 );

    QTest::newRow( "1967/3/14" ) << QDate( 1967, 3, 11 )
                                 << QString( "140abcdef[" )
                                 << QDate( 1967, 3, 14 );
    // more rows can go in here
}

void testDateEdit::testValidator()
{
    QFETCH( QDate, initialDate );
    QFETCH( QString, keyclicks );
    QFETCH( QDate, finalDate );

    QDateEdit dateEdit( initialDate );
    // this next line is just to start editing
    QTest::keyClick( &dateEdit, Qt::Key_Enter );
    QTest::keyClicks( &dateEdit, keyclicks );
    QCOMPARE( dateEdit.date(), finalDate );
}

QTEST_MAIN(testDateEdit)
#include "testmainwidget.moc"
