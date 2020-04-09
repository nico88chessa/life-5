#ifndef ANALOGINPUT_HPP
#define ANALOGINPUT_HPP

#include <configure.h>

#include <QString>

#include <life/common/Constants.hpp>
#include <life/common/Enums.hpp>


DV_LIFE_OPEN_NAMESPACE

class AnalogInput {
public:
    using Ptr = AnalogInput*;
    using ConstPtr = const AnalogInput*;

private:
    QString name;
    DeviceKey device;
    int channel;
    bool alarm;
    analogReal gain;
    analogReal offset;
    QString unit;
    analogReal lowerLimit;
    analogReal upperLimit;
    analogReal hysteresys;
    IOType elementType;

public:
    AnalogInput() :
        AnalogInput("", DeviceKey::NONE, ANALOG_INPUT_CHANNEL_NONE,
                      false, ANALAG_GAIN_DEFAULT, 0,
                      "", std::numeric_limits<analogReal>::min(),
                    std::numeric_limits<analogReal>::max(), ANALAG_HYSTERESIS_DEFAULT) { }
    AnalogInput(
            QString name, DeviceKey device, int channel,
            bool alarm, analogReal gain, analogReal offset,
            QString unit, analogReal lowerLimit,
            analogReal upperLimit, analogReal hysteresys,
            IOType elementType = IOType::GENERIC_ANALOG_INPUT) :
        name(name), device(device), channel(channel),
        alarm(alarm), gain(gain), offset(offset),
        unit(unit), lowerLimit(lowerLimit),
        upperLimit(upperLimit), hysteresys(hysteresys), elementType(elementType) { }

    void setName(const QString& value) { name = value; }
    QString getName() const { return name; }

    void setChannel(int value) { channel = value; }
    int getChannel() const { return channel; }

    void setDevice(const DeviceKey& value) { device = value; }
    DeviceKey getDevice() const { return device; }

    void setAlarm(bool value) { alarm = value; }
    bool isAlarm() const { return alarm; }

    void setGain(const analogReal& value) { gain = value; }
    analogReal getGain() const { return gain; }

    void setOffset(const analogReal& value) { offset = value; }
    analogReal getOffset() const { return offset; }

    void setUnit(const QString& value) { unit = value; }
    QString getUnit() const { return unit; }

    void setLowerLimit(const analogReal& value) { lowerLimit = value; }
    analogReal getLowerLimit() const { return lowerLimit; }

    void setUpperLimit(const analogReal& value) { upperLimit = value; }
    analogReal getUpperLimit() const { return upperLimit; }

    void setHysteresys(const analogReal& value) { hysteresys = value; }
    analogReal getHysteresys() const { return hysteresys; }

    void setElementType(const IOType& value) { elementType = value; }
    IOType getElementType() const { return elementType; }

    friend inline bool operator==(const AnalogInput& l, const AnalogInput& r);
    friend inline bool operator!=(const AnalogInput& l, const AnalogInput& r);
//    friend inline bool operator<(const AnalogInput& l, const AnalogInput& r);

};


/* NOTE NIC 08/04/2020: uguaglianza Digital Input
 * due digital input sono uguali se:
 * 1. caso IOType != GENERIC_ANALOG_INPUT: se gli IOType sono uguali
 * 2. caso IOType == GENERIC_ANALOG_INPUT: se hanno anche lo stesso nome
 */
bool operator==(const AnalogInput& l, const AnalogInput& r) {
    if (l.elementType != r.elementType)
        return false;
    else {
        if (l.elementType == IOType::GENERIC_ANALOG_INPUT)
            return l.getName().compare(r.getName(), Qt::CaseInsensitive) == 0;
        else
            return true;
    }
}

bool operator!=(const AnalogInput& l, const AnalogInput& r) {
    return !(l == r);
}

//bool operator<(const AnalogInput& l, const AnalogInput& r) {
//    return (l.device < r.device) || (
//                (l.device == r.device) && (l.channel < r.channel));
//}

DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dvlife::AnalogInput)

#endif // ANALOGINPUT_HPP
