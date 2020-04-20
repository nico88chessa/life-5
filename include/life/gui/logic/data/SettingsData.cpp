#include "SettingsData.hpp"

#include <life/common/logging/Logger.hpp>


using namespace dvlife;
using namespace dvlife::inner;

namespace dv::life::inner {

std::ostream& operator<<(std::ostream& os, const MenuItem& item) {
    os << "MenuItem: " << item.label;// << " - " << item.image << " - " << item.enabled;
    return os;
}

}



/*** MENU MODEL ***/

MenuModel::MenuModel(QObject* parent): QAbstractListModel(parent), menu() {

}

void MenuModel::appendMenuItem(const MenuItem& item) {

    traceEnter;
    menu.append(item);
    traceExit;

}

QVariant MenuModel::data(const QModelIndex& index, int role) const {

    traceEnter;
    int row = index.row();
    if (row > this->rowCount(index))
        return QVariant();

    traceDebug() << "MenuModel data riga richiesta: " << row;
    auto&& itemRequest = menu.at(row);
    traceDebug() << "MenuModel item: " << itemRequest;

    switch (role) {
    case MenuLabel: return itemRequest.getLabel();
    case MenuImage: return itemRequest.getImage();
    case MenuEnabled: return itemRequest.isEnabled();
    default: return QVariant();
    }

    traceExit;

}

int MenuModel::rowCount(MAYBE_UNUSED const QModelIndex& parent) const {

    traceEnter;
    return menu.size();
    traceExit;

}

QHash<int, QByteArray> MenuModel::roleNames() const {

    traceEnter;

    QHash<int, QByteArray> hash;
    hash[MenuModelRole::MenuLabel] = "mLabel";
    hash[MenuModelRole::MenuImage] = "mImage";
    hash[MenuModelRole::MenuEnabled] = "mEnabled";

    traceExit;
    return hash;

}



/*** SETTINGS DATA ***/

dv::life::SettingsData::SettingsData(QObject* parent) : QObject(parent), menuModel() {

    traceEnter;
    menuModel.appendMenuItem({"Single-line item", "qrc:/icons/menu-black-18dp.svg", true});
    menuModel.appendMenuItem({"Single-line item", "qrc:/icons/settings-24px.svg", true});
    menuModel.appendMenuItem({"Single-line item", "", true});
    traceExit;

}

inner::MenuModel::Ptr SettingsData::getMenuModel() {
    return &menuModel;
}
