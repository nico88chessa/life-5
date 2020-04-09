#include <QtTest/QtTest>

#include <QObject>
#include <QVariant>

#include <life/common/settings/SettingsManager.hpp>
#include <life/common/settings/descriptors/Descriptors.hpp>
#include <life/common/settings/MachineParameter.hpp>
#include <life/common/QtHelper.hpp>
#include <life/core/io/data/DigitalInputValue.hpp>

#include <life/common/logging/Logger.hpp>


constexpr bool testCE1(const dvlife::MachineParameter p) {
    return std::is_same_v<int, decltype (p.defaultValue)>;
}

constexpr bool testCE2(const dvlife::MachineParameter p, dvlife::Option o) {
    return p.hasOption(o);
}

class SettingsTest: public QObject {
    Q_OBJECT

private slots:
    void typeCheckInt_data();
    void typeCheckInt();

    void checkMachineParameterConstexpr_data();
    void checkMachineParameterConstexpr();

    void testSettingsManager();

private:
    void testMachineParameters();

};

Q_DECLARE_METATYPE(dv::life::MachineParameter)

class Prova {

};

void SettingsTest::testSettingsManager() {

    using namespace dvlife;

    auto&& settings = SettingsManager::instance();
    for (int i=0; i<100; ++i) {
        QString name = QString("PROVA_AN_%1)").arg(i);
        bool res = settings.addAnalogInput(AnalogInput(
                                               name, DeviceKey::GALIL_CN, 0,
                                               false, 1.0, 0.0, "mm", 0, 10, 2));
        QVERIFY2(res == true,
                qPrintable(QString("Impossibile inserire l'indice %1").arg(i)));
    }

    for (int i=0; i<20; ++i) {
        QString name = QString("PROVA_AN_%1)").arg(i);
        bool res = settings.removeAnalogInput(AnalogInput(
                                               name, DeviceKey::GALIL_CN, 0,
                                               false, 1.0, 0.0, "mm", 0, 10, 2));
        QVERIFY(res == true);
    }

    for (int i=0; i<30; ++i) {
        QString name = QString("PROVA_AN_20%1").arg(i);
        bool res = settings.addAnalogInput(AnalogInput(
                                               name, DeviceKey::GALIL_CN, 0,
                                               false, 1.0, 0.0, "mm", 0, 10, 2));
        QVERIFY(res == true);
    }

    for (int i=0; i<100; ++i) {
        QString name = QString("PROVA_DI_%1").arg(i);
        bool res = settings.addDigitalInput(DigitalInput(
                                               name, DeviceKey::GALIL_CN, 0, false,
                                               false, false, IOType::GENERIC_DIGITAL_INPUT));
        QVERIFY2(res == true,
                qPrintable(QString("Impossibile inserire l'indice %1").arg(i)));
    }

    for (int i=0; i<20; ++i) {
        QString name = QString("PROVA_DI_%1").arg(i);
        bool res = settings.removeDigitalInput(DigitalInput(
                                               name, DeviceKey::GALIL_CN, 0, false,
                                               false, false, IOType::GENERIC_DIGITAL_INPUT));
        QVERIFY(res == true);
    }

    for (int i=0; i<30; ++i) {
        QString name = QString("PROVA_DI_2_%1").arg(i);
        bool res = settings.addDigitalInput(DigitalInput(
                                               name, DeviceKey::GALIL_CN, 0, false,
                                               false, false, IOType::GENERIC_DIGITAL_INPUT));
        QVERIFY(res == true);
    }

    QVERIFY(DigitalInputValue() == DigitalInputValue());

    try {

        settings.setParameter(dvlife::AXIS_Z_STEP_PER_MM, 102);
        settings.setParameter(dvlife::AXIS_X_TEST, dvlife::AxisXFeedback::MOTOR_RESOLVER);
        settings.setParameter(dvlife::AXIS_X_TEST, 102);
    }  catch (dvlife::exceptions::SettingsException& ex) {

        traceErr() << ex.what();

    }

//    settings.setParameter(dvlife::AXIS_X_TEST, 102);

    settings.restore();
//    res = settings.addAnalogInput(AnalogInput(
//                                           "PROVA_AN_2", 0, DeviceKey::GALIL_CN,
//                                           false, 1.0, 0.0, "mm", 0, 10, 2));
//    QVERIFY(res == true);
//    res = settings.addAnalogInput(AnalogInput(
//                                           "PROVA_AN_3", 0, DeviceKey::GALIL_CN,
//                                           false, 1.0, 0.0, "mm", 0, 10, 2));
//    QVERIFY(res == true);
//    res = settings.addAnalogInput(AnalogInput(
//                                           "PROVA_AN_1", 0, DeviceKey::GALIL_CN,
//                                           false, 1.0, 0.0, "mm", 0, 10, 2));
//    QVERIFY(res == false);
//    res = settings.removeAnalogInput(AnalogInput(
//                                         "PROVA_AN_1", 0, DeviceKey::GALIL_CN,
//                                         false, 1.0, 0.0, "mm", 0, 10, 2));
//    QVERIFY(res == true);
//    res = settings.removeAnalogInput(AnalogInput(
//                                         "PROVA_AN_2", 0, DeviceKey::GALIL_CN,
//                                         false, 1.0, 0.0, "mm", 0, 10, 2));
//    QVERIFY(res == true);
//    res = settings.addAnalogInput(AnalogInput(
//                                           "PROVA_AN_4", 0, DeviceKey::GALIL_CN,
//                                           false, 1.0, 0.0, "mm", 0, 10, 2));
//    QVERIFY(res == true);


}

void SettingsTest::testMachineParameters() {

    using namespace dvlife;

    dvlife::qthelper::registerMetatypes();
    dvlife::qthelper::registerMetatypesStreamOperator();

    MAYBE_UNUSED auto temp = dv::life::AXIS_X_DESCR;

    QString linear = QVariant::fromValue(dv::life::MotorXKind::LINEAR).toString();

    MAYBE_UNUSED bool res = testCE1(dvlife::AXIS_X_HOMING_SPEED_MMS);
//    constexpr dvlife::MachineParameter t = dvlife::AXIS_X_TEST;
//    if constexpr (t.hasOption(dvlife::Option::IS_IP_ADDRESS)) {

//    std::array __temp = { };
//    __temp.cbegin();


//    int testSize = dvlife::AXIS_X_DESCR.size();
    constexpr dvlife::MachineParameter mp2_1 = dvlife::AXIS_X_TEST;
    constexpr dvlife::MachineParameter mp2_2 = dvlife::AXIS_X_FEEDBACK;
//    auto t = dvlife::__AXIS_X_DESCR__str;
//    float test = s.getParameter<float>(AXIS_X_MAX_POS_MM);

    if constexpr (mp2_1.hasOption(dvlife::Option::IS_IP_ADDRESS)) {
        res = true;
    }

    if constexpr (mp2_2.hasOption(dvlife::Option::IS_IP_ADDRESS)) {
        res = true;
    }

    if constexpr (mp2_2.isType<int>()) {
        res = true;
    }

    if constexpr (testCE2(mp2_2, dvlife::Option::IS_IP_ADDRESS)) {
        res = true;
    } else {
        res = false;
    }

    Prova prova;
    if constexpr(isMachineParameterInt(prova)) {
        traceDebug() << "Sono intero";
    } else if constexpr(isMachineParameterDouble(prova)) {
        traceDebug() << "Sono double";
    } else if constexpr(isMachineParameterMotorXKind(prova)) {
        traceDebug() << "Sono MotorXKind";
    } else if constexpr(isMachineParameterXFeedback(prova)) {
        traceDebug() << "Sono Feedback";
    } else {
        traceDebug() << "Nulla";
    }

//    res = std::is_same_v<dvlife::MachineParameter2<1>, dvlife::MachineParameter2<2>>;

    QString test1 = dvlife::utils::EnumUtils::enumToName(dvlife::AxisXFeedback::LINEAR_ENCODER);
    QString test2 = QVariant::fromValue(dv::life::AxisXFeedback::LINEAR_ENCODER).toString();
//    QString test3 = QMetaEnum::valueToKey(dv::life::AxisXFeedback);
//    QMetaEnum::fromType<Q_LINEAR_ENCODER>().valueToKey(AxisXFeedback::LINEAR_ENCODER);
//    QString test2 = QVariant(dv::life::AxisXFeedback::LINEAR_ENCODER).toString();

//    QVERIFY(test1.compare(test2)==0);
    MAYBE_UNUSED auto&& type = QMetaType::type(qPrintable(QString("AxisXFeedback::%1").arg("LINEAR_ENCODER")));
//    QVERIFY(QVariant(dvlife::AxisXFeedback::LINEAR_ENCODER).toString())
    MAYBE_UNUSED auto&& provaOpt = dvlife::__AXIS_X_FEEDBACK__OPTIONS__.begin();
    MAYBE_UNUSED auto&& provaOpt2 = dvlife::__AXIS_X_STEP_PER_MM__OPTIONS__.begin();
    std::initializer_list<dv::life::Option> provaOpt3 = { };
    MAYBE_UNUSED auto&& provaOpt4 = provaOpt3.begin();
    MAYBE_UNUSED auto&& provaOpt3Size = provaOpt3.size();
    dvlife::SettingsManager::instance();


}



void SettingsTest::typeCheckInt_data() {

    QTest::addColumn<dvlife::MachineParameter>("type");
    QTest::addColumn<bool>("result");

    QTest::newRow("AXIS_X_STEP_PER_MM") << dvlife::AXIS_X_STEP_PER_MM << true;
    QTest::newRow("AXIS_X_MIN_POS_MM") << dvlife::AXIS_X_MIN_POS_MM << true;
    QTest::newRow("AXIS_X_MAX_POS_MM") << dvlife::AXIS_X_MAX_POS_MM << true;
    QTest::newRow("AXIS_X_SAFETY_POS_MM") << dvlife::AXIS_X_SAFETY_POS_MM << true;
    QTest::newRow("AXIS_X_BASE_OFFSET_MM") << dvlife::AXIS_X_BASE_OFFSET_MM << true;
    QTest::newRow("AXIS_X_MANUAL_SPEED_MMS") << dvlife::AXIS_X_MANUAL_SPEED_MMS << true;
    QTest::newRow("AXIS_X_MANUAL_ACC_MMS2") << dvlife::AXIS_X_MANUAL_ACC_MMS2 << true;
    QTest::newRow("AXIS_X_MANUAL_DEC_MMS2") << dvlife::AXIS_X_MANUAL_DEC_MMS2 << true;
    QTest::newRow("AXIS_X_OPERATIVE_SPEED_MMS") << dvlife::AXIS_X_OPERATIVE_SPEED_MMS << true;
    QTest::newRow("AXIS_X_OPERATIVE_ACC_MMS2") << dvlife::AXIS_X_OPERATIVE_ACC_MMS2 << true;
    QTest::newRow("AXIS_X_OPERATIVE_DEC_MMS2") << dvlife::AXIS_X_OPERATIVE_DEC_MMS2 << true;
    QTest::newRow("AXIS_X_HOMING_SPEED_MMS") << dvlife::AXIS_X_HOMING_SPEED_MMS << true;
    QTest::newRow("AXIS_X_HOMING_ACC_MMS2") << dvlife::AXIS_X_HOMING_ACC_MMS2 << true;
    QTest::newRow("AXIS_X_HOMING_DEC_MMS2") << dvlife::AXIS_X_HOMING_DEC_MMS2 << true;
    QTest::newRow("AXIS_X_STEP_SPEED_MMS") << dvlife::AXIS_X_STEP_SPEED_MMS << true;
    QTest::newRow("AXIS_X_STEP_ACC_MMS2") << dvlife::AXIS_X_STEP_ACC_MMS2 << true;
    QTest::newRow("AXIS_X_STEP_DEC_MMS2") << dvlife::AXIS_X_STEP_DEC_MMS2 << true;
    QTest::newRow("AXIS_X_FEEDBACK") << dvlife::AXIS_X_FEEDBACK << false;
    QTest::newRow("AXIS_X_TEST") << dvlife::AXIS_X_TEST << false;

    QTest::newRow("AXIS_Z_STEP_PER_MM") << dvlife::AXIS_Z_STEP_PER_MM << true;
    QTest::newRow("AXIS_Z_MIN_POS_MM") << dvlife::AXIS_Z_MIN_POS_MM << true;
    QTest::newRow("AXIS_Z_MAX_POS_MM") << dvlife::AXIS_Z_MAX_POS_MM << true;
    QTest::newRow("AXIS_Z_SAFETY_POS_MM") << dvlife::AXIS_Z_SAFETY_POS_MM << true;
    QTest::newRow("AXIS_Z_MANUAL_SPEED_MMS") << dvlife::AXIS_Z_MANUAL_SPEED_MMS << true;
    QTest::newRow("AXIS_Z_MANUAL_ACC_MMS2") << dvlife::AXIS_Z_MANUAL_ACC_MMS2 << true;
    QTest::newRow("AXIS_Z_MANUAL_DEC_MMS2") << dvlife::AXIS_Z_MANUAL_DEC_MMS2 << true;
    QTest::newRow("AXIS_Z_OPERATIVE_SPEED_MMS") << dvlife::AXIS_Z_OPERATIVE_SPEED_MMS << true;
    QTest::newRow("AXIS_Z_OPERATIVE_ACC_MMS2") << dvlife::AXIS_Z_OPERATIVE_ACC_MMS2 << true;
    QTest::newRow("AXIS_Z_OPERATIVE_DEC_MMS2") << dvlife::AXIS_Z_OPERATIVE_DEC_MMS2 << true;
    QTest::newRow("AXIS_Z_HOMING_SPEED_MMS") << dvlife::AXIS_Z_HOMING_SPEED_MMS << true;
    QTest::newRow("AXIS_Z_HOMING_ACC_MMS2") << dvlife::AXIS_Z_HOMING_ACC_MMS2 << true;
    QTest::newRow("AXIS_Z_HOMING_DEC_MMS2") << dvlife::AXIS_Z_HOMING_DEC_MMS2 << true;

}

void SettingsTest::typeCheckInt() {

    dvlife::qthelper::registerMetatypes();
    dvlife::qthelper::registerMetatypesStreamOperator();

    QFETCH(dvlife::MachineParameter, type);
    QFETCH(bool, result);

    QCOMPARE(type.isType<int>(), result);

}

void SettingsTest::checkMachineParameterConstexpr_data() {

    QTest::addColumn<dvlife::MachineParameter>("mp");
    QTest::addColumn<bool>("result");

    QTest::newRow("AXIS_X_STEP_PER_MM") << dvlife::AXIS_X_STEP_PER_MM << true;
    QTest::newRow("AXIS_X_MIN_POS_MM") << dvlife::AXIS_X_MIN_POS_MM << true;
    QTest::newRow("AXIS_X_MAX_POS_MM") << dvlife::AXIS_X_MAX_POS_MM << true;
    QTest::newRow("AXIS_X_SAFETY_POS_MM") << dvlife::AXIS_X_SAFETY_POS_MM << true;
    QTest::newRow("AXIS_X_BASE_OFFSET_MM") << dvlife::AXIS_X_BASE_OFFSET_MM << true;
    QTest::newRow("AXIS_X_MANUAL_SPEED_MMS") << dvlife::AXIS_X_MANUAL_SPEED_MMS << true;
    QTest::newRow("AXIS_X_MANUAL_ACC_MMS2") << dvlife::AXIS_X_MANUAL_ACC_MMS2 << true;
    QTest::newRow("AXIS_X_MANUAL_DEC_MMS2") << dvlife::AXIS_X_MANUAL_DEC_MMS2 << true;
    QTest::newRow("AXIS_X_OPERATIVE_SPEED_MMS") << dvlife::AXIS_X_OPERATIVE_SPEED_MMS << true;
    QTest::newRow("AXIS_X_OPERATIVE_ACC_MMS2") << dvlife::AXIS_X_OPERATIVE_ACC_MMS2 << true;
    QTest::newRow("AXIS_X_OPERATIVE_DEC_MMS2") << dvlife::AXIS_X_OPERATIVE_DEC_MMS2 << true;
    QTest::newRow("AXIS_X_HOMING_SPEED_MMS") << dvlife::AXIS_X_HOMING_SPEED_MMS << true;
    QTest::newRow("AXIS_X_HOMING_ACC_MMS2") << dvlife::AXIS_X_HOMING_ACC_MMS2 << true;
    QTest::newRow("AXIS_X_HOMING_DEC_MMS2") << dvlife::AXIS_X_HOMING_DEC_MMS2 << true;
    QTest::newRow("AXIS_X_STEP_SPEED_MMS") << dvlife::AXIS_X_STEP_SPEED_MMS << true;
    QTest::newRow("AXIS_X_STEP_ACC_MMS2") << dvlife::AXIS_X_STEP_ACC_MMS2 << true;
    QTest::newRow("AXIS_X_STEP_DEC_MMS2") << dvlife::AXIS_X_STEP_DEC_MMS2 << true;
    QTest::newRow("AXIS_X_FEEDBACK") << dvlife::AXIS_X_FEEDBACK << true;
    QTest::newRow("AXIS_X_TEST") << dvlife::AXIS_X_TEST << true;

    QTest::newRow("AXIS_Z_STEP_PER_MM") << dvlife::AXIS_Z_STEP_PER_MM << true;
    QTest::newRow("AXIS_Z_MIN_POS_MM") << dvlife::AXIS_Z_MIN_POS_MM << true;
    QTest::newRow("AXIS_Z_MAX_POS_MM") << dvlife::AXIS_Z_MAX_POS_MM << true;
    QTest::newRow("AXIS_Z_SAFETY_POS_MM") << dvlife::AXIS_Z_SAFETY_POS_MM << true;
    QTest::newRow("AXIS_Z_MANUAL_SPEED_MMS") << dvlife::AXIS_Z_MANUAL_SPEED_MMS << true;
    QTest::newRow("AXIS_Z_MANUAL_ACC_MMS2") << dvlife::AXIS_Z_MANUAL_ACC_MMS2 << true;
    QTest::newRow("AXIS_Z_MANUAL_DEC_MMS2") << dvlife::AXIS_Z_MANUAL_DEC_MMS2 << true;
    QTest::newRow("AXIS_Z_OPERATIVE_SPEED_MMS") << dvlife::AXIS_Z_OPERATIVE_SPEED_MMS << true;
    QTest::newRow("AXIS_Z_OPERATIVE_ACC_MMS2") << dvlife::AXIS_Z_OPERATIVE_ACC_MMS2 << true;
    QTest::newRow("AXIS_Z_OPERATIVE_DEC_MMS2") << dvlife::AXIS_Z_OPERATIVE_DEC_MMS2 << true;
    QTest::newRow("AXIS_Z_HOMING_SPEED_MMS") << dvlife::AXIS_Z_HOMING_SPEED_MMS << true;
    QTest::newRow("AXIS_Z_HOMING_ACC_MMS2") << dvlife::AXIS_Z_HOMING_ACC_MMS2 << true;
    QTest::newRow("AXIS_Z_HOMING_DEC_MMS2") << dvlife::AXIS_Z_HOMING_DEC_MMS2 << true;

}

void SettingsTest::checkMachineParameterConstexpr() {

    dvlife::qthelper::registerMetatypes();
    dvlife::qthelper::registerMetatypesStreamOperator();

    QFETCH(dvlife::MachineParameter, mp);
    QFETCH(bool, result);

    // dai test
    QCOMPARE(dvlife::isMachineParameter<decltype(mp)>::value, result);

    QCOMPARE(dvlife::isMachineParameter<int>::value, false);
    QCOMPARE(dvlife::isMachineParameter<float>::value, false);
    QCOMPARE(dvlife::isMachineParameter<double>::value, false);

}

QTEST_MAIN(SettingsTest)
#include "SettingsTest.moc"
