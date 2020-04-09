#ifndef DIGITALINPUT_HPP
#define DIGITALINPUT_HPP

#include <QString>

#include <configure.h>

#include <life/common/Types.hpp>
#include <life/common/Constants.hpp>
#include <life/common/Enums.hpp>


DV_LIFE_OPEN_NAMESPACE

class DigitalInput {
public:
    using Ptr = DigitalInput*;
    using ConstPtr = const DigitalInput*;

private:
    QString name;
    DeviceKey device;
    int channel;
    bool invertLogic;
    bool alarm;
    bool alarmInverted;
    IOType elementType;

public:
    /* costruttore di copia implicitamente definito dato che non e' dichiarato;
     * il costruttore di copia da una copia var/var
     * move constructor predefinito
     */
    DigitalInput() :
        DigitalInput("", DeviceKey::NONE, DIGITAL_INPUT_CHANNEL_NONE, false, false, false, IOType::NONE) { }

    DigitalInput(QString name, DeviceKey device, int channel,
                  bool invertLogic, bool alarm, bool alarmInverted, IOType elementType) :
        name(name), device(device), channel(channel), invertLogic(invertLogic),
        alarm(alarm), alarmInverted(alarmInverted), elementType(elementType) { }

    void setName(const QString& value) { name = value; }
    inline QString getName() const { return name; }

    void setChannel(int value) { channel = value; }
    inline int getChannel() const { return channel; }

    void setInvertLogic(bool value) { invertLogic = value; }
    inline bool isInvertLogic() const { return invertLogic; }

    void setDevice(const DeviceKey& value) { device = value; }
    inline DeviceKey getDevice() const { return device; }

    void setAlarm(bool value) { alarm = value; }
    inline bool isAlarm() const { return alarm; }

    void setAlarmInverted(bool value) { alarmInverted = value; }
    inline bool isAlarmInverted() const { return alarmInverted; }

    void setElementType(const IOType& value) { elementType = value; }
    inline IOType getElementType() const { return elementType; }

    friend inline bool operator==(const DigitalInput& l, const DigitalInput& r);
    friend inline bool operator!=(const DigitalInput& l, const DigitalInput& r);
//    friend inline bool operator<(const DigitalInput& l, const DigitalInput& r);

};

/* NOTE NIC 08/04/2020: uguaglianza Digital Input
 * due digital input sono uguali se:
 * 1. caso IOType != GENERIC_DIGITAL_INPUT: se gli IOType sono uguali
 * 2. caso IOType == GENERIC_DIGITAL_INPUT: se hanno anche lo stesso nome
 */
bool operator==(const DigitalInput& l, const DigitalInput& r) {
    if (l.elementType != r.elementType)
        return false;
    else {
        if (l.elementType == IOType::GENERIC_DIGITAL_INPUT)
            return l.getName().compare(r.getName(), Qt::CaseInsensitive) == 0;
        else
            return true;
    }
}

bool operator!=(const DigitalInput& l, const DigitalInput& r) {
    return !(l == r);
}

//bool operator<(const DigitalInput& l, const DigitalInput& r) {
//    return (l.device < r.device) || (
//                (l.device == r.device) && (l.channel < r.channel));
//}


DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dvlife::DigitalInput)

#endif // DIGITALINPUT_HPP
