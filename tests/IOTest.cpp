#include <QtTest/QtTest>

#include <QObject>
#include <QVariant>

#include <life/common/Enums.hpp>
#include <life/common/QtHelper.hpp>


class IOTest: public QObject {
    Q_OBJECT

private slots:
    void testEnum_data();
    void testEnum();

};

void IOTest::testEnum_data() {

    dvlife::qthelper::registerMetatypes();
    dvlife::qthelper::registerMetatypesStreamOperator();

    QTest::addColumn<dvlife::IOType>("ioType");
    QTest::addColumn<int>("value");

    QTest::newRow("NONE") << dvlife::IOType::NONE << -1;
    QTest::newRow("POWER") << dvlife::IOType::POWER << 0;
    QTest::newRow("CYCLE") << dvlife::IOType::CYCLE << 1;
    QTest::newRow("EMERGENCY_MUSHROOM") << dvlife::IOType::EMERGENCY_MUSHROOM << 2;
    QTest::newRow("DOOR_OPEN") << dvlife::IOType::DOOR_OPEN << 3;
    QTest::newRow("MAINTENANCE") << dvlife::IOType::MAINTENANCE << 4;
    QTest::newRow("WATER_ALARM") << dvlife::IOType::WATER_ALARM << 5;
    QTest::newRow("MARK_IN_PROGRESS") << dvlife::IOType::MARK_IN_PROGRESS << 6;
    QTest::newRow("SCANNER_READY") << dvlife::IOType::SCANNER_READY << 7;
    QTest::newRow("SCANNER_ERROR") << dvlife::IOType::SCANNER_ERROR << 8;
    QTest::newRow("DISTANCE_SENSOR_FAULT") << dvlife::IOType::DISTANCE_SENSOR_FAULT << 9;
    QTest::newRow("DEPRESSURE_SENSOR_FAULT") << dvlife::IOType::DEPRESSURE_SENSOR_FAULT << 10;
    QTest::newRow("PRESSURE_1_SENSOR_FAULT") << dvlife::IOType::PRESSURE_1_SENSOR_FAULT << 11;
    QTest::newRow("PRESSURE_2_SENSOR_FAULT") << dvlife::IOType::PRESSURE_2_SENSOR_FAULT << 12;
    QTest::newRow("GENERIC_DIGITAL_INPUT") << dvlife::IOType::GENERIC_DIGITAL_INPUT << 13;
    QTest::newRow("LASER_POWER") << dvlife::IOType::LASER_POWER << 256;
    QTest::newRow("COMPRESSED_AIR_1") << dvlife::IOType::COMPRESSED_AIR_1 << 257;
    QTest::newRow("COMPRESSED_AIR_2") << dvlife::IOType::COMPRESSED_AIR_2 << 258;
    QTest::newRow("SUCTION") << dvlife::IOType::SUCTION << 259;
    QTest::newRow("POWER_SCAN") << dvlife::IOType::POWER_SCAN << 260;
    QTest::newRow("START_SCAN") << dvlife::IOType::START_SCAN << 261;
    QTest::newRow("STOP_SCAN") << dvlife::IOType::STOP_SCAN << 262;
    QTest::newRow("YELLOW_LIGHT") << dvlife::IOType::YELLOW_LIGHT << 263;
    QTest::newRow("RED_LIGHT") << dvlife::IOType::RED_LIGHT << 264;
    QTest::newRow("GREEN_LIGHT") << dvlife::IOType::GREEN_LIGHT << 265;
    QTest::newRow("GENERIC_ANALOG_INPUT") << dvlife::IOType::GENERIC_ANALOG_INPUT << 512;

}

void IOTest::testEnum() {

    QFETCH(dvlife::IOType, ioType);
    QFETCH(int, value);

    QCOMPARE(static_cast<int>(ioType), value);

}

QTEST_MAIN(IOTest)
#include "IOTest.moc"
