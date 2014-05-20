#include <QtTest/QtTest>

class TestQString: public QObject
{
        Q_OBJECT

private slots:
        void toUpper_data();
        void toUpper();
};

void TestQString::toUpper_data()
{
        QTest::addColumn<QString>("string");
        QTest::addColumn<QString>("result");

        QTest::newRow("tout en minuscules") << "hello" << "HELLO";
        QTest::newRow("minuscules et majuscules") << "Hello" << "HELLO";
        QTest::newRow("tout en majuscule") << "HELLO" << "HELLO";
}

void TestQString::toUpper()
{
        QFETCH(QString, string);
        QFETCH(QString, result);

        QCOMPARE(string.toUpper(), result);
}

QTEST_MAIN(TestQString)
#include "testqstring.moc"

