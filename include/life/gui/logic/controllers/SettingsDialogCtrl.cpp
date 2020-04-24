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
    if (parent.isValid() || !*this)
        return 0;

    return menuContainer->size();

    traceExit;

}

bool MenuModel::setData(const QModelIndex& index, const QVariant& value, int role) {

    traceEnter;

    bool successfull = false;

    if (!*this)
        return successfull;

    int row = index.row();

    MenuItem item;

    try {
        item = menuContainer->itemAt(row);
    }  catch (settingsdialogdata::IndexOutOfBoundException& ex) {
        traceErr() << "Indice out of range: " << row;
        return successfull;
    }

    switch (static_cast<Roles>(role)) {
    case Roles::LABEL: item.setLabel(value.value<QString>()); break;
    case Roles::IMAGE: item.setImage(value.value<QString>()); break;
    case Roles::ENABLED: item.setEnabled(value.value<bool>()); break;
    }

    try {

        menuContainer->replaceItem(item, row);
        emit dataChanged(index, index, QVector<int>() << role);
        successfull = true;

    }  catch (settingsdialogdata::IndexOutOfBoundException& ex) {
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
        switch (static_cast<Roles>(role)) {
        case Roles::LABEL: return item.getLabel();
        case Roles::IMAGE: return item.getImage();
        case Roles::ENABLED: return item.isEnabled();
        }

    }  catch (settingsdialogdata::IndexOutOfBoundException& ex) {
        traceErr() << "Indice out of range: " << row;
    }

    traceExit;
    return QVariant();

}

QHash<int, QByteArray> MenuModel::roleNames() const {

    traceEnter;

    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::LABEL)] = "itemLabel";
    roles[static_cast<int>(Roles::IMAGE)] = "itemImage";
    roles[static_cast<int>(Roles::ENABLED)] = "itemIsEnabled";

    traceExit;
    return roles;

}

MenuModel::operator bool() const noexcept {

    traceEnter;
    traceExit;
    return menuContainer != nullptr;

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

    if (*this)
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
        emit dataChanged(index(row, 0), index(row, 0));
    });

    endResetModel();

    emit menuContainerChanged();

    traceExit;

}



/*** SETTINGS GROUP PARAMETERS MODEL ***/

SettingsGroupParametersModel::SettingsGroupParametersModel(QObject* parent) :
    QAbstractListModel(parent), container(nullptr) {

    traceEnter;
    traceExit;
}

QHash<int, QByteArray> SettingsGroupParametersModel::roleNames() const noexcept {

    traceEnter;

    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::NAME)] = "parameterName";
    roles[static_cast<int>(Roles::VALUE)] = "parameterValue";
    roles[static_cast<int>(Roles::TYPE)] = "parameterType";

    traceExit;
    return roles;

}

int SettingsGroupParametersModel::rowCount(const QModelIndex& parent) const noexcept {

    traceEnter;

    if (parent.isValid() || !*this) {
        traceExit;
        return 0;
    }

    int size = 0;

    try {
        size = container->settingsGroupAt(groupIndex).size();
    } catch (settingsdialogdata::IndexOutOfBoundException& ex) {
        traceErr() << "L'indice del gruppo e' errato: " << groupIndex;
    }

    traceExit;
    return size;

}

QVariant SettingsGroupParametersModel::data(const QModelIndex& index, int role) const noexcept {

    if (!index.isValid()) {
        traceExit;
        return QVariant();
    }

    if (!*this) {
        traceExit;
        return QVariant();
    }

    try {
        int row = index.row();
        SettingsGroup::Parameter p = container->parameterAtGroup(groupIndex, row);

        switch (static_cast<Roles>(role)) {
        case Roles::NAME: return p.getName();
        case Roles::VALUE: return p.getValue();
        case Roles::TYPE: return QVariant::fromValue(p.getType());
        }

    }  catch (settingsdialogdata::IndexOutOfBoundException& ex) {
        traceErr() << "L'indice del gruppo e' errato: " << groupIndex;
    }

    traceExit;
    return QVariant();

}

bool SettingsGroupParametersModel::setData(
        const QModelIndex& index, const QVariant& value, int role) noexcept {

    if (!index.isValid()) {
        traceExit;
        return false;
    }

    if (!*this) {
        traceExit;
        return false;
    }

    try {
        int row = index.row();
        SettingsGroup::Parameter p = container->parameterAtGroup(groupIndex, row);

        switch (static_cast<Roles>(role)) {
        case Roles::NAME:
            p.setName(value.value<QString>());
            emit dataChanged(index, index, QVector<int>() << role);
            break;
        case Roles::VALUE:
            p.setValue(value);
            emit dataChanged(index, index, QVector<int>() << role);
            break;
        case Roles::TYPE:
            p.setType(value.value<SettingsParameter::ParameterType>());
            emit dataChanged(index, index, QVector<int>() << role);
            break;
        default: break;
        }
        container->replaceParameterAtGroup(groupIndex, row, p);
        return true;

    }  catch (settingsdialogdata::IndexOutOfBoundException& ex) {
        traceErr() << "L'indice del gruppo e' errato: " << groupIndex;
    }

    traceExit;
    return false;

}

void SettingsGroupParametersModel::setSettingsGroupContainerAndIndex(
        SettingsGroupContainer* value, int indexGroup) noexcept {

    traceEnter;

    if (value == nullptr) {
        traceDebug() << "Value e' nullptr";
        traceExit;
        return;
    }

    if ( (container == value) && (this->groupIndex == indexGroup) ) {
        traceDebug() << "Nessun cambiamento di modello";
        traceExit;
        return;
    }

    if (*this)
        container->disconnect(this);

    container = value;
    this->groupIndex = indexGroup;

    connect(container, &SettingsGroupContainer::beforeInsertParameter, this, [=](int groupIndex, int row) {
        if (this->groupIndex != groupIndex)
            return;
        beginInsertRows(QModelIndex(), row, row);
    });
    connect(container, &SettingsGroupContainer::afterInsertParameter, this, [=](int groupIndex, MAYBE_UNUSED int row) {
        if (this->groupIndex != groupIndex)
            return;
        endInsertRows();
    });
    connect(container, &SettingsGroupContainer::parameterChanged, this, [=](int groupIndex, int row) {
        if (this->groupIndex != groupIndex)
            return;
        emit dataChanged(this->index(row), this->index(row));
    });
    connect(container, &SettingsGroupContainer::beforeRemoveParameter, this, [=](int groupIndex, int row) {
        if (this->groupIndex != groupIndex)
            return;
        beginRemoveRows(QModelIndex(), row, row);
    });
    connect(container, &SettingsGroupContainer::afterRemoveParameter, this, [=](int groupIndex, MAYBE_UNUSED int row) {
        if (this->groupIndex != groupIndex)
            return;
        endRemoveRows();
    });

    traceExit;

}

void SettingsGroupParametersModel::setSettingsGroupContainer(SettingsGroupContainer* value) noexcept {
    traceEnter;
    this->setSettingsGroupContainerAndIndex(value, groupIndex);
    traceExit;
    return;
}

SettingsGroupContainer* SettingsGroupParametersModel::getSettingsGroupContainer() const noexcept {
    traceEnter;
    traceExit;
    return container;
}

int SettingsGroupParametersModel::getIndexGroup() const noexcept {
    traceEnter;
    traceExit;
    return groupIndex;
}

dv::life::SettingsGroupParametersModel::operator bool() const noexcept {
    return container != nullptr;
}



/*** SETTINGS GROUP CONTAINER ***/

SettingsGroupModel::SettingsGroupModel(QObject* parent) :
    QAbstractListModel(parent),
    container(nullptr) {

    traceEnter;
    traceExit;

}

QHash<int, QByteArray> SettingsGroupModel::roleNames() const noexcept {

    traceEnter;

    QHash<int, QByteArray> roles;
    roles[static_cast<int>(Roles::NAME_ROLE)] = "itemName";
    roles[static_cast<int>(Roles::ACTIVE_ROLE)] = "itemIsActive";
    roles[static_cast<int>(Roles::MANDATORY_ROLE)] = "itemIsMandatory";

    traceExit;
    return roles;

}

int SettingsGroupModel::rowCount(MAYBE_UNUSED const QModelIndex& parent) const noexcept {

    traceEnter;
    if (parent.isValid() || !*this) {
        traceExit;
        return 0;
    }

    traceExit;
    return container->size();

}

QVariant SettingsGroupModel::data(const QModelIndex& index, int role) const noexcept {

    traceEnter;
    if (!*this) {
        traceExit;
        return QVariant();
    }

    if (!index.isValid()) {
        traceExit;
        return QVariant();
    }

    int row = index.row();

    try {

        auto&& settingsGroup = container->settingsGroupAt(row);

        switch (static_cast<Roles>(role)) {
        case Roles::NAME_ROLE: traceExit; return settingsGroup.getName();
        case Roles::MANDATORY_ROLE: traceExit; return settingsGroup.isMandatory();
        case Roles::ACTIVE_ROLE: traceExit; return settingsGroup.isActive();
        }

    } catch (settingsdialogdata::IndexOutOfBoundException& ex) {
        traceErr() << "Indice riga " << row << " non valido";
    }

    traceExit;
    return QVariant();

}

bool SettingsGroupModel::setData(const QModelIndex& index, const QVariant& value, int role) noexcept {

    traceEnter;
    if (!*this) {
        traceExit;
        return false;
    }

    if (!index.isValid()) {
        traceExit;
        return false;
    }

    int row = index.row();

    try {

        auto&& settingsGroup = container->settingsGroupAt(row);

        switch (static_cast<Roles>(role)) {
        case Roles::NAME_ROLE: return false;
        case Roles::MANDATORY_ROLE: return false;
        case Roles::ACTIVE_ROLE:
            bool active = value.value<bool>();
            settingsGroup.setActive(active);
            emit dataChanged(index, index, QVector<int>() << role);
            return true;
        }

    } catch (settingsdialogdata::IndexOutOfBoundException& ex) {
        traceErr() << "Indice riga " << row << " non valido";
    }

    traceExit;
    return false;

}

SettingsGroupContainer* SettingsGroupModel::getSettingsGroupContainer() const noexcept {
    return container;
}

void SettingsGroupModel::setSettingsGroupContainer(SettingsGroupContainer* value) noexcept {

    if (value==nullptr)
        return;

    if (*this)
        container->disconnect(this);

    container = value;

    connect(container, &SettingsGroupContainer::beforeInsertGroup, this, [=](int row) {
        this->beginInsertRows(QModelIndex(), row, row);
    });
    connect(container, &SettingsGroupContainer::afterInsertGroup, this, [=](MAYBE_UNUSED int row) {
        this->endInsertRows();
    });
    connect(container, &SettingsGroupContainer::groupChanged, this, [=](int row) {
        emit dataChanged(index(row, 0), index(row, 0));
    });
    connect(container, &SettingsGroupContainer::beforeRemoveGroup, this, [=](int row) {
        this->beginRemoveRows(QModelIndex(), row, row);
    });
    connect(container, &SettingsGroupContainer::afterRemoveGroup, this, [=](MAYBE_UNUSED int row) {
        this->endRemoveRows();
    });

}

dv::life::SettingsGroupModel::operator bool() const noexcept {
    return container != nullptr;
}



/*** SETTINGS DIALOG CTRL P ***/

SettingsDialogCtrlP::SettingsDialogCtrlP(QObject* parent) :
    QObject(parent),
    menuModel(new MenuModel(this)),
    settingsGroupModel(new SettingsGroupModel(this)), settingsGroupParametersModel() {

    /* ricordarsi di impostare il parent, altrimenti se un oggetto passa a QML, o viene
       preso dal QML attraverso un metodo INVOKABLE, l'ownership dell'oggetto passa a
       JavaScriptOwnership
       */

    traceEnter;
    traceExit;

}

SettingsDialogCtrlP::~SettingsDialogCtrlP() {

    traceEnter;
    for (auto&& item: settingsGroupParametersModel)
        delete item;
    traceExit;

}



/*** SETTINGS DIALOG CTRL ***/

SettingsDialogCtrl::SettingsDialogCtrl(QObject* parent) :
    SettingsDialogCtrl(nullptr, nullptr, parent) {

    traceEnter;
    traceExit;

}

SettingsDialogCtrl::SettingsDialogCtrl(
        MAYBE_UNUSED QQmlEngine* qmlEngine, MAYBE_UNUSED QJSEngine* jsEngine, QObject* parent) :
    BaseController(parent),
    dPtr(new SettingsDialogCtrlP()),
    data(new SettingsDialogData()) {

    traceEnter;

    dPtr->qPtr = this;

    this->initialize();
    this->setupSignalsAndSlots();

    dPtr->menuModel->setMenuContainer(&data->getMenuContainer());
    dPtr->settingsGroupModel->setSettingsGroupContainer(&data->getSettingsGroupContainer());



    traceExit;

}

SettingsDialogCtrl::~SettingsDialogCtrl() {

    traceEnter;
    delete dPtr;
    delete data;
    traceExit;

}

MenuModel* SettingsDialogCtrl::getMenuModel() noexcept {
    traceEnter;
    traceExit;
    return dPtr->menuModel.data();
}

SettingsGroupModel* SettingsDialogCtrl::getSettingsGroupModel() noexcept {

    traceEnter;
    traceExit;
    return dPtr->settingsGroupModel.data();

}

SettingsDialogData::Ptr SettingsDialogCtrl::getData() noexcept {

    traceEnter;
    traceExit;
    return data;

}

void SettingsDialogCtrl::initialize() {

    traceEnter;

    traceDebug() << "Inizializzo il menu principale";

    auto&& menuContainer = this->data->getMenuContainer();
    menuContainer.appendItem({tr("SW Settings"), "qrc:/icons/devices_other-24px.svg", true});
    menuContainer.appendItem({tr("Date/Time"), "qrc:/icons/calendar_today-24px", true});
    menuContainer.appendItem({tr("Languages"), "qrc:/icons/translate-24px.svg", true});
    menuContainer.appendItem({tr("Network"), "qrc:/icons/router-24px.svg", true});

    auto&& settingsGroupContainer = this->data->getSettingsGroupContainer();
    settingsGroupContainer.appendSettingsGroup({"Gruppo1", false, true});
    settingsGroupContainer.appendSettingsGroup({"Gruppo2", false, true});
    settingsGroupContainer.appendSettingsGroup({"Gruppo3", false, false});
    settingsGroupContainer.appendSettingsGroup({"Gruppo4", false, true});

    settingsGroupContainer.appendParameterAtGroup(0, {"P01"});
    settingsGroupContainer.appendParameterAtGroup(0, {"P02"});
    settingsGroupContainer.appendParameterAtGroup(0, {"P03"});

    settingsGroupContainer.appendParameterAtGroup(1, {"P11"});
    settingsGroupContainer.appendParameterAtGroup(1, {"P12"});
    settingsGroupContainer.appendParameterAtGroup(1, {"P13"});

    settingsGroupContainer.appendParameterAtGroup(2, {"P21"});
    settingsGroupContainer.appendParameterAtGroup(2, {"P22"});
    settingsGroupContainer.appendParameterAtGroup(2, {"P23"});

    settingsGroupContainer.appendParameterAtGroup(3, {"P31"});
    settingsGroupContainer.appendParameterAtGroup(3, {"P32"});
    settingsGroupContainer.appendParameterAtGroup(3, {"P33"});

    for (int i=0; i<data->getSettingsGroupContainer().size(); ++i) {
        SettingsGroupParametersModel::Ptr parameterModel = new SettingsGroupParametersModel(dPtr);
        parameterModel->setSettingsGroupContainerAndIndex(&data->getSettingsGroupContainer(), i);
        dPtr->settingsGroupParametersModel.append(parameterModel);
    }

    traceExit;

}

void SettingsDialogCtrl::setupSignalsAndSlots() {

    traceEnter;
    traceExit;

}

void SettingsDialogCtrl::testAdd()
{
//    data->getMenuContainer()->setItem({"Single-line item -1", "qrc:/icons/menu-24px.svg", true}, 0);
//    data->getMenuContainer()->appendItem({"Single-line item 4", "qrc:/icons/menu-24px.svg", true});
//    data->getSettingsGroupContainer().appendSettingsGroup({"Gruppo5", false, false});
    data->getSettingsGroupContainer().replaceParameterAtGroup(0, 0, {"P01b"});

}

SettingsGroupParametersModel::Ptr SettingsDialogCtrl::settingsGroupParameterModel(int index) noexcept {

    traceEnter;
    if (index<0 || index>=dPtr->settingsGroupParametersModel.size())
        return nullptr;

    traceExit;
//    return dPtr->settingsGroupParametersModel.at(index);
    return dPtr->settingsGroupParametersModel[index];

}
