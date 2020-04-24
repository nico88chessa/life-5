#ifndef SETTINGSDIALOGDATA_HPP
#define SETTINGSDIALOGDATA_HPP

#include <configure.h>

#include <QObject>
#include <QString>
#include <QList>
#include <QVariant>

#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

/* NOTE NIC 20/04/2020: gestione eccezioni
   per ora metto sotto namespace le varie eccezioni; e' da valutare
   se fare una classe standard sottonamespace dv::life con le eccezioni
   che sono comuni a varie classi
*/
namespace settingsdialogdata {

class IndexOutOfBoundException : public std::exception {
public:
    IndexOutOfBoundException() { }

    virtual const char* what() const noexcept {
        return "Index out of bound exception";
    }
};

}



/*** MENU ITEM ***/

class MenuItem {
    DV_DECL_POINTER_ALIAS(MenuItem)

private:
    QString label;
    QString image;
    bool enabled;

public:
    MenuItem(const QString& label="", const QString& image="", bool enabled = true) :
        label(label), image(image), enabled(enabled) { }

    QString getLabel() const noexcept { return label; }

    void setLabel(const QString& value) noexcept { label = value; }

    QString getImage() const noexcept { return image; }

    void setImage(const QString& value) noexcept { image = value; }

    bool isEnabled() const noexcept { return enabled; }

    void setEnabled(bool value) noexcept { enabled = value; }

    friend std::ostream& operator<<(std::ostream& os, const MenuItem& item);

};



/*** MENU CONTAINER ***/

class MenuContainer : public QObject {
    Q_OBJECT
    DV_DECL_POINTER_ALIAS(MenuContainer)

private:
    QList<MenuItem> items;

public:
    explicit MenuContainer(QObject* parent = nullptr);

    virtual ~MenuContainer();

    int size() const noexcept;

    void addItem(const MenuItem& item, int index) noexcept;

    void appendItem(const MenuItem& item) noexcept;

    /**
       \brief setItem
       \param item
       \param index
     */
    void replaceItem(const MenuItem& item, int index) noexcept(false);

    /**
       \brief itemAt
       \param index
       \throw IndexOutOfBoundException se index non e' valido
       \return
     */
    const MenuItem& itemAt(int index) const noexcept(false);

    /**
       \brief removeItem
       \param index
       \throw IndexOutOfBoundException se index non e' valido
     */
    void removeItem(int index) noexcept(false);

protected:
    bool isIndexValid(int index) const noexcept;

signals:
    void beforeInsert(int index);
    void afterInsert(int index);
    void dataChanged(int index);
    void beforeRemove(int index);
    void afterRemove(int index);

};



/*** SETTINGS PARAMETER ***/

class SettingsParameter {
    Q_GADGET
    Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")
    DV_DECL_POINTER_ALIAS(SettingsParameter)

    friend class SettingsGroup;

public:
    enum class ParameterType : int {
        INT = 0,
        DOUBLE,
        AXISXFEEDBACK,
        MOTORXKIND
    };
    Q_ENUM(ParameterType)

private:
    QString name;
    QVariant value;
    ParameterType type;

public:
    SettingsParameter(const QString& name, QVariant value = 0, ParameterType type = ParameterType::INT) :
        name(name), value(value), type(type) { }

    QString getName() const { return name; }

    void setName(const QString& value) { name = value; }

    QVariant getValue() const noexcept { return value; }

    void setValue(const QVariant& value) noexcept { this->value = value; }

    ParameterType getType() const noexcept { return type; }

    void setType(const ParameterType& value) noexcept { type = value; }

    friend bool operator==(const SettingsParameter& left, const SettingsParameter& right);

    friend std::ostream& operator<<(std::ostream& os, const SettingsParameter& parameter);

};



/*** SETTINGS GROUP ***/

class SettingsGroup {
    DV_DECL_POINTER_ALIAS(SettingsGroup)

    using Parameter = class SettingsParameter;

private:
    QString name;
    bool mandatory;
    bool active;
    QList<SettingsParameter> parameters;

public:
    SettingsGroup(const QString& groupName="",
                  bool mandatory=false,
                  bool active=false) :
        name(groupName), mandatory(mandatory), active(active) { }

    QString getName() const noexcept { return name; }

    void setName(const QString& value) noexcept { name = value; }

    bool isMandatory() const noexcept { return mandatory; }

    void setMandatory(bool value) noexcept { mandatory = value; }

    bool isActive() const noexcept { return active; }

    void setActive(bool value) noexcept { active = value; }

    int size() const noexcept { return parameters.size(); }

    const QList<SettingsParameter>& getParameters() const noexcept { return parameters; }

    /**
       \brief indexOf
       \param p
       \return
       \throw IndexOutOfBoundException se parametro non e' presente
     */
    int indexOf(const SettingsParameter& p) const noexcept(false) {

        int index;
        if ((index = parameters.indexOf(p)) < 0)
            throw settingsdialogdata::IndexOutOfBoundException();

        return index;
    }

    void appendParameter(const SettingsParameter& p) noexcept {
        parameters.append(p);
    }

    /**
       \brief parameterAt
       \param index
       \return
       \throw IndexOutOfBoundException se index non e' valido
     */
    SettingsParameter& parameterAt(int index) noexcept(false) {
        if (!isIndexValid(index))
            throw settingsdialogdata::IndexOutOfBoundException();
        return parameters[index];
    }

    /**
       \brief parameterAt
       \param index
       \return
       \throw IndexOutOfBoundException se index non e' valido
     */
    const SettingsParameter& parameterAt(int index) const noexcept(false) {
        if (!isIndexValid(index))
            throw settingsdialogdata::IndexOutOfBoundException();
        return parameters.at(index);
    }

    /**
       \brief replaceParameter
       \param index
       \param parameter
       \throw IndexOutOfBoundException se index non e' valido
     */
    void replaceParameter(int index, const SettingsParameter& parameter) noexcept(false) {
        if (!isIndexValid(index))
            throw settingsdialogdata::IndexOutOfBoundException();
        parameters.replace(index, parameter);
    }

    /**
       \brief removeParameterAtIndex
       \param index
       \throw IndexOutOfBoundException se index non e' valido
     */
    void removeParameterAtIndex(int index) noexcept(false) {
        if (!isIndexValid(index))
            throw settingsdialogdata::IndexOutOfBoundException();

        parameters.removeAt(index);
    }

    friend bool operator==(const SettingsGroup& left, const SettingsGroup& right);

    friend std::ostream& operator<<(std::ostream& os, const SettingsGroup& parameter);

protected:
    bool isIndexValid(int index) const noexcept { return index >= 0 && index < parameters.size(); }

};



/*** SETTINGS GROUP CONTAINER ***/

class SettingsGroupContainer : public QObject {
    Q_OBJECT
    DV_DECL_POINTER_ALIAS(SettingsGroupContainer)

private:
    QList<SettingsGroup> groups;

public:
    SettingsGroupContainer(QObject* parent = nullptr);

    Q_INVOKABLE int size() const noexcept;

    void addSettingsGroup(const SettingsGroup& group, int index) noexcept;

    void appendSettingsGroup(const SettingsGroup& group) noexcept;

    /**
       \brief removeSettingsGroup
       \param index
       \throw IndexOutOfBoundException se index non e' valido
     */
    void removeSettingsGroup(int index) noexcept(false);

    /**
       \brief replaceGroup
       \param index
       \param group
       \throw IndexOutOfBoundException se index non e' valido
     */
    void replaceSettingsGroup(int index, const SettingsGroup& group) noexcept(false);

    /**
       \brief settingsGroupAt
       \param index
       \return
       \throw IndexOutOfBoundException se index non e' valido
     */
    SettingsGroup& settingsGroupAt(int index) noexcept(false);

    /**
       \brief settingsGroupAt
       \param index
       \return
       \throw IndexOutOfBoundException se index non e' valido
     */
    const SettingsGroup& settingsGroupAt(int index) const noexcept(false);

    /**
       \brief groupParameters
       \param index
       \return
       \throw IndexOutOfBoundException se index non e' valido
     */
    const QList<SettingsGroup::Parameter>& settingsGroupParameters(int index) const noexcept(false);

    /**
       \brief parameterAtGroup
       \param indexGroup
       \param parameterName
       \return
       \throw IndexOutOfBoundException se groupIndex non e' valido
       \throw IndexOutOfBoundException se parameterIndex non e' valido
     */
    SettingsGroup::Parameter parameterAtGroup(int groupIndex, int parameterIndex) const noexcept(false);

    /**
       \brief parameterAtGroup
       \param indexGroup
       \param parameterName
       \return
       \throw IndexOutOfBoundException se groupIndex non e' valido
       \throw IndexOutOfBoundException se parameterName non presente
     */
    SettingsGroup::Parameter parameterAtGroup(int groupIndex, const QString& parameterName) const noexcept(false);

    /**
       \brief appendParameter
       \param groupIndex
       \param parameter
       \throw IndexOutOfBoundException se groupIndex non e' valido
     */
    void appendParameterAtGroup(int groupIndex, const SettingsGroup::Parameter& parameter) noexcept(false);

    /**
       \brief replaceParameter
       \param groupIndex
       \param parameterIndex
       \param parameter
       \throw IndexOutOfBoundException se groupIndex non e' valido
       \throw IndexOutOfBoundException se parameterName non presente
     */
    void replaceParameterAtGroup(int groupIndex, int parameterIndex, const SettingsGroup::Parameter& parameter) noexcept(false);

    /**
       \brief removeParameter
       \param groupIndex
       \param parameterIndex
       \throw IndexOutOfBoundException se groupIndex non e' valido
       \throw IndexOutOfBoundException se parameterName non presente
     */
    void removeParameterAtGroup(int groupIndex, int parameterIndex) noexcept(false);


protected:
    bool isIndexValid(int index) const;

signals:
    void beforeInsertGroup(int index);
    void afterInsertGroup(int index);
    void groupChanged(int index);
    void beforeRemoveGroup(int index);
    void afterRemoveGroup(int index);

    void beforeInsertParameter(int groupIndex, int index);
    void afterInsertParameter(int groupIndex, int index);
    void parameterChanged(int groupIndex, int index);
    void beforeRemoveParameter(int groupIndex, int index);
    void afterRemoveParameter(int groupIndex, int index);

};



/*** SETTINGS DIALOG DATA ***/

class SettingsDialogData : public QObject {
    Q_OBJECT

public:
    DV_DECL_POINTER_ALIAS(SettingsDialogData)

private:
    MenuContainer menuContainer;
    SettingsGroupContainer settingsGroupContainer;

public:
    explicit SettingsDialogData(QObject* parent = nullptr);

    const MenuContainer& getMenuContainer() const noexcept;

    MenuContainer& getMenuContainer() noexcept;

    const SettingsGroupContainer& getSettingsGroupContainer() const noexcept;

    SettingsGroupContainer& getSettingsGroupContainer() noexcept;

};

DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dv::life::MenuItem)

#endif // SETTINGSDATA_HPP
