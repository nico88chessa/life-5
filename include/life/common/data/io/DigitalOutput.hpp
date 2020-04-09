#ifndef DIGITALOUTPUT_HPP
#define DIGITALOUTPUT_HPP

#include <QString>

#include <configure.h>

#include <life/common/Types.hpp>
#include <life/common/Constants.hpp>
#include <life/common/Enums.hpp>


DV_LIFE_OPEN_NAMESPACE

class DigitalOutput {
public:
    using Ptr = DigitalOutput*;
    using ConstPtr = const DigitalOutput*;

private:
    QString name;
    DeviceKey device;
    int channel;
    bool invertLogic;
    bool alarm;
    IOType elementType;

public:
    DigitalOutput() :
        DigitalOutput("", DeviceKey::NONE, DIGITAL_OUTPUT_CHANNEL_NONE, false, false, IOType::NONE) { }

    DigitalOutput(QString name, DeviceKey device, int channel,
                  bool invertLogic, bool alarm, IOType elementType) :
              name(name), device(device), channel(channel),
              invertLogic(invertLogic), alarm(alarm), elementType(elementType) { }

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

    void setElementType(const IOType& value) { elementType = value; }
    inline IOType getElementType() const { return elementType; }

    friend inline bool operator==(const DigitalOutput& l, const DigitalOutput& r);
    friend inline bool operator!=(const DigitalOutput& l, const DigitalOutput& r);
//    friend inline bool operator<(const DigitalOutput& l, const DigitalOutput& r);

};

bool operator==(const DigitalOutput& l, const DigitalOutput& r) {
    return l.elementType == r.elementType;
}

bool operator!=(const DigitalOutput& l, const DigitalOutput& r) {
    return !(l == r);
}

//bool operator<(const DigitalOutput& l, const DigitalOutput& r) {
//    return (l.device < r.device) || (
//                (l.device == r.device) && (l.channel < r.channel));
//}


DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dvlife::DigitalOutput)

#endif // DIGITALOUTPUT_HPP
