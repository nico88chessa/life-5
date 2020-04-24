#ifndef SETTINGSDIALOGCTRL_HPP
#define SETTINGSDIALOGCTRL_HPP

#include <configure.h>

#include <life/common/MacroUtils.hpp>
#include <life/gui/logic/BaseController.hpp>

#include <QAbstractListModel>


DV_LIFE_OPEN_NAMESPACE

class SettingsDialogCtrlP;
class SettingsDialogData;
class MenuModel;
class SettingsGroupParametersModel;
class SettingsGroupModel;

class SettingsDialogCtrl : public BaseController {
    Q_OBJECT
    Q_PROPERTY(SettingsDialogData* data READ getData CONSTANT)
    Q_PROPERTY(MenuModel* menuModel READ getMenuModel)
    Q_PROPERTY(SettingsGroupModel* settingsGroupModel READ getSettingsGroupModel)

    DV_DECL_POINTER_ALIAS(SettingsDialogCtrl)

    friend class SettingsDialogCtrlP;

private:
    SettingsDialogCtrlP* dPtr;
    SettingsDialogData* data;

public:
    explicit SettingsDialogCtrl(QObject* parent = nullptr);

    explicit SettingsDialogCtrl(QQmlEngine* qmlEngine,
                       QJSEngine* jsEngine,
                       QObject* parent = nullptr);

    ~SettingsDialogCtrl();

    SettingsDialogData* getData() noexcept;

    MenuModel* getMenuModel() noexcept;

    SettingsGroupModel* getSettingsGroupModel() noexcept;

private:
    void initialize();

    void setupSignalsAndSlots();

public slots:
    void testAdd();

    SettingsGroupParametersModel* settingsGroupParameterModel(int index) noexcept;

};

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSDIALOGCTRL_HPP
