#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <configure.h>

#include <type_traits>

#include <life/common/Enums.hpp>


DV_LIFE_OPEN_NAMESPACE

template <class T>
struct remove_const_ref {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template <class T>
using remove_const_ref_t = typename remove_const_ref<T>::type;


// controlla che un enum sia stato registrato con Q_ENUM_NS
template <typename T>
static constexpr bool isQEnumSerializable() {

    return std::is_same_v<T, DeviceKey> ||
            std::is_same_v<T, MotorXKind> ||
            std::is_same_v<T, AxisXFeedback> ||
            std::is_same_v<T, IOType>;

}

/* NOTE NIC 08/04/2020: gestione specializzazione template I/O
 * le funzioni isDigitalInputType, isDigitalOutputType, isAnalogInputType
 * sono specializzazioni e non overloading!
 * fare attenzione quindi a inserirle nell'ordine corretto;
 * per chiarimenti, vedere il link:
 * https://en.cppreference.com/w/cpp/language/function_template
 * paragrafo: Function overloads vs function specializations
 */

template <typename T>
constexpr bool isDigitalInputType(MAYBE_UNUSED T type) {
    return false;
}

template <>
constexpr bool isDigitalInputType<IOType>(MAYBE_UNUSED IOType type) {
    int value = static_cast<int>(type);
    return value >= DIGITAL_INPUT_MASK && value < DIGITAL_OUTPUT_MASK;
}

template <typename T>
constexpr bool isDigitalOutputType(MAYBE_UNUSED T type) {
    return false;
}

template <>
constexpr bool isDigitalOutputType<IOType>(MAYBE_UNUSED IOType type) {
    int value = static_cast<int>(type);
    return value >= DIGITAL_OUTPUT_MASK && value < ANALOG_INPUT_MASK;
}

template <typename T>
constexpr bool isAnalogInputType(MAYBE_UNUSED T type) {
    return false;
}

template <>
constexpr bool isAnalogInputType<IOType>(MAYBE_UNUSED IOType type) {
    int value = static_cast<int>(type);
    return value >= ANALOG_INPUT_MASK;
}

DV_LIFE_CLOSE_NAMESPACE

#endif // TRAITS_HPP
