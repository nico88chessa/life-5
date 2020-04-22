#include "SettingsDialogData.hpp"

#include <life/common/logging/Logger.hpp>


using namespace dvlife;

std::ostream& dvlife::operator<<(std::ostream& os, const MenuItem& item) {
    os << "MenuItem: " << item.label;// << " - " << item.image << " - " << item.enabled;
    return os;
}



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

    emit beforeInsert(index);
    if (index > size())
        items.append(item);

    items.insert(index, item);
    emit afterInsert(index);

    traceExit;

}

void MenuContainer::appendItem(const MenuItem& item) noexcept {

    traceEnter;
    this->addItem(item, this->size());
    traceExit;

}

void MenuContainer::setItem(const MenuItem& item, int index) noexcept(false) {

    traceEnter;
    traceDebug() << "Replace item " << item << " all'indice: " << index;
    if (!isIndexValid(index))
        throw(menucontainer::IndexOutOfBoundException());

    items.replace(index, item);
    emit dataChanged(index);

    traceExit;
}

MenuItem MenuContainer::itemAt(int index) const {

    traceEnter;
    traceDebug() << "Indice: " << index;
    if (!isIndexValid(index))
        throw(menucontainer::IndexOutOfBoundException());

    traceExit;
    return items.at(index);

}

void MenuContainer::removeItem(int index) {

    traceEnter;
    traceDebug() << "Rimozione item all'indice: " << index;
    if (!isIndexValid(index))
        throw(menucontainer::IndexOutOfBoundException());

    items.removeAt(index);
    traceExit;

}

bool MenuContainer::isIndexValid(int index) const noexcept {

    traceEnter;
    traceDebug() << "Controllo validita' indice: " << index;
    traceExit;

    return !(index < 0 || index > (this->size() - 1) );

}



/*** SETTINGS DATA ***/

SettingsDialogData::SettingsDialogData(QObject* parent) : QObject(parent), menuContainer() {

    traceEnter;
    traceExit;

}

MenuContainer::Ptr SettingsDialogData::getMenuContainer() {
    return &menuContainer;
}

