#include <QtTest/QtTest>
#include <QObject>

#include <life/common/settings/SettingsManager.hpp>

class Test1: public QObject {
    Q_OBJECT
private slots:
    void toUpper();

};


void Test1::toUpper() {
    dvlife::SettingsManager::instance();
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}

QTEST_MAIN(Test1)
#include "Test1.moc"
