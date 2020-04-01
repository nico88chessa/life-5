#ifndef MACHINEPARAMETER_HPP
#define MACHINEPARAMETER_HPP

#include <configure.h>

#include <string>
#include <variant>

#include <life/common/Traits.hpp>
#include <life/common/Types.hpp>


DV_LIFE_OPEN_NAMESPACE

enum class Option : int {
    IS_IP_ADDRESS = 0
};

using MachineParameterType = std::variant<int, double, MotorXKind, AxisXFeedback>;

/*!
 * \brief La struttura MachineParameter rappresenta un campo del file di configurazione.
 *
 */
struct MachineParameter {
//    const char* group;
    SettingsGroup group;
    const char* key;
    const char* label;
    MachineParameterType defaultValue;
    const std::initializer_list<Option> options;
};


#ifndef DECL_MACHINE_PARAMETER
#define DECL_MACHINE_PARAMETER(name, group, key, label, defaultValue, options) \
    static constexpr MachineParameter name = { \
        group, \
        key, \
        label, \
        defaultValue, \
        options \
    };
#endif

#ifndef DECL_MACHINE_PARAMETER_NOOPT
#define DECL_MACHINE_PARAMETER_NOOPT(name, group, key, label, defaultValue) \
    DECL_MACHINE_PARAMETER(name, group, key, label, defaultValue, { })
#endif

#define TYPE_OF_MP(p) \
    static_assert(isMachineParameter<remove_const_ref_t<decltype(p)>>::value, "Il tipo di parametro deve essere MachineParameter"); \
    remove_const_ref_t<decltype(std::get<p.defaultValue.index()>(p.defaultValue))>


// qui verifico se un parametro e' di tipo MachineParameter o no
template <typename T, typename = void>
struct isMachineParameter {
    static constexpr bool value = false;
};

template <typename T>
struct isMachineParameter<T, std::enable_if_t<std::is_same<T, MachineParameter>::value> > {
    static constexpr bool value = true;
};


// qui verifico, tramite variabile (che deve essere constexpr!!!), il tipo di variabile definito
// all'interno del variant (grazie C++17 posso usare i variant a compile time!)
template <typename T, typename V, std::enable_if_t<!isMachineParameter<T>::value, int> = 0>
constexpr bool isMachineParameterType(MAYBE_UNUSED T mp) {
    return false;
}

template <typename T, typename V, std::enable_if_t<isMachineParameter<T>::value, int> = 0>
constexpr bool isMachineParameterType(T mp) {
//    using valueType = dvlife::remove_const_ref_t<decltype(mp.defaultValue)>;
//    valueType v = mp.defaultValue;
//    int index = mp.defaultValue.index();
//    auto baseType = std::get<0>(v);
//    return std::is_same_v<
//            V,
//            dvlife::remove_const_ref_t<decltype(std::get<mp.defaultValue.index()>(mp.defaultValue))> >;
    return std::holds_alternative<V>(mp.defaultValue);
}

template <typename T>
constexpr bool isMachineParameterInt(T mp) {
    return isMachineParameterType<T, int>(mp);
}

template <typename T>
constexpr bool isMachineParameterDouble(T mp) {
    return isMachineParameterType<T, double>(mp);
}

template <typename T>
constexpr bool isMachineParameterMotorXKind(T mp) {
    return isMachineParameterType<T, MotorXKind>(mp);
}

template <typename T>
constexpr bool isMachineParameterXFeedback(T mp) {
    return isMachineParameterType<T, AxisXFeedback>(mp);
}

DV_LIFE_CLOSE_NAMESPACE

#endif // MACHINEPARAMETER_HPP
