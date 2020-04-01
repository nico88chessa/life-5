#ifndef TRAITS_HPP
#define TRAITS_HPP

#include <configure.h>

#include <type_traits>


DV_LIFE_OPEN_NAMESPACE

template <class T>
struct remove_const_ref {
    using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template <class T>
using remove_const_ref_t = typename remove_const_ref<T>::type;



//template <typename T, typename = void>
//struct isEnumDescriptable {
//    static constexpr bool value = false;
//};

//template <typename T>
//inline constexpr bool isEnumDescriptable_v = isEnumDescriptable<T>::value;


//enum class SettingsGroup; // forward declaration
//template <typename T>
//struct isEnumDescriptable<T, std::enable_if_t<std::is_same_v<T, SettingsGroup>> > {
//    static constexpr bool value = true;
//};

DV_LIFE_CLOSE_NAMESPACE

#endif // TRAITS_HPP
