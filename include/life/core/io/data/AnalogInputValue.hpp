#ifndef ANALOGINPUTVALUE_HPP
#define ANALOGINPUTVALUE_HPP

#include <life/common/data/io/AnalogInput.hpp>


DV_LIFE_OPEN_NAMESPACE

class AnalogInputValue : public AnalogInput {
public:
    using Ptr = AnalogInputValue*;
    using ConstPtr = AnalogInputValue*;

private:
    analogReal value;

public:
    AnalogInputValue() :
        AnalogInputValue(AnalogInput()) { }

    AnalogInputValue(const AnalogInput& a) :
        AnalogInputValue(
            a.getName(),
            a.getDevice(),
            a.getChannel(),
            a.isAlarm(),
            a.getGain(),
            a.getOffset(),
            a.getUnit(),
            a.getLowerLimit(),
            a.getUpperLimit(),
            a.getHysteresys(),
            a.getElementType()) { }

    AnalogInputValue(QString name, DeviceKey device, int channel,
                     bool alarm, analogReal gain, analogReal offset,
                     QString unit, analogReal lowerLimit,
                     analogReal upperLimit, analogReal hysteresys,
                     IOType elementType = IOType::GENERIC_ANALOG_INPUT) :
        AnalogInput(
            name, device, channel,
            alarm, gain, offset,
            unit, lowerLimit,
            upperLimit, hysteresys,
            elementType), value(0) { }

    analogReal getValue() const { return value; }
    void setValue(const analogReal& value) { this->value = value; }

};

DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dvlife::AnalogInputValue)

#endif // ANALOGINPUTVALUE_HPP
