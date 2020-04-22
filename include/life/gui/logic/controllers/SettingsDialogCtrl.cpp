#include "SettingsDialogCtrlP.hpp"
#include "SettingsDialogCtrl.hpp"

#include <life/common/logging/Logger.hpp>
#include <life/gui/logic/data/SettingsDialogData.hpp>


using namespace dvlife;


/*** MENU MODEL ***/

MenuModel::MenuModel(QObject* parent) : QAbstractListModel(parent), menuContainer(nullptr) {

    traceEnter;
    traceExit;

}

int MenuModel::rowCount(const QModelIndex& parent) const {

    traceEnter;

    // se ha un parent, significa che la struttura e' gerarchica, quindi non e' una lista
    if (parent.isValid() || !operator bool())
        return 0;

    return menuContainer->size();

    traceExit;

}

bool MenuModel::setData(const QModelIndex& index, const QVariant& value, int role) {

    traceEnter;

    bool successfull = false;

    if (!operator bool())
        return successfull;

    int row = index.row();

    MenuItem item;

    try {
        item = menuContainer->itemAt(row);
    }  catch (menucontainer::IndexOutOfBoundException& ex) {
        traceErr() << "Indice out of range: " << row;
        return successfull;
    }

    switch (static_cast<MENU_ROLES>(role)) {
    case MENU_ROLES::LABEL: item.setLabel(value.value<QString>()); break;
    case MENU_ROLES::IMAGE: item.setImage(value.value<QString>()); break;
    case MENU_ROLES::ENABLED: item.setEnabled(value.value<bool>()); break;
    }

    try {

        menuContainer->setItem(item, row);
        emit dataChanged(index, index, QVector<int>() << role);
        successfull = true;

    }  catch (menucontainer::IndexOutOfBoundException& ex) {
        traceErr() << "Indice out of range: " << row;
        return successfull;
    }

    traceExit;
    return successfull;

}

QVariant MenuModel::data(const QModelIndex& index, int role) const {

    traceEnter;

    int row = index.row();

    try {

        traceDebug() << "Indice richiesto: " << row;

        auto&& item = menuContainer->itemAt(row);
        switch (static_cast<MENU_ROLES>(role)) {
        case MENU_ROLES::LABEL: return item.getLabel();
        case MENU_ROLES::IMAGE: return item.getImage();
        case MENU_ROLES::ENABLED: return item.isEnabled();
        }

    }  catch (menucontainer::IndexOutOfBoundException& ex) {
        traceErr() << "Indice out of range: " << row;
    }

    traceExit;
    return QVariant();

}

QHash<int, QByteArray> MenuModel::roleNames() const {

    traceEnter;

    QHash<int, QByteArray> roles;
    roles[static_cast<int>(MENU_ROLES::LABEL)] = "itemLabel";
    roles[static_cast<int>(MENU_ROLES::IMAGE)] = "itemImage";
    roles[static_cast<int>(MENU_ROLES::ENABLED)] = "itemIsEnabled";

    traceExit;
    return roles;

}

MenuContainer* MenuModel::getMenuContainer() const {

    traceEnter;
    traceExit;
    return menuContainer;

}

void MenuModel::setMenuContainer(MenuContainer::Ptr container) {

    traceEnter;

    if (!container)
        return;

    if (operator bool())
        menuContainer->disconnect(this);

    beginResetModel();

    this->menuContainer = container;
    connect(menuContainer, &MenuContainer::beforeInsert, this, [=](int row) {
        beginInsertRows(QModelIndex(), row, row);
    });
    connect(menuContainer, &MenuContainer::afterInsert, this, [=]() {
        endInsertRows();
    });
    connect(menuContainer, &MenuContainer::beforeRemove, this, [=](int row) {
        beginRemoveRows(QModelIndex(), row, row);
    });
    connect(menuContainer, &MenuContainer::afterRemove, this, [=]() {
        endRemoveRows();
    });
    connect(menuContainer, &MenuContainer::dataChanged, this, [=](int row) {
        dataChanged(index(row, 0), index(row, 0));
    });

    endResetModel();

    emit menuContainerChanged();

    traceExit;

}



/*** SETTINGS CONTROLLER PRIVATE ***/

SettingsDialogCtrlP::SettingsDialogCtrlP(QObject* parent) :
    QObject(parent), menuModel(new MenuModel()) {

    traceEnter;
    traceExit;

}

SettingsDialogCtrlP::~SettingsDialogCtrlP() {

    traceEnter;
    traceExit;

}



/*** SETTINGS CONTROLLER ***/

SettingsDialogCtrl::SettingsDialogCtrl(QObject* parent) :
    SettingsDialogCtrl(nullptr, nullptr, parent) {

    traceEnter;
    traceExit;

}

SettingsDialogCtrl::SettingsDialogCtrl(MAYBE_UNUSED QQmlEngine* qmlEngine, MAYBE_UNUSED QJSEngine* jsEngine, QObject* parent) :
    BaseController(parent),
    dPtr(new SettingsDialogCtrlP()),
    data(new SettingsDialogData()) {

    traceEnter;

    dPtr->qPtr = this;
    dPtr->menuModel->setMenuContainer(data->getMenuContainer());

    this->initialize();
    this->setupSignalsAndSlots();

    traceExit;

}

SettingsDialogCtrl::~SettingsDialogCtrl() {

    traceEnter;
    delete dPtr;
    delete data;
    traceExit;

}

MenuModel* SettingsDialogCtrl::getMenuModel() {
    traceEnter;
    traceExit;
    return dPtr->menuModel.data();
}

void SettingsDialogCtrl::initialize() {

    traceEnter;

    traceDebug() << "Inizializzo il menu principale";

    auto&& menuContainer = this->data->getMenuContainer();
    menuContainer->appendItem({tr("SW Settings"), "qrc:/icons/devices_other-24px.svg", true});
    menuContainer->appendItem({tr("Date/Time"), "qrc:/icons/calendar_today-24px", true});
    menuContainer->appendItem({tr("Languages"), "qrc:/icons/translate-24px.svg", true});
    menuContainer->appendItem({tr("Network"), "qrc:/icons/router-24px.svg", true});

    traceExit;

}

SettingsDialogData::Ptr SettingsDialogCtrl::getData() {

    traceEnter;
    traceExit;
    return data;

}

void SettingsDialogCtrl::setupSignalsAndSlots() {

    traceEnter;
    traceExit;

}

void SettingsDialogCtrl::testAdd()
{
//    data->getMenuContainer()->setItem({"Single-line item -1", "qrc:/icons/menu-24px.svg", true}, 0);
//    data->getMenuContainer()->appendItem({"Single-line item 4", "qrc:/icons/menu-24px.svg", true});

}
