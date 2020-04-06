#ifndef TYPES_HPP
#define TYPES_HPP

#include <configure.h>

#include <type_traits>

#include <QMetaType>


DV_LIFE_OPEN_NAMESPACE

static constexpr int ENUM_INVALID = -1;

enum class DeviceKey : int {
    NONE = ENUM_INVALID,
};

/**
 * @brief The MotorXKind enum
 * Indica se il mototore dell'asse X e' lineare o meno;
 * se lineare, bisogna fare il wake and shake
 * LINEAR: motore lineare
 * NO_LINEAR: motore non lineare
 */
enum class MotorXKind : int {
    NONE = ENUM_INVALID,
    LINEAR,
    NO_LINEAR
};

/**
 * @brief The AxisXFeedback enum
 * Indica il tipo di retroazione utilizzato per l'asse X;
 * LINEAR_ENCODER: riga ottica
 * MOTOR_RESOLVER: resolver del motore
 * Questa distinzione potrebbe essere necessaria in caso di homing
 * dell'asse X. In caso linear potrebbe essere necessario la ricerca
 * dello 0 encoder, in caso di motor resolver potrebbe essere sufficiente
 * uscire dal sigaro
 */
enum class AxisXFeedback : int {
    NONE = ENUM_INVALID,
    LINEAR_ENCODER,
    MOTOR_RESOLVER
};


enum class SettingsGroupType : int {
    NONE = ENUM_INVALID,
    GUI,
    AXIS_X,
    AXIS_Z,
    CYLINDER,
    PROVA
};


/**
  * definisco le variabili gestibili da qt
  */

Q_NAMESPACE

Q_ENUM_NS(DeviceKey)
Q_ENUM_NS(MotorXKind)
Q_ENUM_NS(AxisXFeedback)

template <typename T>
static constexpr bool isQEnumSerializable() {

    return std::is_same_v<T, DeviceKey> ||
            std::is_same_v<T, MotorXKind> ||
            std::is_same_v<T, AxisXFeedback>;

}

DV_LIFE_CLOSE_NAMESPACE

#endif // TYPES_HPP
