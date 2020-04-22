#ifndef QMLHELPER_HPP
#define QMLHELPER_HPP

#include <configure.h>

#include <initializer_list>

#include <QFontDatabase>
#include <QUrl>
#include <QQmlEngine>

#include <life/common/logging/Logger.hpp>
#include <life/common/Constants.hpp>
#include <life/gui/logic/FactoryQml.hpp>
#include <life/gui/logic/controllers/MainWindowCtrl.hpp>
#include <life/gui/logic/data/MainWindowData.hpp>
#include <life/gui/logic/data/SettingsDialogData.hpp>
#include <life/gui/logic/controllers/SettingsDialogCtrl.hpp>
#include <life/gui/logic/controllers/SettingsDialogCtrlP.hpp>


DV_LIFE_OPEN_NAMESPACE

namespace qmlhelper {

//static constexpr char DV_QML_URI[] = "dv.life";
static constexpr char DV_QML_URI_CONTROLLERS[] = "dv.life.controllers";
static constexpr char DV_QML_URI_DATA[] = "dv.life.data";
static constexpr char DV_QML_URI_CONTROLS[] = "theme.controls";

void registerQmlSingletons() {

    traceEnter;

    int qmlTypeId;

    qmlTypeId = qmlRegisterSingletonType<MainWindowCtrl>(DV_QML_URI_CONTROLLERS, 1, 0, "MainwindowCtrl",
                                                               [](QQmlEngine* qmlEngine, QJSEngine* jsEngine) -> QObject* {
                return FactoryQml::instance().getInstance<MainWindowCtrl>(qmlEngine, jsEngine); }
                );
    traceDebug() << "MainWindowCtrl QML TypeId: " << qmlTypeId;

    qmlTypeId = qmlRegisterSingletonType<SettingsDialogCtrl>(DV_QML_URI_CONTROLLERS, 1, 0, "SettingsDialogCtrl",
                                                               [](QQmlEngine* qmlEngine, QJSEngine* jsEngine) -> QObject* {
                return FactoryQml::instance().getInstance<SettingsDialogCtrl>(qmlEngine, jsEngine); }
                );
    traceDebug() << "SettingsDialogCtrl QML TypeId: " << qmlTypeId;

    traceExit;

}

void registerQmlTypes() {

    traceEnter;
//    int qmlTypeId = qmlRegisterType(QUrl("qrc:/qml/theme/controls/AppBar.qml"), DV_QML_URI_CONTROLS, 1, 0, "AppBar");
//    traceDebug() << "MainWindowData QML TypeId: " << qmlTypeId;
    traceExit;

}

void registerQmlAnonymousTypes() {

    traceEnter;

    /* Note NIC 10/04/2020: register QML anonymous types
     * vedere con le Qt 5.15 se va bene sta cosa
     */

    int qmlTypeId;

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    qmlTypeId = qmlRegisterType<dv::life::MainWindowData>();
    traceDebug() << "MainWindowData QML TypeId: " << qmlTypeId;
    qmlTypeId = qmlRegisterType<dv::life::SettingsDialogData>();
    traceDebug() << "SettingsDialogData QML TypeId: " << qmlTypeId;
    qmlTypeId = qmlRegisterType<dv::life::MenuModel>();
    traceDebug() << "MenuModel QML TypeId: " << qmlTypeId;
//    qmlTypeId = qmlRegisterType<dvlife::MenuModel*>();
//    traceDebug() << "MenuModel* QML TypeId: " << qmlTypeId;
#else
    qmlTypeId = qmlRegisterAnonymousType<dvlife::MainwindowData>(dvlife::DV_LIFE_QML_DATA_NAMESPACE, 1, 0);
    traceDebug() << "MainwindowData QML TypeId: " << qmlTypeId;
    qmlTypeId = qmlRegisterAnonymousType<dvlife::SettingsDialogData>(dvlife::DV_LIFE_QML_DATA_NAMESPACE, 1, 0);
    traceDebug() << "SettingsDialogData QML TypeId: " << qmlTypeId;
#endif

    traceExit;

}

void registerQmlUncreatableTypes() {

    traceEnter;
    int qmlTypeId;
//    qmlTypeId = qmlRegisterUncreatableType<MenuContainer>(DV_QML_URI_CONTROLLERS, 1, 0, "MenuContainer", "MenuContainer should not be created in QML");
//    traceDebug() << "MenuContainer TypeId: " << qmlTypeId;
//    qmlTypeId = qmlRegisterUncreatableType<DVTheme>(DV_QML_URI_THEME, 1, 0, "DVTheme", "DVTheme is an attached property");
//    traceDebug() << "DVTheme QML TypeId: " << qmlTypeId;

    traceExit;

}

void registerMetaTypes() {

    traceEnter;
    int qmlTypeId;

    // NOTE NIC 22/04/2020: non si capisce perche' devo registrare il puntatore in questo modo;
    // vedere link forum qml: https://forum.qt.io/topic/113897/qml-c-exposing-pointer-type-attribute-to-qml
    qmlTypeId = qRegisterMetaType<dv::life::MenuModel*>("MenuModel*");
    traceDebug() << "MenuModel* QML TypeId: " << qmlTypeId;

    traceExit;
}

void addCustomFonts() {

    traceEnter;

    std::initializer_list<std::string> fonts = {
        ":/fonts/Roboto-Black.ttf",
        ":/fonts/Roboto-BlackItalic.ttf",
        ":/fonts/Roboto-Bold.ttf",
        ":/fonts/Roboto-BoldItalic.ttf",
        ":/fonts/Roboto-Italic.ttf",
        ":/fonts/Roboto-Light.ttf",
        ":/fonts/Roboto-LightItalic.ttf",
        ":/fonts/Roboto-Medium.ttf",
        ":/fonts/Roboto-MediumItalic.ttf",
        ":/fonts/Roboto-Regular.ttf",
        ":/fonts/Roboto-Thin.ttf",
        ":/fonts/Roboto-ThinItalic.ttf",
    };

    int id;
    for (auto&& f: fonts) {
        id = QFontDatabase::addApplicationFont(QString::fromStdString(f));
        if (id < 0)
            traceErr() << "Impossibile caricare il font " << f;
        else
            ++id;
    }

    traceDebug() << "Caricati" << id << " fonts Roboto";

    traceExit;
}

}

DV_LIFE_CLOSE_NAMESPACE

#endif // QMLHELPER_HPP
