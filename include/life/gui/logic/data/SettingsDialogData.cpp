#include "SettingsDialogData.hpp"

#include <life/common/logging/Logger.hpp>


DV_LIFE_OPEN_NAMESPACE

std::ostream& operator<<(std::ostream& os, const MenuItem& item) {
    os << "MenuItem: " << item.label;// << " - " << item.image << " - " << item.enabled;
    return os;
}

std::ostream& operator<<(std::ostream& os, const SettingsParameter& parameter) {
    os << "Parameter: " << parameter.name;
    return os;
}

std::ostream& operator<<(std::ostream& os, const SettingsGroup& group) {
    os << "Parameter: " << group.name;
    return os;
}

bool operator==(const SettingsParameter& left, const SettingsParameter& right) {
    return left.name.compare(right.name, Qt::CaseInsensitive) == 0;
}

bool operator==(const SettingsGroup& left, const SettingsGroup& right) {
    return left.name.compare(right.name, Qt::CaseInsensitive) == 0;
}

DV_LIFE_CLOSE_NAMESPACE



using namespace dvlife;

/*** MENU CONTAINER ***/

MenuContainer::MenuContainer(QObject* parent) : QObject(parent)/*, items()*/ {

    traceEnter;
    traceExit;

}

MenuContainer::~MenuContainer() {

    traceEnter;
    traceExit;

}

int MenuContainer::size() const noexcept {

    traceEnter;
    traceDebug() << "Size: " << items.size();
    traceExit;
    return items.size();

}

void MenuContainer::addItem(const MenuItem& item, int index) noexcept {

    traceEnter;

    traceDebug() << "Aggiungo item " << item << " all'indice: " << index;

    // il controllo dell'indice viene fatto da QList
    emit beforeInsert(index);
    items.insert(index, item);
    emit afterInsert(index);

    traceExit;

}

void MenuContainer::appendItem(const MenuItem& item) noexcept {

    traceEnter;
    this->addItem(item, this->size());
    traceExit;

}

void MenuContainer::replaceItem(const MenuItem& item, int index) noexcept(false) {

    traceEnter;
    traceDebug() << "Replace item " << item << " all'indice: " << index;
    if (!isIndexValid(index))
        throw(settingsdialogdata::IndexOutOfBoundException());

    items.replace(index, item);
    emit dataChanged(index);

    traceExit;
}

const MenuItem& MenuContainer::itemAt(int index) const {

    traceEnter;
    traceDebug() << "itemAt: " << index;
    if (!isIndexValid(index))
        throw(settingsdialogdata::IndexOutOfBoundException());

    traceExit;
    return items.at(index);

}

void MenuContainer::removeItem(int index) {

    traceEnter;
    traceDebug() << "Rimozione item all'indice: " << index;
    if (!isIndexValid(index))
        throw(settingsdialogdata::IndexOutOfBoundException());

    items.removeAt(index);
    traceExit;

}

bool MenuContainer::isIndexValid(int index) const noexcept {

    traceEnter;
    traceDebug() << "Controllo validita' indice: " << index;
    traceExit;

    return index >= 0 && index < size();

}



/*** SETTINGS GROUP CONTAINER ***/

SettingsGroupContainer::SettingsGroupContainer(QObject* parent) : QObject(parent), groups() {
    traceEnter;
    traceExit;
}

int SettingsGroupContainer::size() const noexcept {
    traceEnter;
    traceDebug() << "Size: " << groups.size();
    traceExit;
    return groups.size();
}

void SettingsGroupContainer::addSettingsGroup(const SettingsGroup& group, int index) noexcept {

    traceEnter;

    if (index < 0)
        index = 0;
    else if (index > size())
        index = size();

    traceDebug() << "Aggiungo gruppo " << group << " all'indice: " << index;

    emit beforeInsertGroup(index);
    groups.insert(index, group);
    emit afterInsertGroup(index);

    traceExit;

}

void SettingsGroupContainer::appendSettingsGroup(const SettingsGroup& group) noexcept {

    traceEnter;
    this->addSettingsGroup(group, this->size());
    traceExit;

}

void SettingsGroupContainer::removeSettingsGroup(int index) noexcept(false) {

    traceEnter;
    traceDebug() << "Rimozione gruppo all'indice: " << index;
    if (!isIndexValid(index))
        throw(settingsdialogdata::IndexOutOfBoundException());

    void beforeRemoveGroup(int index);
    groups.removeAt(index);
    void afterRemoveGroup(int index);

    traceExit;

}

void SettingsGroupContainer::replaceSettingsGroup(int index, const SettingsGroup& group) noexcept(false) {

    traceEnter;
    traceDebug() << "Replace gruppo " << group << " all'indice: " << index;
    if (!isIndexValid(index))
        throw(settingsdialogdata::IndexOutOfBoundException());

    groups.replace(index, group);
    emit groupChanged(index);

    traceExit;

}

SettingsGroup& SettingsGroupContainer::settingsGroupAt(int index) noexcept(false) {

    traceEnter;
    traceDebug() << "Indice: " << index;
    if (!isIndexValid(index))
        throw(settingsdialogdata::IndexOutOfBoundException());

    traceExit;
    return groups[index];

}

const SettingsGroup& SettingsGroupContainer::settingsGroupAt(int index) const noexcept(false) {

    traceEnter;
    traceDebug() << "Indice: " << index;
    if (!isIndexValid(index))
        throw(settingsdialogdata::IndexOutOfBoundException());

    traceExit;
    return groups.at(index);

}

const QList<SettingsGroup::Parameter>& SettingsGroupContainer::settingsGroupParameters(int index) const noexcept(false) {

    traceEnter;
    traceExit;
    return settingsGroupAt(index).getParameters();
}

SettingsGroup::Parameter SettingsGroupContainer::parameterAtGroup(int groupIndex, int parameterIndex) const noexcept(false) {

    traceEnter;

    auto&& group = settingsGroupAt(groupIndex);
    SettingsGroup::Parameter p = group.parameterAt(parameterIndex);

    traceExit;
    return p;
}

SettingsGroup::Parameter SettingsGroupContainer::parameterAtGroup(int groupIndex, const QString& parameterName) const noexcept(false) {

    return parameterAtGroup(groupIndex, settingsGroupAt(groupIndex).indexOf(SettingsGroup::Parameter(parameterName)));

}

void SettingsGroupContainer::appendParameterAtGroup(int groupIndex, const SettingsGroup::Parameter& parameter) noexcept(false) {

    traceEnter;

    auto&& settingsGroup = settingsGroupAt(groupIndex);
    int parameterSize = settingsGroup.size();
    emit beforeInsertParameter(groupIndex, parameterSize);
    settingsGroup.appendParameter(parameter);
    emit afterInsertParameter(groupIndex, parameterSize);

    traceExit;

}

void SettingsGroupContainer::replaceParameterAtGroup(int groupIndex, int parameterIndex, const SettingsGroup::Parameter& parameter) noexcept(false) {

    traceEnter;
    auto&& settingsGroup = settingsGroupAt(groupIndex);
    settingsGroup.replaceParameter(parameterIndex, parameter);
    emit parameterChanged(groupIndex, parameterIndex);
    traceExit;

}

void SettingsGroupContainer::removeParameterAtGroup(int groupIndex, int parameterIndex) noexcept(false) {

    traceEnter;
    auto&& settingsGroup = settingsGroupAt(groupIndex);

    emit beforeRemoveParameter(groupIndex, parameterIndex);
    settingsGroup.removeParameterAtIndex(parameterIndex);
    emit afterRemoveParameter(groupIndex, parameterIndex);

    traceExit;

}

bool SettingsGroupContainer::isIndexValid(int index) const {
    traceEnter;
    traceDebug() << "Controllo validita' indice: " << index;
    traceExit;

    return index >= 0 && index < size();
}



/*** SETTINGS DATA ***/

SettingsDialogData::SettingsDialogData(QObject* parent) :
    QObject(parent),
    menuContainer(),
    settingsGroupContainer() {

    traceEnter;
    traceExit;

}

const MenuContainer& SettingsDialogData::getMenuContainer() const noexcept {
    return menuContainer;
}

MenuContainer& SettingsDialogData::getMenuContainer() noexcept {
    return menuContainer;
}

const SettingsGroupContainer& SettingsDialogData::getSettingsGroupContainer() const noexcept{
    return settingsGroupContainer;
}

SettingsGroupContainer& SettingsDialogData::getSettingsGroupContainer() noexcept {
    return settingsGroupContainer;
}
