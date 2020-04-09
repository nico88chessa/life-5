#ifndef ENUMS_HPP
#define ENUMS_HPP

#include <configure.h>

#include <QMetaType>

#include <life/common/Constants.hpp>


DV_LIFE_OPEN_NAMESPACE

enum class DeviceKey : int {
    NONE = ENUM_INVALID,
    GALIL_CN,
    GALIL_PLC
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
    DIGITAL_INPUT,
    DIGITAL_OUTPUT,
    ANALOG_INPUT,
    ANALOG_OUTPUT,
    PROVA
};

/**
 * @brief The IOType enum
 * Questi enum descrivono i diversi tipi di input;
 * Attenzione agli input generici; questi tipi di input sono utilizzati per gestire sensori
 * (quindi solo input) non noti a priori.
 * Gli enum sono suddivisi in categorie (vedere Constants.hpp)
 * gli input sono considerati Generici se hanno un valore intero >= a GENERIC_***_INPUT;
 * quindi, suddividendo quelli digitali da quelli analogici, si ha:
 * INGRESSI GENERICI DIGITALI [GENERIC_DIGITAL_INPUT, 255]
 * INGRESSI GENERICI ANALOGICI [GENERIC_ANALOG_INPUT = 512, 767]
 */
enum class IOType : IOScopedType {
    NONE = ENUM_INVALID,                      // not valid IO -1
    POWER = DIGITAL_INPUT_MASK,               // digital input [0, 255]
    CYCLE,                                    // digital input
    EMERGENCY_MUSHROOM,                       // digital input
    DOOR_OPEN,                                // digital input
    MAINTENANCE,                              // digital input
    WATER_ALARM,                              // digital input
    MARK_IN_PROGRESS,                         // digital input
    SCANNER_READY,                            // digital input
    SCANNER_ERROR,                            // digital input
    DISTANCE_SENSOR_FAULT,                    // digital input
    DEPRESSURE_SENSOR_FAULT,                  // digital input
    PRESSURE_1_SENSOR_FAULT,                  // digital input
    PRESSURE_2_SENSOR_FAULT,                  // digital input
    GENERIC_DIGITAL_INPUT,                    // generic digital input [GENERIC_DIGITAL_INPUT, 255]
    LASER_POWER = DIGITAL_OUTPUT_MASK,        // digital output [256, 511]
    COMPRESSED_AIR_1,                         // digital output
    COMPRESSED_AIR_2,                         // digital output
    SUCTION,                                  // digital output
    POWER_SCAN,                               // digital output
    START_SCAN,                               // digital output
    STOP_SCAN,                                // digital output
    GREEN_LIGHT,                              // digital output
    YELLOW_LIGHT,                             // digital output
    RED_LIGHT,                                // digital output
    GENERIC_ANALOG_INPUT = ANALOG_INPUT_MASK  // generic analog input [512, 767]
};

static constexpr int MAX_NUMBER_GENERIC_DIGITAL_INPUT =
        static_cast<int>(DIGITAL_OUTPUT_MASK) - static_cast<int>(IOType::GENERIC_DIGITAL_INPUT);

static constexpr int MAX_NUMBER_GENERIC_ANALOG_INPUT = ANALOG_OUTPUT_MASK - ANALOG_INPUT_MASK;

/**
  * definisco le variabili gestibili da qt
  */

Q_NAMESPACE

Q_ENUM_NS(DeviceKey)
Q_ENUM_NS(MotorXKind)
Q_ENUM_NS(AxisXFeedback)
Q_ENUM_NS(IOType)


DV_LIFE_CLOSE_NAMESPACE

#endif // ENUMS_HPP
