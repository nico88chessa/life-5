#include "SettingsManager.hpp"

#include <QString>
#include <QSettings>

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

    // aggiungo i gruppi
//    for (auto&& groupDescriptor: settingsGroupsDescr) {
//        if (groups.contains(groupDescriptor.key))
//            continue;
//        QString groupName = utils::EnumUtils::getEnumName(groupDescriptor.key);
//        groups.insert(groupDescriptor.key, detail::Group(groupName, findGroupDescriptor(groupDescriptor.key).isMandatory));
//    }

    // ed i parametri ai gruppi con i valori di default
//    this->addMachineParameters(AXIS_X_DESCR.getParameters());
//    this->addMachineParameters(AXIS_Z_DESCR.getParameters());
//    addGroupFromDescriptor(dvlife::AXIS_X_DESCR);
    this->addGroupFromDescriptor(AXIS_X_DESCR);
    this->addGroupFromDescriptor(AXIS_Z_DESCR);
    traceExit;

    // ora carico i parametri da file (almeno quelli presenti nel file)
    loadFromFile();

    // una volta caricati, faccio il flush su file (utile nel caso di inizializzazione del file di configurazione)
    flush();

}

SettingsManager::~SettingsManager() {

}

void SettingsManager::addGroupFromDescriptor(const SettingDescriptor& settingDescriptor) noexcept {

    traceEnter;

    using namespace dvlife::detail;

    SettingsGroupType type = settingDescriptor.groupType();
    if (groups.contains(type)) {
        traceInfo() << "Gruppo gia' presente.";
        return;
    }

    QString groupName = utils::EnumUtils::enumToName(type);
    groups.insert(type, Group(groupName, settingDescriptor.isMandatory()));
    Group& group = groups[type];

    // inizio a scorrere i parametri
    for (int i=0; i<settingDescriptor.size(); ++i) {

        MachineParameter p = settingDescriptor.getParameters()[i];

        /* NOTE NIC 04/04/2020
         * per questo trucco, vedere link https://en.cppreference.com/w/cpp/utility/variant/visit
         * il funzionamento del magico std::visit e' il seguente:
         * per ogni variant, viene ritornato il cast al tipo di valore che il variant contiene;
         * una volta fatto il cast, viene chiamata la funzione Callable (passata come primo
         * parametro dalla funzione visit stessa).
         * In questo caso quindi, la successione di eventi e' questa:
         * 1. passo il std::variant
         * 2. converte il std::variant ad un valore fra: int, double, ecc ecc
         * 3. il valore convertito passa alla funzione Callable (lambda in questo caso)
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

        setter(p.defaultValue, group.getParams()[p.key]);

    }


    traceExit;

}

void SettingsManager::addMachineParameters(const std::initializer_list<MachineParameter>& list) noexcept {

    traceEnter;

    for (auto&& v: list) {
        SettingsGroupType currentGroupKey = v.group;
        if (!groups.contains(currentGroupKey)) {
            QString groupName = utils::EnumUtils::enumToName(currentGroupKey);
//            groups.insert(currentGroupKey, detail::Group(groupName, findGroupDescriptor(currentGroupKey).isMandatory));
        }

        detail::Group& group = groups[currentGroupKey];

        /* NOTE NIC 01/04/2020
         * per questo trucco, vedere link https://en.cppreference.com/w/cpp/utility/variant/visit
         * il funzionamento del magico std::visit e' il seguente:
         * per ogni variant, viene ritornato il cast al tipo di valore che il variant contiene;
         * una volta fatto il cast, viene chiamata la funzione Callable (passata come primo
         * parametro dalla funzione visit stessa).
         * In questo caso quindi, la successione di eventi e' questa:
         * 1. passo il std::variant
         * 2. converte il std::variant ad un valore fra: int, double, ecc ecc
         * 3. il valore convertito passa alla funzione Callable (lambda in questo caso)
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

        setter(v.defaultValue, group.getParams()[v.key]);

    }
    traceExit;

}

void SettingsManager::loadFromFile() {

    traceEnter;

    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION, PROJECT_NAME);

    // scorro i gruppi
    for (auto&& g: groups) {

        QStringView groupName = g.getName();

        // per ogni gruppo, prelevo i parametri
        auto&& paramsMap = g.getParams();
        for (auto&& paramKey: paramsMap.keys()) {

            QString stringKey = QString("%1/%2").arg(groupName).arg(paramKey);
            // valore da file o quello di default (caricato con il caricamento dei parametri)
            QVariant currentValue = settings.value(paramKey, paramsMap.value(paramKey));
            paramsMap[paramKey] = currentValue;

        }

    }

    traceExit;

}

void SettingsManager::flush() {

    traceEnter;
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, ORGANIZATION, PROJECT_NAME);

    // scorro i gruppi
    for (auto&& g: groups) {

        QStringView groupName = g.getName();

        // sul file di configurazione scrivo i gruppi che sono abilitati oppure sono obbligatori
        if (g.isEnabled() || g.isMandatory()) {

            // per ogni gruppo, prelevo i parametri
            auto&& paramsMap = g.getParams();
            for (auto&& paramKey: paramsMap.keys()) {

                QString stringKey = QString("%1/%2").arg(groupName).arg(paramKey);
                QVariant currentValue = paramsMap.value(paramKey);

                settings.setValue(stringKey, currentValue);

            }

        } else {
            // gli altri li elimino
            settings.remove(groupName.toString());
        }

    }

    settings.sync();

    traceExit;
}
