#ifndef SETTINGSCTRL_HPP
#define SETTINGSCTRL_HPP

#include <configure.h>

#include <life/common/MacroUtils.hpp>
#include <life/gui/logic/BaseController.hpp>
#include <life/gui/logic/data/SettingsData.hpp>


DV_LIFE_OPEN_NAMESPACE

class SettingsCtrlPrivate;

class SettingsCtrl : public BaseController {
    Q_OBJECT
    Q_PROPERTY(SettingsData* data READ getData)

    friend class SettingsCtrlPrivate;

public:
    DV_DECL_POINTER_ALIAS(SettingsCtrl)

private:
    SettingsCtrlPrivate* dPtr;
    SettingsData data;

public:
    explicit SettingsCtrl(QObject* parent = nullptr);
    explicit SettingsCtrl(QQmlEngine* qmlEngine,
                       QJSEngine* jsEngine,
                       QObject* parent = nullptr);
    ~SettingsCtrl();

    SettingsData::Ptr getData();

};

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSCTRL_HPP
