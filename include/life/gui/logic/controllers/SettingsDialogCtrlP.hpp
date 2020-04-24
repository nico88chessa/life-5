#ifndef SETTINGSDIALOGCTRLP_HPP
#define SETTINGSDIALOGCTRLP_HPP

#include <configure.h>

#include <QObject>
#include <QAbstractListModel>
#include <QScopedPointer>

#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

class MenuContainer;


/*** MENU MODEL ***/

class MenuModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(MenuContainer* menuContainer READ getMenuContainer WRITE setMenuContainer NOTIFY menuContainerChanged)

    DV_DECL_POINTER_ALIAS(MenuModel)

public:
    enum class Roles : int {
        LABEL = 0,
        IMAGE,
        ENABLED
    };

private:
    MenuContainer* menuContainer;

public:
    explicit MenuModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    operator bool() const noexcept;

public slots:
    int rowCount(const QModelIndex& parent) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    QVariant data(const QModelIndex& index, int role) const override;

    MenuContainer* getMenuContainer() const;

    void setMenuContainer(MenuContainer* container);

signals:
    void menuContainerChanged();

};



class SettingsGroupContainer;

/*** SETTINGS GROUP PARAMETER MODEL ***/


/*!
   \brief The SettingsGroupParametersModel class
   Questa classe e' utilizzata per visualizzare la lista di parametri di
   configurazione del SW.
   Il modello deriva da una AbstractList, tuttavia non e' il massimo;
   valutare in futuro se utilizzare una struttura gerachica con il modello
   \c SettinsGroupModel e poi eventualmente utilizzare un FilterProxyModel
   per restringere il campo di parametri da visualizzare a seconda del
   gruppo selezionato
 */

class SettingsGroupParametersModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(SettingsGroupContainer* container READ getSettingsGroupContainer WRITE setSettingsGroupContainer)

    DV_DECL_POINTER_ALIAS(SettingsGroupParametersModel)

public:
    enum class Roles : int {
        NAME,
        VALUE,
        TYPE
    };

public:
    explicit SettingsGroupParametersModel(QObject* parent = nullptr);

    ~SettingsGroupParametersModel() {
        int i=0;
        i++;
    }

    QHash<int, QByteArray> roleNames() const noexcept;

    int rowCount(const QModelIndex& parent) const noexcept;

    QVariant data(const QModelIndex& index, int role) const noexcept;

    bool setData(const QModelIndex& index, const QVariant& value, int role) noexcept;

    void setSettingsGroupContainerAndIndex(SettingsGroupContainer* value, int groupIndex) noexcept;

    void setSettingsGroupContainer(SettingsGroupContainer* value) noexcept;

    SettingsGroupContainer* getSettingsGroupContainer() const noexcept;

    int getIndexGroup() const noexcept;

protected:
    operator bool() const noexcept;

private:
    SettingsGroupContainer* container;
    int groupIndex;

};



/*** SETTINGS GROUP MODEL ***/

class SettingsGroupModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(SettingsGroupContainer* container READ getSettingsGroupContainer WRITE setSettingsGroupContainer)

    DV_DECL_POINTER_ALIAS(SettingsGroupModel)

public:
    enum class Roles : int {
        NAME_ROLE = 0,
        MANDATORY_ROLE,
        ACTIVE_ROLE
    };

public:
    explicit SettingsGroupModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const noexcept;

    int rowCount(const QModelIndex& parent) const noexcept;

    QVariant data(const QModelIndex& index, int role) const noexcept;

    bool setData(const QModelIndex& index, const QVariant& value, int role) noexcept;

    SettingsGroupContainer* getSettingsGroupContainer() const noexcept;

    void setSettingsGroupContainer(SettingsGroupContainer* value) noexcept;

protected:
    operator bool() const noexcept;

private:
    SettingsGroupContainer* container;

signals:
    void settingsGroupContainerChanged();

};



class SettingsDialogCtrl;

/*** SETTINGS DIALOG CTRL P ***/

class SettingsDialogCtrlP: public QObject {
    Q_OBJECT

    DV_DECL_POINTER_ALIAS(SettingsDialogCtrlP)

    friend class SettingsDialogCtrl;

private:
    SettingsDialogCtrl* qPtr;
    QScopedPointer<MenuModel> menuModel;
    QScopedPointer<SettingsGroupModel> settingsGroupModel;
    QList<SettingsGroupParametersModel*> settingsGroupParametersModel;

public:
    explicit SettingsDialogCtrlP(QObject* parent = nullptr);

    virtual ~SettingsDialogCtrlP();

};

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSDIALOGCTRLP_HPP
