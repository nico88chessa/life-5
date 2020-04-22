#ifndef SETTINGSDIALOGCTRLP_HPP
#define SETTINGSDIALOGCTRLP_HPP

#include <configure.h>

#include <QObject>
#include <QAbstractListModel>
#include <QScopedPointer>

#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

class MenuContainer;

class MenuModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(MenuContainer* menuContainer READ getMenuContainer WRITE setMenuContainer NOTIFY menuContainerChanged)

    DV_DECL_POINTER_ALIAS(MenuModel)

public:
    enum class MENU_ROLES : int {
        LABEL = 0,
        IMAGE,
        ENABLED
    };

private:
    MenuContainer* menuContainer;

public:
    explicit MenuModel(QObject* parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;

    operator bool() const { return menuContainer != nullptr; }

public slots:
    int rowCount(const QModelIndex& parent) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    QVariant data(const QModelIndex& index, int role) const override;

    MenuContainer* getMenuContainer() const;

    void setMenuContainer(MenuContainer* container);

signals:
    void menuContainerChanged();

};



class SettingsDialogCtrl;

class SettingsDialogCtrlP: public QObject {
    Q_OBJECT

    DV_DECL_POINTER_ALIAS(SettingsDialogCtrlP)

    friend class SettingsDialogCtrl;

private:
    SettingsDialogCtrl* qPtr;
    QScopedPointer<MenuModel> menuModel;

public:
    explicit SettingsDialogCtrlP(QObject* parent = nullptr);
    virtual ~SettingsDialogCtrlP();

};

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSDIALOGCTRLP_HPP
