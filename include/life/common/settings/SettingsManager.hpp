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
    QString name;
    bool mandatory;
    bool enabled;
    QMap<QString, QVariant> params;

public:
    Group() : Group("", false, false) { }
    Group(QString name) : Group(name, false) { }
    Group(QString name, bool isMandatory) : Group(name, isMandatory, isMandatory==true) { }
    Group(QString name, bool isMandatory, bool isEnabled) :
        name(name),
        mandatory(isMandatory),
        enabled(isEnabled), params() { }

    inline QStringView getName() const { return name; }
    inline bool isMandatory() const { return mandatory; }
    inline bool isEnabled() const { return enabled; }
    inline void setEnabled(bool value) noexcept(false) {
        if (isMandatory() && !value)
            throw dvlife::exceptions::DisableMandatoryGroupException();
        enabled = value;
    }
    QMap<QString, QVariant>& getParams() { return params; }
    const QMap<QString, QVariant>& getParams() const { return params; }
};

}

DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dvlife::detail::Group)

DV_LIFE_OPEN_NAMESPACE

class SettingDescriptor;

class SettingsManager {

private:
    QMap<SettingsGroupType, detail::Group> groups;

public:
    static SettingsManager& instance();

private:
    SettingsManager();
    ~SettingsManager();

    SettingsManager(const SettingsManager& other) = delete;
    SettingsManager(SettingsManager&& other) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    void addGroupFromDescriptor(const dv::life::SettingDescriptor& settingDescriptor) noexcept;
    void addMachineParameters(const std::initializer_list<MachineParameter>& list) noexcept;


public:

    template <typename T>
    T getParameter(const MachineParameter p) const noexcept(false) {

        traceEnter;
        auto&& temp = this->getParameter<T>(p.group, QLatin1String(p.key));
        traceExit;

        return temp;

    }

    template <typename T>
    T getParameter(SettingsGroupType groupId, const QLatin1String& paramKey) const noexcept(false) {

        traceEnter;

        if (!groups.contains(groupId)) {
            traceErr() << "Gruppo non trovato nel set di parametri";
            throw dvlife::exceptions::SettingsManagerGroupParameterNotFoundException(utils::EnumUtils::enumToName(groupId).toStdString());
        }

        const detail::Group& selectedGroup = groups[groupId];
//        QString paramKey = key.toString();
        if (!selectedGroup.getParams().contains(paramKey)) {
            traceErr() << "Parametro non trovato all'interno del gruppo";
            throw dvlife::exceptions::SettingsManagerParameterNotFoundException(
                        utils::EnumUtils::enumToName(groupId).toStdString(),
                        utils::EnumUtils::enumToName(groupId).toStdString());
        }

        const QVariant& pValue = selectedGroup.getParams()[paramKey];

        if (!pValue.canConvert<T>()) {
            traceErr() << "Richiesto tipo di dato errato";
            throw dvlife::exceptions::SettingsManagerTypeMismatchException();
        }

        traceExit;

        return pValue.value<T>();

    }

    void loadFromFile();

    void flush();

};


DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSMANAGER_HPP
