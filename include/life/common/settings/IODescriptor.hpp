#ifndef IODESCRIPTOR_HPP
#define IODESCRIPTOR_HPP

#include <configure.h>

#include <life/common/Enums.hpp>
#include <life/common/data/io/DigitalInput.hpp>
#include <life/common/data/io/DigitalOutput.hpp>
#include <life/common/data/io/AnalogInput.hpp>


DV_LIFE_OPEN_NAMESPACE

class DigitalInputDescr : public DigitalInput {
public:
    using Ptr = DigitalInputDescr*;
    using ConstPtr = const DigitalInputDescr*;

private:
    bool mandatory;

public:

    DigitalInputDescr() :
        DigitalInputDescr("", DeviceKey::NONE, DIGITAL_INPUT_CHANNEL_NONE,
                          false, false, false, IOType::NONE,
                          false) { };

    /* NOTE NIC 08/04/2020: move-constructor non definito, copy-constructor si
     * in qeusto caso il move constructor ricade nel copy-constructor, come definito
     * al link: https://en.cppreference.com/w/cpp/language/move_constructor
     * paragrafo notes ("If only the copy constructor is provided, all argument
     * categories select it (as long as it takes a reference to const, since rvalues
     * can bind to const references), which makes copying the fallback for moving,
     * when moving is unavailable.
     */

    DigitalInputDescr(const DigitalInput& d) :
        DigitalInputDescr(d.getName(), d.getDevice(), d.getChannel(),
                          d.isInvertLogic(), d.isAlarm(), d.isAlarmInverted(), d.getElementType(),
                          false) { }

    DigitalInputDescr(
            QString name, DeviceKey device, int channel, bool invertLogic,
            bool alarm, bool alarmInverted, IOType elementType,
            bool mandatory = false) :
        DigitalInput(
            name, device, channel,
            invertLogic, alarm, alarmInverted, elementType),
        mandatory(mandatory) { }

    void setMandatory(bool value) { mandatory = value; }
    inline bool isMandatory() const { return mandatory; };

};



class DigitalOutputDescr : public DigitalOutput {
public:
    using Ptr = DigitalOutputDescr*;
    using ConstPtr = const DigitalOutputDescr*;

private:
    bool mandatory;

public:
    DigitalOutputDescr() :
        DigitalOutputDescr("", DeviceKey::NONE, DIGITAL_OUTPUT_CHANNEL_NONE,
                          false, false, IOType::NONE,
                          false) { };

    DigitalOutputDescr(const DigitalOutput& d) :
        DigitalOutputDescr(d.getName(), d.getDevice(), d.getChannel(),
                           d.isInvertLogic(), d.isAlarm(), d.getElementType(),
                           false) { }

    DigitalOutputDescr(
            QString name, DeviceKey device, int channel,
            bool invertLogic, bool alarm, IOType elementType,
            bool mandatory = false) :
        DigitalOutput(
            name, device, channel,
            invertLogic, alarm, elementType),
        mandatory(mandatory) { }

    void setMandatory(bool value) { mandatory = value; }
    inline bool isMandatory() const { return mandatory; };

};



class AnalogInputDescr : public AnalogInput {
public:
    using Ptr = AnalogInputDescr*;
    using ConstPtr = const AnalogInputDescr*;

private:
    bool mandatory;

public:
    AnalogInputDescr() :
        AnalogInputDescr("", DeviceKey::NONE, ANALOG_INPUT_CHANNEL_NONE,
                         false, ANALAG_GAIN_DEFAULT, 0,
                         "", std::numeric_limits<analogReal>::min(),
                       std::numeric_limits<analogReal>::max(), ANALAG_HYSTERESIS_DEFAULT,
                       IOType::GENERIC_ANALOG_INPUT,
                       false) { };

    AnalogInputDescr(const AnalogInput& a) :
        AnalogInputDescr(a.getName(), a.getDevice(), a.getChannel(),
                         a.isAlarm(), a.getGain(), a.getOffset(),
                         a.getUnit(), a.getLowerLimit(),
                         a.getUpperLimit(), a.getHysteresys(),
                         a.getElementType(),
                         false) { }

    AnalogInputDescr(
            QString name, DeviceKey device, int channel,
            bool alarm, analogReal gain, analogReal offset,
            QString unit, analogReal lowerLimit,
            analogReal upperLimit, analogReal hysteresys,
            IOType elementType = IOType::GENERIC_ANALOG_INPUT,
            bool mandatory = false) :
        AnalogInput(
            name, device, channel,
            alarm, gain, offset,
            unit, lowerLimit,
            upperLimit, hysteresys,
            elementType),
        mandatory(mandatory) { }

    void setMandatory(bool value) { mandatory = value; }
    inline bool isMandatory() const { return mandatory; };

};

DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dvlife::DigitalInputDescr)
Q_DECLARE_METATYPE(dvlife::DigitalOutputDescr)
Q_DECLARE_METATYPE(dvlife::AnalogInputDescr)

#endif // IODESCRIPTOR_HPP

