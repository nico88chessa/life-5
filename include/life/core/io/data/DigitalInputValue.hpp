#ifndef DIGITALINPUTVALUE_HPP
#define DIGITALINPUTVALUE_HPP

#include <life/common/data/io/DigitalInput.hpp>


DV_LIFE_OPEN_NAMESPACE

class DigitalInputValue : public DigitalInput {
public:
    using Ptr = DigitalInputValue*;
    using ConstPtr = const DigitalInputValue*;

private:
    bool value;

public:
    DigitalInputValue() :
        DigitalInputValue(DigitalInput()) { }

    DigitalInputValue(const DigitalInput& d) :
        DigitalInputValue(
            d.getName(),
            d.getDevice(),
            d.getChannel(),
            d.isInvertLogic(),
            d.isAlarm(),
            d.isAlarmInverted(),
            d.getElementType()) { }

    DigitalInputValue(QString name, DeviceKey device, int channel,
                 bool invertLogic, bool alarm, bool alarmInverted, IOType elementType) :
        DigitalInput(name, device, channel, invertLogic, alarm, alarmInverted, elementType),
        value(invertLogic ? true : false) { }

    bool getValue() const { return value; }
    void setValue(bool value) { this->value = value; }

};

DV_LIFE_CLOSE_NAMESPACE

#endif // DIGITALINPUTVALUE_HPP
