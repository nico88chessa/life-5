#ifndef SETTINGSCTRLPRIVATE_HPP
#define SETTINGSCTRLPRIVATE_HPP

#include <configure.h>

#include <QAbstractItemModel>
#include <QObject>

#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

class SettingsCtrl;

class SettingsCtrlPrivate : public QObject {
    Q_OBJECT

    friend class SettingsCtrl;

public:
    DV_DECL_POINTER_ALIAS(SettingsCtrlPrivate)

private:
    SettingsCtrl* qPtr;

public:
    explicit SettingsCtrlPrivate();

};

DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSCTRLPRIVATE_HPP
