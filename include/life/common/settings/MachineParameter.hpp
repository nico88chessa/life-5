#ifndef MACHINEPARAMETER_HPP
#define MACHINEPARAMETER_HPP

#include <configure.h>

#include <variant>

#include <life/common/Traits.hpp>
#include <life/common/Types.hpp>


DV_LIFE_OPEN_NAMESPACE

enum class Option : int {
    IS_IP_ADDRESS
};

using MachineParameterType = std::variant<int, double, MotorXKind, AxisXFeedback>;

/*!
 * \brief La struttura MachineParameter rappresenta un campo del file di configurazione.
 */

struct MachineParameter {
    const dvlife::SettingsGroupType group;
    const char* const key;
    const char* const label;
    dvlife::MachineParameterType defaultValue;

    /*
     * MAI FARE UNA COSA DEL GENERE CON LE INITIALIZER_LIST<T> (usarle come attributo di classe)
     *
     * In poche parole, le initializer_list wrappano al loro interno un oggetto del tipo constT[N];
     * il lifetime dell'oggetto viene esteso SSE l'initializer_list viene assegnata ad
     * un'altra initializer_list.
     * es.: https://akrzemi1.wordpress.com/2016/07/07/the-cost-of-stdinitializer_list/
     * In questo caso, quando la std::initializer_list va out of scope (esce dal costruttore),
     * la variabile options contiene un dangling reference alla vecchia initializer list
     *
     * da: https://en.cppreference.com/w/cpp/utility/initializer_list
     * The underlying array is a temporary array of type const T[N], in which each element
     * is copy-initialized (except that narrowing conversions are invalid) from the corresponding
     * element of the original initializer list. THE LIFETIME OF THE UNDERLYING ARRAY IS THE
     * SAME AS ANY OTHER TEMPORARY OBJECT, EXCEPT THAT INITIALIZING AN INITIALIZER_LIST OBJECT
     * FROM THE ARRAY EXTENDS THE LIFETIME OF THE ARRAY EXACTLY LIKE BINDING A REFERENCE TO A
     * TEMPORARY (WITH THE SAME EXCEPTIONS, SUCH AS FOR INITIALIZING A NON-STATIC CLASS MEMBER).
     * THE UNDERLYING ARRAY MAY BE ALLOCATED IN READ-ONLY MEMORY.
     */
    /***** const std::initializer_list<dvlife::Option> options; *****/

    /* meglio usare un puntatore; qui e' compito del programmatore usare correttamente questa
     * struttura dati
     */

    /* puntatore a options.. in attesa di C++20 dove potrebbe essere disponibile un'allocazione
     * di tipo std::array senza dare a priori il numero di elementi
     */
    const dv::life::Option* const options;
    const int size;

    constexpr MachineParameter(): MachineParameter(
                                    SettingsGroupType::NONE, "", "", 0, nullptr, 0) { }

    constexpr MachineParameter(dv::life::SettingsGroupType _group,
                               const char* _key,
                               const char* _label,
                               dv::life::MachineParameterType _defaultValue,
                               const dv::life::Option* _options, int _size) :
        group(_group),
        key(_key),
        label(_label),
        defaultValue(_defaultValue),
        options(_options), size(_size) { }

    template <typename T>
    constexpr bool isType() const {
        return std::holds_alternative<T>(defaultValue);
    }

    constexpr bool hasOption(Option opt) const {
        if (options==nullptr)
            return false;
        for (int i=0; i<size; ++i)
            if (opt == options[i])
                return true;
        return false;
//        for (auto&& i: options)
//            if (i == opt)
//                return true;
//        return false;
    }
};


#ifndef MACHINE_PARAMETER_BRACED_INIT_LIST
#define MACHINE_PARAMETER_BRACED_INIT_LIST(...) __VA_ARGS__
#endif

/* NOTE Nic 04/04/2020: controllo __OPTIONS__size()
 * in questo modo gestisco un undefined behaviour delle std::initializer_list vuote
 */
#ifndef DECL_MACHINE_PARAMETER
#define DECL_MACHINE_PARAMETER(name, group, key, label, defaultValue, options) \
    MAYBE_UNUSED static constexpr std::initializer_list<dv::life::Option> __##name##__OPTIONS__ = { MACHINE_PARAMETER_BRACED_INIT_LIST options }; \
    MAYBE_UNUSED static constexpr MachineParameter name = MachineParameter( \
        group, \
        key, \
        label, \
        defaultValue, \
        __##name##__OPTIONS__.size() > 0 ? __##name##__OPTIONS__.begin() : nullptr, \
        __##name##__OPTIONS__.size() \
    );
#endif

//#ifndef DECL_MACHINE_PARAMETER
//#define DECL_MACHINE_PARAMETER(name, group, key, label, defaultValue, options) \
//#define DECL_MACHINE_PARAMETER(name, group, key, label, defaultValue, options) \
//    static constexpr MachineParameter name = { \
//        group, \
//        key, \
//        label, \
//        defaultValue, \
//        options \
//    };
//#endif



#ifndef DECL_MACHINE_PARAMETER_NOOPT
#define DECL_MACHINE_PARAMETER_NOOPT(name, group, key, label, defaultValue) \
    DECL_MACHINE_PARAMETER(name, group, key, label, defaultValue, ( ) )
#endif

#define TYPE_OF_MP(p) \
    static_assert(isMachineParameter<remove_const_ref_t<decltype(p)>>::value, "Il tipo di parametro deve essere MachineParameter"); \
    remove_const_ref_t<decltype(std::get<p.defaultValue.index()>(p.defaultValue))>


// qui verifico se un parametro e' di tipo MachineParameter o no
template <typename T>
struct isMachineParameter {
    static constexpr bool value = false;
};

template <>
struct isMachineParameter<MachineParameter> {
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
    return mp.template isType<V>();
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
