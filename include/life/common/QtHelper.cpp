#include "QtHelper.hpp"

#include <QDataStream>
#include <QVariant>
#include <QByteArray>
#include <QMetaEnum>

#include <life/common/logging/Logger.hpp>
#include <life/common/Types.hpp>
#include <life/common/Traits.hpp>
#include <life/common/Utils.hpp>


using namespace dvlife;

void qthelper::registerMetatypes() {

    // mi assicuro che questa funzione venga chiamata una volta sola
    static bool called = false;
    if (called)
        return;
    called = true;

    int qmlTypeId = qRegisterMetaType<dv::life::DeviceKey>("dv::life::DeviceKey");
    traceDebug() << "dv::life::DeviceKey QML TypeId: " << qmlTypeId;
    qmlTypeId = qRegisterMetaType<DeviceKey>("DeviceKey");
    traceDebug() << "DeviceKey QML TypeId: " << qmlTypeId;
    qmlTypeId = qRegisterMetaType<dv::life::MotorXKind>("dv::life::MotorXKind");
    traceDebug() << "dv::life::MotorXKind QML TypeId: " << qmlTypeId;
    qmlTypeId = qRegisterMetaType<MotorXKind>("MotorXKind");
    traceDebug() << "MotorXKind QML TypeId: " << qmlTypeId;
    qmlTypeId = qRegisterMetaType<dv::life::AxisXFeedback>("dv::life::AxisXFeedback");
    traceDebug() << "dv::life::AxisXFeedback QML TypeId: " << qmlTypeId;
    qmlTypeId = qRegisterMetaType<AxisXFeedback>("AxisXFeedback");
    traceDebug() << "AxisXFeedback QML TypeId: " << qmlTypeId;

}

void qthelper::registerMetatypesStreamOperator() {

    // mi assicuro che questa funzione venga chiamata una volta sola
    static bool called = false;
    if (called)
        return;
    called = true;

    qRegisterMetaTypeStreamOperators<dv::life::DeviceKey>("dv::life::DeviceKey");
    qRegisterMetaTypeStreamOperators<DeviceKey>("DeviceKey");
    qRegisterMetaTypeStreamOperators<dv::life::MotorXKind>("dv::life::MotorXKind");
    qRegisterMetaTypeStreamOperators<MotorXKind>("MotorXKind");
    qRegisterMetaTypeStreamOperators<dv::life::AxisXFeedback>("dv::life::AxisXFeedback");
    qRegisterMetaTypeStreamOperators<AxisXFeedback>("AxisXFeedback");

}


template <typename T>
static inline QDataStream& serializeEnumWrapper(QDataStream &out, const T& obj) {

    static_assert(isQEnumSerializable<T>(), "Il tipo T deve essere registrato con Q_ENUM_NS");

    /* NOTE NIC 05/04/2020
     * non passo per la class Utils e nemmeno per QString / QStringLiteral;
     * queste classi infatti codificano la stringa in UTF-8 o Latin1, per cui i byte dei caratteri
     * sono codificati; preferisco usare i raw byte per avere nel file di configurazione un
     * formato leggibile
     */
    QByteArray bytes = QMetaEnum::fromType<T>().valueToKey(static_cast<int>(obj));
    bytes.insert(0, '|');
    bytes.append('|');
    out << bytes;
    return out;

}

template <typename T>
static inline QDataStream& deserializeEnumWrapper(QDataStream &in, T& obj) {

    static_assert(isQEnumSerializable<T>(), "Il tipo T deve essere registrato con Q_ENUM_NS");

    QByteArray data;
    in >> data;
    data.replace('|', QByteArray()); // rimuovo le barre verticali
    bool isOk = false;
    obj = static_cast<T>(ENUM_INVALID);
    int enumValue = QMetaEnum::fromType<T>().keyToValue(data, &isOk);
    if (isOk)
        obj = static_cast<T>(enumValue);
    return in;

}


QDataStream& operator<<(QDataStream& out, const DeviceKey& obj) {
    return serializeEnumWrapper(out, obj);
}

QDataStream& operator>>(QDataStream& in, DeviceKey& obj) {
    return deserializeEnumWrapper(in, obj);
}

QDataStream& operator<<(QDataStream& out, const MotorXKind& obj) {
    return serializeEnumWrapper(out, obj);
}

QDataStream& operator>>(QDataStream& in, MotorXKind& obj) {
    return deserializeEnumWrapper(in, obj);
}

QDataStream& operator<<(QDataStream& out, const AxisXFeedback& obj) {
    return serializeEnumWrapper(out, obj);
}

QDataStream& operator>>(QDataStream& in, AxisXFeedback& obj) {
    return deserializeEnumWrapper(in, obj);
}

QDataStream& operator<<(QDataStream& out, const IOType& obj) {
    return serializeEnumWrapper(out, obj);
}

QDataStream& operator>>(QDataStream& in, IOType& obj) {
    return deserializeEnumWrapper(in, obj);
}
