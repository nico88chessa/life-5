#include "SettingsManager.hpp"

#include <QString>

#include <life/common/settings/descriptors/Descriptors.hpp>


using namespace dvlife;

SettingsManager& SettingsManager::instance() {

    traceEnter;
    static SettingsManager sm = SettingsManager();
    traceExit;
    return sm;

}

SettingsManager::SettingsManager() : groups() {

    traceEnter;
    this->addParameter(AXIS_X_DESCR.getParameters());
    this->addParameter(AXIS_Z_DESCR.getParameters());
    traceExit;

}

SettingsManager::~SettingsManager() {

}

void SettingsManager::addParameter(const std::initializer_list<MachineParameter>& list) {

    traceEnter;
    for (auto&& v: list) {
        SettingsGroup currentGroup = v.group;
        if (!groups.contains(currentGroup))
            groups.insert(currentGroup, detail::Group());

        detail::Group& values = groups[currentGroup];
//        if (isMachineParameterInt(v))
//            values.getParams()[v.key] = std::get<int>(v.defaultValue);
//        else if (isMachineParameterDouble(v))
//            values.getParams()[v.key] = std::get<double>(v.defaultValue);
//        else if (isMachineParameterMotorXKind(v))
//            values.getParams()[v.key] = QVariant::fromValue(std::get<dv::life::MotorXKind>(v.defaultValue));
//        else if (isMachineParameterXFeedback(v))
//            values.getParams()[v.key] = QVariant::fromValue(std::get<dv::life::AxisXFeedback>(v.defaultValue));

        /* NOTE NIC 01/04/2020
         * per questo trucco, vedere link https://en.cppreference.com/w/cpp/utility/variant/visit
         * il funzionamento del magico std::visit e' il seguente:
         * per ogni variant, viene ritornato il cast al tipo di valore che il variant contiene;
         * una volta fatto il cast, viene chiamata la funzione Callable passata come primo
         * parametro dalla funzione visit stessa.
         * In questo caso quindi, la successione di eventi e' questa:
         * 1. passo il std::variant
         * 2. converte il std::variant ad un valore fra: int, double, ecc ecc
         * 3. il valore convertito passa alla funzione lambda
         * 4. la funzione lambda converte il valore a QVariant
         * La condizione if constexpr garantisce che la decisione del tipo viene fatta
         * a compile-time, non a runtime!!
         */

        auto setter = [](auto&& stdVariant, QVariant& v) {

            v = QVariant::fromValue(std::visit([](auto&& sv) -> QVariant {
                using T = std::decay_t<decltype(sv)>;
                if constexpr (std::is_same_v<T, int>)
                    return static_cast<int>(sv);
                else if constexpr (std::is_same_v<T, double>)
                    return static_cast<double>(sv);
                else if constexpr (std::is_same_v<T, MotorXKind>)
                    return QVariant::fromValue(static_cast<dvlife::MotorXKind>(sv));
                else if constexpr (std::is_same_v<T, AxisXFeedback>)
                    return QVariant::fromValue(static_cast<dvlife::AxisXFeedback>(sv));
            }, stdVariant));

        };

        setter(v.defaultValue, values.getParams()[v.key]);

    }
    traceExit;

}
