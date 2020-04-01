#include "Utils.hpp"


using namespace dvlife;

/* NOTE Nic 30/03/2020
 * template specialization della funzione dichiarate nell'header
 */
template <>
QLatin1String utils::EnumUtils::getEnumName(SettingsGroup cat) noexcept {

    using namespace dvlife;

    switch (cat) {
    case SettingsGroup::GUI: return QLatin1String("Gui");
    case SettingsGroup::AXIS_X: return QLatin1String("Axis X");
    case SettingsGroup::AXIS_Z: return QLatin1String("Axis Z");
    case SettingsGroup::CYLINDER: return QLatin1String("Cylinder");
    }
    return QLatin1String("");
}

template <>
QLatin1String utils::EnumUtils::getEnumName(MotorXKind cat) noexcept {

    using namespace dvlife;

    switch (cat) {
    case MotorXKind::LINEAR: return QLatin1String("Linear");
    case MotorXKind::NO_LINEAR: return QLatin1String("No Linear");
    }
    return QLatin1String("");
}

template <>
QLatin1String utils::EnumUtils::getEnumName(AxisXFeedback cat) noexcept {

    using namespace dvlife;

    switch (cat) {
    case AxisXFeedback::LINEAR_ENCODER: return QLatin1String("Linear encoder");
    case AxisXFeedback::MOTOR_RESOLVER: return QLatin1String("Motor resolver");
    }
    return QLatin1String("");
}
