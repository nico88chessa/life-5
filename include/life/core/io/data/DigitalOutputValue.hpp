#ifndef DIGITALOUTPUTVALUE_HPP
#define DIGITALOUTPUTVALUE_HPP

#include <life/common/data/io/DigitalOutput.hpp>


DV_LIFE_OPEN_NAMESPACE

class DigitalOutputValue : public DigitalOutput {
public:
    using Ptr = DigitalOutputValue*;
    using ConstPtr = const DigitalOutputValue*;

private:
    bool value;

public:
    DigitalOutputValue() :
        DigitalOutputValue(DigitalOutput()) { }

    DigitalOutputValue(const DigitalOutput& d) :
        DigitalOutputValue(
            d.getName(),
            d.getDevice(),
            d.getChannel(),
            d.isInvertLogic(),
            d.isAlarm(),
            d.getElementType()) { }

    DigitalOutputValue(QString name, DeviceKey device, int channel,
                  bool invertLogic, bool alarm, IOType elementType) :
        DigitalOutput(name, device, channel, invertLogic, alarm, elementType),
        value(invertLogic ? true : false) { } // value sempre disattivo

    bool getValue() const { return value; }
    void setValue(bool value) { this->value = value; }

};

DV_LIFE_CLOSE_NAMESPACE

#endif // DIGITALOUTPUTVALUE_HPP
