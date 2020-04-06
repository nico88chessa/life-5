#ifndef SETTINGDESCRIPTOR_HPP
#define SETTINGDESCRIPTOR_HPP

#include <configure.h>

#include <initializer_list>

#include <life/common/settings/MachineParameter.hpp>


DV_LIFE_OPEN_NAMESPACE

class SettingDescriptor {
private:
    const dv::life::SettingsGroupType gt;
    const bool mandatory;
    const dv::life::MachineParameter* const parameters;
    const int s;

public:
    constexpr SettingDescriptor(
            dv::life::SettingsGroupType _gt,
            bool _mandatory,
            const dv::life::MachineParameter* _parameters, int _size) :
        gt(_gt), mandatory(_mandatory), parameters(_parameters), s(_size) { }

    constexpr dv::life::SettingsGroupType groupType() const {
        return gt;
    }

    constexpr bool isMandatory() const {
        return mandatory;
    }
    constexpr const dv::life::MachineParameter* getParameters() const {
        return parameters;
    }

    constexpr int size() const {
        return s;
    }

    //constexpr dv::life::MachineParameter getParameter(const char* const key) const {
    //
    //    const dv::life::MachineParameter* params = parameters;
    //    bool found = false;
    //
    //    for (int i=0; i<s; ++i) {
    //        const char* keyToSearch = key;
    //        const char* pKey = params[i].key;
    //        bool isCharDifferent = false;
    //
    //        while (*keyToSearch || *pKey)
    //            if (*keyToSearch++ != *pKey++)
    //                isCharDifferent = true;
    //
    //        if (!isCharDifferent)
    //            return params[i];
    //    }
    //
    //    /* NOTE NIC 02/04/2020: throw exception in constant expression
    //     * if (!found) mi serve perche' altrimenti il compilatore mi da problemi in compilazione
    //     * nel caso usassi questa funzione in una constant expression;
    //     * esempio (vedere esempio indexDescr)
    //     * std::array<int, getParameter(SettingsGroupType::AXIS_X)> ciao; <-- KO (anche se dovrebbe essere OK!!)
    //     * std::array<int, getParameter(SettingsGroupType::PROVA)> ciao; <-- KO (giustamente)
    //     */
    //    if (!found)
    //        throw "Parameter not founded";
    //
    //}


};


#ifndef SETTINGS_DESCRIPTOR_BRACED_INIT_LIST
#define SETTINGS_DESCRIPTOR_BRACED_INIT_LIST(...) __VA_ARGS__
#endif

#ifndef DECL_SETTINGS_DESCRIPTOR
#define DECL_SETTINGS_DESCRIPTOR(name, group_type, mandatory, parameters_brace_list) \
    MAYBE_UNUSED static constexpr std::initializer_list<dv::life::MachineParameter> __##name##__DESCRIPTOR_PARAMETERS__ = { SETTINGS_DESCRIPTOR_BRACED_INIT_LIST parameters_brace_list }; \
    MAYBE_UNUSED static constexpr dv::life::SettingDescriptor name = dv::life::SettingDescriptor( \
        group_type, \
        mandatory, \
        __##name##__DESCRIPTOR_PARAMETERS__.begin(), \
        __##name##__DESCRIPTOR_PARAMETERS__.size() \
    );
#endif

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGDESCRIPTOR_HPP
