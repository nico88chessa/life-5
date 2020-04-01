#ifndef SETTINGDESCRIPTOR_HPP
#define SETTINGDESCRIPTOR_HPP

#include <configure.h>

#include <vector>

#include <life/common/settings/MachineParameter.hpp>


DV_LIFE_OPEN_NAMESPACE

class SettingDescriptor {
private:
    std::initializer_list<MachineParameter> parameters;

public:
    constexpr SettingDescriptor(const std::initializer_list<MachineParameter> l) :
        parameters(l) { }

    constexpr std::initializer_list<MachineParameter> getParameters() const {
        return parameters;
    }

};

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGDESCRIPTOR_HPP
