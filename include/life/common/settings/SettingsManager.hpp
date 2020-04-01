#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <configure.h>

#include <type_traits>

#include <QMap>
#include <QVariant>
#include <QString>

#include <life/common/logging/Logger.hpp>
#include <life/common/Types.hpp>
#include <life/common/Utils.hpp>
#include <life/common/settings/MachineParameter.hpp>
#include <life/common/settings/SettingsManagerExceptions.hpp>


DV_LIFE_OPEN_NAMESPACE

namespace detail {

    class Group {
    public:
        using Ptr = Group*;
        using ConstPtr = const Group*;

    private:
        bool isEnabled;
        QMap<QString, QVariant> params;

    public:
        Group() : isEnabled(false), params() { }

        bool getIsEnabled() const { return isEnabled; }
        void setIsEnabled(bool value) { isEnabled = value; }
        QMap<QString, QVariant>& getParams() { return params; }
        const QMap<QString, QVariant>& getParams() const { return params; }

    };

}

DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dvlife::detail::Group)


DV_LIFE_OPEN_NAMESPACE

class SettingsManager {

private:
    QMap<SettingsGroup, detail::Group> groups;

public:
    static SettingsManager& instance();

private:
    SettingsManager();
    ~SettingsManager();

    SettingsManager(const SettingsManager& other) = delete;
    SettingsManager(SettingsManager&& other) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    void addParameter(const std::initializer_list<MachineParameter>& list);

public:

    template <typename T>
    T getParameter(const MachineParameter p) const noexcept(false) {

        traceEnter;
        auto&& temp = this->getParameter<T>(p.group, QLatin1String(p.key));
        traceExit;

        return temp;

    }

    template <typename T>
    T getParameter(SettingsGroup groupId, const QLatin1String& paramKey) const noexcept(false) {

        traceEnter;

        if (!groups.contains(groupId)) {
            traceErr() << "Gruppo non trovato nel set di parametri";
            throw dvlife::exceptions::SettingsManagerGroupParameterNotFoundException(utils::EnumUtils::getEnumName(groupId).data());
        }

        const detail::Group& selectedGroup = groups[groupId];
//        QString paramKey = key.toString();
        if (!selectedGroup.getParams().contains(paramKey)) {
            traceErr() << "Parametro non trovato all'interno del gruppo";
            throw dvlife::exceptions::SettingsManagerParameterNotFoundException(
                        utils::EnumUtils::getEnumName(groupId).data(),
                        utils::EnumUtils::getEnumName(groupId).data());
        }

        const QVariant& pValue = selectedGroup.getParams()[paramKey];

        if (!pValue.canConvert<T>()) {
            traceErr() << "Richiesto tipo di dato errato";
            throw dvlife::exceptions::SettingsManagerTypeMismatchException();
        }

        traceExit;

        return pValue.value<T>();

    }



};


DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSMANAGER_HPP
