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


DV_LIFE_OPEN_NAMESPACE

namespace qthelper {

//static constexpr char DV_QML_URI[] = "dv.life";
static constexpr char DV_QML_URI_CONTROLLERS[] = "dv.life.controllers";
static constexpr char DV_QML_URI_DATA[] = "dv.life.data";
static constexpr char DV_QML_URI_CONTROLS[] = "theme.controls";

void registerQmlSingletons() {

    traceEnter;

    int qmlTypeId = qmlRegisterSingletonType<MainWindowCtrl>(DV_QML_URI_CONTROLLERS, 1, 0, "MainwindowCtrl",
                                                               [](QQmlEngine* qmlEngine, QJSEngine* jsEngine) -> QObject* {
                return FactoryQml::instance().getInstance<MainWindowCtrl>(qmlEngine, jsEngine); }
                );
    traceDebug() << "MainWindowCtrl QML TypeId: " << qmlTypeId;

//    qmlTypeId = qmlRegisterSingletonType<ThemeConstants>(DV_QML_URI_THEME, 1, 0, "ThemeConstants",
//                                                               [](QQmlEngine* qmlEngine, QJSEngine* jsEngine) -> QObject* {
//                return FactoryQml::instance().getInstance<ThemeConstants>(qmlEngine, jsEngine); }
//                );
//    traceDebug() << "ThemeConstants QML TypeId: " << qmlTypeId;

    traceExit;

}

void registerQmlType() {

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

#if QT_VERSION < QT_VERSION_CHECK(5, 15, 0)
    int qmlTypeId = qmlRegisterType<dvlife::MainWindowData>();
    traceDebug() << "MainWindowData QML TypeId: " << qmlTypeId;
#else
    int qmlTypeId = qmlRegisterAnonymousType<dvlife::MainwindowData>(dvlife::DV_LIFE_QML_DATA_NAMESPACE, 1, 0);
    traceDebug() << "MainwindowData QML TypeId: " << qmlTypeId;
#endif

    traceExit;

}

void registerQmlUncreatableType() {

    traceEnter;
//    int qmlTypeId = qmlRegisterUncreatableType<DVTheme>(DV_QML_URI_THEME, 1, 0, "DVTheme", "DVTheme is an attached property");
//    traceDebug() << "DVTheme QML TypeId: " << qmlTypeId;

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
