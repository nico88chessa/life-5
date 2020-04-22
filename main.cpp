#include <QFontDatabase>
#include <configure.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQuickControls2/QQuickStyle>

#include <life/common/logging/Logger.hpp>
#include <life/common/QtHelper.hpp>
#include <life/gui/logic/QmlHelper.hpp>



int main(MAYBE_UNUSED int argc, MAYBE_UNUSED char** argv) {

    using namespace dvlife;

    traceEnter;
    traceInfo() << "Avvio applicazione " << PROJECT_NAME;
    traceInfo() << "Versione " << PROJECT_VERSION;

    qthelper::registerMetatypes();
    qthelper::registerMetatypesStreamOperator();

    qmlhelper::registerQmlTypes();
    qmlhelper::registerQmlSingletons();
    qmlhelper::registerQmlAnonymousTypes();
    qmlhelper::registerQmlUncreatableTypes();
    qmlhelper::registerMetaTypes();

    QGuiApplication app(argc, argv);
    app.setAttribute(Qt::AA_EnableHighDpiScaling);

    qmlhelper::addCustomFonts();
    auto fam = QFontDatabase().families();

    QQmlApplicationEngine engine;
    auto currentList = engine.importPathList();

    engine.addImportPath("./qml-plugin/");
//    engine.addImportPath("qrc:/qml/");
//    engine.addImportPath(":/qml/");
//    engine.addImportPath("qrc:/qml/settingsDialogParts/");
//    engine.addImportPath(":/qml/settingsDialogParts/");
    currentList = engine.importPathList();
    engine.load(QUrl(QStringLiteral("qrc:/qml/MainWindow.qml")));

    return app.exec();
    traceExit;

}
