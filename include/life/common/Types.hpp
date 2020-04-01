#ifndef TYPES_HPP
#define TYPES_HPP

#include <configure.h>

#include <QMetaType>


DV_LIFE_OPEN_NAMESPACE

enum class DeviceKey : int {
    NONE = -1,
};

enum class SettingsGroup : int {
    GUI = 0,
    AXIS_X,
    AXIS_Z,
    CYLINDER
};

/**
 * @brief The MotorXKind enum
 * Indica se il mototore dell'asse X e' lineare o meno;
 * se lineare, bisogna fare il wake and shake
 * LINEAR: motore lineare
 * NO_LINEAR: motore non lineare
 */
enum class MotorXKind : int {
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
    LINEAR_ENCODER,
    MOTOR_RESOLVER
};


DV_LIFE_CLOSE_NAMESPACE


/**
  * definisco le variabili gestibili da qt
  */

DV_LIFE_OPEN_NAMESPACE

Q_NAMESPACE

DV_LIFE_CLOSE_NAMESPACE


/* WARNING NIC 31/03/2020
 * lo inserisco qui, in modo da separare gli enum
 * dalle direttive per Qt
 * la dichiarazione degli enums presenti nel file .ipp
 * funziona perche' e' definito qui sopra la direttiva
 * Q_NAMESPACE
 * in qualche modo, grazie a questa riga il moc fa il parse
 * anche di questo file; se non ci fosse ci sarebbero problemi
 */
#include "TypesQDecl.ipp"


#endif // TYPES_HPP
