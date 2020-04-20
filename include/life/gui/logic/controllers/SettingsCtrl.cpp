#include "SettingsCtrlPrivate.hpp"
#include "SettingsCtrl.hpp"

#include <life/common/logging/Logger.hpp>


using namespace dvlife;

/*** SETTINGS CONTROLLER PRIVATE ***/

SettingsCtrlPrivate::SettingsCtrlPrivate() {

    traceEnter;
    traceExit;

}



/*** SETTINGS CONTROLLER ***/

SettingsCtrl::SettingsCtrl(QObject* parent) :
    SettingsCtrl(nullptr, nullptr, parent) {

    traceEnter;
    traceExit;

}

SettingsCtrl::SettingsCtrl(MAYBE_UNUSED QQmlEngine* qmlEngine, MAYBE_UNUSED QJSEngine* jsEngine, QObject* parent) :
    BaseController(parent), dPtr(new SettingsCtrlPrivate()), data(this) {

    traceEnter;
    dPtr->qPtr = this;
    traceExit;

}

SettingsCtrl::~SettingsCtrl() {

    traceEnter;
    delete dPtr;
    traceExit;

}

SettingsData::Ptr SettingsCtrl::getData() {

    traceEnter;
    traceExit;
    return &this->data;

}
