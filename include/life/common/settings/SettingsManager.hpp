#ifndef SETTINGSMANAGER_HPP
#define SETTINGSMANAGER_HPP

#include <configure.h>

#include <type_traits>

#include <QMap>
#include <QVariant>
#include <QString>

#include <life/common/logging/Logger.hpp>
#include <life/common/Types.hpp>
#include <life/common/Enums.hpp>
#include <life/common/Utils.hpp>
#include <life/common/settings/MachineParameter.hpp>
#include <life/common/settings/SettingsManagerExceptions.hpp>
#include <life/common/settings/IODescriptor.hpp>


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
    inline bool setEnabled(bool value) noexcept {
        if (isMandatory() && !value)
            return false;
        enabled = value;
        return true;
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
    QMap<DIKey, DigitalInputDescr> digitalInputs;
    QMap<DOKey, DigitalOutputDescr> digitalOutputs;
    QMap<AIKey, AnalogInputDescr> analogInputs;

public:
    static SettingsManager& instance();

private:
    SettingsManager();
    ~SettingsManager();

    SettingsManager(const SettingsManager& other) = delete;
    SettingsManager(SettingsManager&& other) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;

    void initialize();
    void addGroupFromDescriptor(const dv::life::SettingDescriptor& settingDescriptor) noexcept;
    void addMandatoryIO() noexcept;


    void loadFromFile();

    /**
     * \brief addDigitalInput
     * \param d digital input da aggiungere
     * \return True se l'aggiunta e' andata a buon fine, False altrimenti
     */
    bool addDigitalInput(const DigitalInputDescr& d, bool overwriteIfExists = false);

    /**
     * \brief addDigitalOutput
     * \param d
     * \return True se l'aggiunta e' andata a buon fine, False altrimenti
     */
    bool addDigitalOutput(const DigitalOutputDescr& d, bool overwriteIfExists = false);


    /**
     * \brief addAnalogInput
     * \param d
     * \return True se l'aggiunta e' andata a buon fine, False altrimenti
     */
    bool addAnalogInput(const AnalogInputDescr& a, bool overwriteIfExists = false);

public:

    /**
     * \throw GroupParameterNotFoundException
     * \throw ParameterNotFoundException
     * \throw TypeMismatchException
     */
    template <typename T>
    T getParameter(const MachineParameter p) const noexcept(false) {

        traceEnter;
        auto&& temp = this->getParameter<T>(p.group, QLatin1String(p.key));
        traceExit;

        return temp;

    }

    /**
     * \throw GroupParameterNotFoundException
     * \throw ParameterNotFoundException
     * \throw TypeMismatchException
     */
    template <typename T>
    T getParameter(SettingsGroupType groupId, QLatin1String paramKey) const noexcept(false) {

        traceEnter;
        using namespace dvlife::exceptions;

        if (!groups.contains(groupId)) {
            traceErr() << "Gruppo non trovato nel set di parametri";
            throw GroupParameterNotFoundException(utils::EnumUtils::enumToName(groupId).toStdString());
        }

        const detail::Group& selectedGroup = groups[groupId];
        if (!selectedGroup.getParams().contains(paramKey)) {
            traceErr() << "Parametro non trovato all'interno del gruppo";
            throw ParameterNotFoundException(
                        utils::EnumUtils::enumToName(groupId).toStdString(),
                        paramKey.cbegin());
        }

        const QVariant& pValue = selectedGroup.getParams()[paramKey];

        if (!pValue.canConvert<T>()) {
            traceErr() << "Richiesto tipo di dato errato";
            throw TypeMismatchException();
        }

        traceExit;

        return pValue.value<T>();

    }

    /**
     * \throw GroupParameterNotFoundException
     * \throw ParameterNotFoundException
     * \throw TypeMismatchException
     */
    template <typename T>
    void setParameter(const MachineParameter p, T value) noexcept(false) {

        traceEnter;
        this->setParameter<T>(p.group, QLatin1String(p.key), value);
        traceExit;
    }

    /**
     * \throw GroupParameterNotFoundException
     * \throw ParameterNotFoundException
     * \throw TypeMismatchException
     */
    template <typename T>
    void setParameter(SettingsGroupType groupId, QLatin1String paramKey, T value) noexcept(false) {

        traceEnter;

        using namespace dvlife::exceptions;

        if (!groups.contains(groupId)) {
            traceErr() << "Gruppo non trovato nel set di parametri";
            throw GroupParameterNotFoundException(utils::EnumUtils::enumToName(groupId).toStdString());
        }

        detail::Group& selectedGroup = groups[groupId];
        if (!selectedGroup.getParams().contains(paramKey)) {
            traceErr() << "Parametro non trovato all'interno del gruppo";
            throw ParameterNotFoundException(
                        utils::EnumUtils::enumToName(groupId).toStdString(),
                        paramKey.cbegin());
        }

        QVariant& pValue = selectedGroup.getParams()[paramKey];

        if (!pValue.canConvert<T>()) {
            traceErr() << "Richiesto tipo di dato errato";
            throw TypeMismatchException();
        }

        pValue = QVariant::fromValue(value);

        traceExit;

    }

    /**
     * \brief addDigitalInput
     * \param d digital input da aggiungere
     * \return true se l'aggiunta e' andata a buon fine, false altrimenti
     */
    bool addDigitalInput(const DigitalInput& d);

    /**
     * \brief addDigitalOutput
     * \param d
     * \return true se l'aggiunta e' andata a buon fine, false altrimenti
     */
    bool addDigitalOutput(const DigitalOutput& d);


    /**
     * \brief addAnalogInput
     * \param d
     * \return true se l'aggiunta e' andata a buon fine, false altrimenti
     */
    bool addAnalogInput(const AnalogInput& a);

    /**
     * \brief removeDigitalInput
     * \param d
     * \return true se la rimozione e' andata a buon fine, false altrimenti
     */
    bool removeDigitalInput(const DigitalInput& d);

    /**
     * \brief removeDigitalOutput
     * \param d
     * \return true se la rimozione e' andata a buon fine, false altrimenti
     */
    bool removeDigitalOutput(const DigitalOutput& d);

    /**
     * \brief removeAnalogInput
     * \param d
     * \return true se la rimozione e' andata a buon fine, false altrimenti
     */
    bool removeAnalogInput(const AnalogInput& a);

    void flush();

    void restore();

};


DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSMANAGER_HPP
