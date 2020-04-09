#include "Utils.hpp"

#include <QVariant>
#include <QMetaEnum>

#include <life/common/Types.hpp>
#include <life/common/Enums.hpp>
#include <life/common/Traits.hpp>
#include <life/common/settings/MachineParameter.hpp>


/* NOTE Nic 02/04/2020
 * Sfrutto il fatto di registrare gli enum attraverso la direttiva Q_ENUM_NS
 * presente nel file Types.
 * in questo modo il moc genera una struttura dati agli enum che, fra le altre cose,
 * permette di convertire un enum in QString;
 * la stringa relativa all'enum e' uguale a enum; esempio:
 * AXIS_X -> stringa = "AXIS_X"
 */

using namespace dvlife;

/* NOTE Nic 30/03/2020
 * template specialization della funzione dichiarate nell'header
 */
template <>
QString utils::EnumUtils::enumToName(SettingsGroupType cat) noexcept {

    // uso questo modo perche' SettingsGroupType non e' dichiarato come Q_ENUM_NS in Types.hpp
    using namespace dvlife;

    switch (cat) {
    case SettingsGroupType::GUI: return QLatin1String("GUI");
    case SettingsGroupType::AXIS_X: return QLatin1String("AXIS_X");
    case SettingsGroupType::AXIS_Z: return QLatin1String("AXIS_Z");
    case SettingsGroupType::CYLINDER: return QLatin1String("CYLINDER");
    case SettingsGroupType::DIGITAL_INPUT: return QLatin1String("DIGITAL_INPUT");
    case SettingsGroupType::DIGITAL_OUTPUT: return QLatin1String("DIGITAL_OUTPUT");
    case SettingsGroupType::ANALOG_INPUT: return QLatin1String("ANALOG_INPUT");
    case SettingsGroupType::ANALOG_OUTPUT: return QLatin1String("ANALOG_OUTPUT");
    default: return QLatin1String("NONE");
    }

}

template <>
SettingsGroupType utils::EnumUtils::nameToEnum(QLatin1String str) noexcept {

    // uso questo modo perche' SettingsGroupType non e' dichiarato come Q_ENUM_NS in Types.hpp
    if (str == QLatin1String("GUI")) return SettingsGroupType::GUI;
    else if (str == QLatin1String("AXIS_X")) return SettingsGroupType::AXIS_X;
    else if (str == QLatin1String("AXIS_Z")) return SettingsGroupType::AXIS_Z;
    else if (str == QLatin1String("CYLINDER")) return SettingsGroupType::CYLINDER;
    else if (str == QLatin1String("DIGITAL_INPUT")) return SettingsGroupType::DIGITAL_INPUT;
    else if (str == QLatin1String("DIGITAL_OUTPUT")) return SettingsGroupType::DIGITAL_OUTPUT;
    else if (str == QLatin1String("ANALOG_INPUT")) return SettingsGroupType::ANALOG_INPUT;
    else if (str == QLatin1String("ANALOG_OUTPUT")) return SettingsGroupType::ANALOG_OUTPUT;

    return SettingsGroupType::NONE;
}

template <>
QString utils::EnumUtils::enumToName(DeviceKey cat) noexcept {

    // inutile, pero' e' un reminder se in futuro si decide di rivedere questa parte di codice
    static_assert(isQEnumSerializable<DeviceKey>(),
            "L'enum DeviceKey deve essere registrato con la direttiva Q_ENUM_NS");

    switch (cat) {
    case DeviceKey::GALIL_CN:
    case DeviceKey::GALIL_PLC: return QVariant::fromValue(cat).toString();
    default: return QLatin1String("NONE");
    }

}

template <>
DeviceKey utils::EnumUtils::nameToEnum(QLatin1String str) noexcept {

    static_assert(isQEnumSerializable<DeviceKey>(),
            "L'enum DeviceKey deve essere registrato con la direttiva Q_ENUM_NS");

    QMetaEnum metaType = QMetaEnum::fromType<DeviceKey>();
    bool isOk = false;
    DeviceKey value = static_cast<DeviceKey>(metaType.keyToValue(str.cbegin(), &isOk));
    if (isOk)
        return value;
    return DeviceKey::NONE;

}

template <>
QString utils::EnumUtils::enumToName(MotorXKind cat) noexcept {

    static_assert(isQEnumSerializable<MotorXKind>(),
            "L'enum MotorXKind deve essere registrato con la direttiva Q_ENUM_NS");

    switch (cat) {
    case MotorXKind::LINEAR:
    case MotorXKind::NO_LINEAR: return QVariant::fromValue(cat).toString();
    default: return QLatin1String("NONE");
    }

}

template <>
MotorXKind utils::EnumUtils::nameToEnum(QLatin1String str) noexcept {

    static_assert(isQEnumSerializable<MotorXKind>(),
            "L'enum MotorXKind deve essere registrato con la direttiva Q_ENUM_NS");

    QMetaEnum metaType = QMetaEnum::fromType<MotorXKind>();
    bool isOk = false;
    MotorXKind value = static_cast<MotorXKind>(metaType.keyToValue(str.cbegin(), &isOk));
    if (isOk)
        return value;
    return MotorXKind::NONE;

}

template <>
QString utils::EnumUtils::enumToName(AxisXFeedback cat) noexcept {

    static_assert(isQEnumSerializable<AxisXFeedback>(),
            "L'enum AxisXFeedback deve essere registrato con la direttiva Q_ENUM_NS");

    switch (cat) {
    case AxisXFeedback::LINEAR_ENCODER:
    case AxisXFeedback::MOTOR_RESOLVER: return QVariant::fromValue(cat).toString();
    default: return QLatin1String("NONE");
    }

}

template <>
AxisXFeedback utils::EnumUtils::nameToEnum(QLatin1String str) noexcept {

    static_assert(isQEnumSerializable<AxisXFeedback>(),
            "L'enum AxisXFeedback deve essere registrato con la direttiva Q_ENUM_NS");

    QMetaEnum metaType = QMetaEnum::fromType<AxisXFeedback>();
    bool isOk = false;
    AxisXFeedback value = static_cast<AxisXFeedback>(metaType.keyToValue(str.cbegin(), &isOk));
    if (isOk)
        return value;
    return AxisXFeedback::NONE;

}

template <>
QString utils::EnumUtils::enumToName(IOType cat) noexcept {

    static_assert(isQEnumSerializable<IOType>(),
            "L'enum DeviceKey deve essere registrato con la direttiva Q_ENUM_NS");

    switch (cat) {
    case IOType::POWER:
    case IOType::CYCLE:
    case IOType::EMERGENCY_MUSHROOM:
    case IOType::DOOR_OPEN:
    case IOType::MAINTENANCE:
    case IOType::WATER_ALARM:
    case IOType::MARK_IN_PROGRESS:
    case IOType::SCANNER_READY:
    case IOType::SCANNER_ERROR:
    case IOType::DISTANCE_SENSOR_FAULT:
    case IOType::DEPRESSURE_SENSOR_FAULT:
    case IOType::PRESSURE_1_SENSOR_FAULT:
    case IOType::PRESSURE_2_SENSOR_FAULT:
    case IOType::GENERIC_DIGITAL_INPUT:
    case IOType::LASER_POWER:
    case IOType::COMPRESSED_AIR_1:
    case IOType::COMPRESSED_AIR_2:
    case IOType::SUCTION:
    case IOType::POWER_SCAN:
    case IOType::START_SCAN:
    case IOType::STOP_SCAN:
    case IOType::YELLOW_LIGHT:
    case IOType::RED_LIGHT:
    case IOType::GREEN_LIGHT:
    case IOType::GENERIC_ANALOG_INPUT: return QVariant::fromValue(cat).toString();
    default: return QLatin1String("NONE");
    }

}

template <>
IOType utils::EnumUtils::nameToEnum(QLatin1String str) noexcept {

    static_assert(isQEnumSerializable<IOType>(),
            "L'enum DeviceKey deve essere registrato con la direttiva Q_ENUM_NS");

    QMetaEnum metaType = QMetaEnum::fromType<IOType>();
    bool isOk = false;
    IOType value = static_cast<IOType>(metaType.keyToValue(str.cbegin(), &isOk));
    if (isOk)
        return value;
    return IOType::NONE;

}

bool utils::IOUtils::isGenericDigitalInput(IOType type) {

    IOScopedType value = static_cast<IOScopedType>(type);
    return value >= static_cast<IOScopedType>(IOType::GENERIC_DIGITAL_INPUT) &&
            value < DIGITAL_OUTPUT_MASK;

}

bool utils::IOUtils::isGenericAnalogInput(IOType type) {

    IOScopedType value = static_cast<IOScopedType>(type);
    return value >= static_cast<IOScopedType>(IOType::GENERIC_ANALOG_INPUT);

}
