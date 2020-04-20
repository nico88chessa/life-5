#include "DVThemeControlsPlugin.hpp"

#include <QQmlEngine>
#include <QScopedPointer>

#include <DVTheme.hpp>
#include <ThemeConstants.hpp>


DVThemeControlsPlugin::DVThemeControlsPlugin() { }

void DVThemeControlsPlugin::registerTypes(const char* uri) {

//    Q_ASSERT(uri == QLatin1String("DVTheme"));

//    QByteArray import = QByteArray(uri) + ".impl";
    int qmlTypeId;
    qmlTypeId = qmlRegisterUncreatableType<DVTheme>(uri, 1, 0, "DVTheme", "DVTheme is an attached property");

    qmlTypeId = qmlRegisterSingletonType<ThemeConstants>(uri, 1, 0, "ThemeConstants",
                                                         [](QQmlEngine* qmlEngine, QJSEngine* jsEngine) -> QObject* {

                static QScopedPointer<ThemeConstants> instance;

                if (!instance) {
                    instance.reset(new ThemeConstants()); // qui inizializzo l'oggetto di tipo T la prima volta sola
                    qmlEngine->setObjectOwnership(instance.data(), QQmlEngine::CppOwnership);
                }
                return instance.data();
    });

}
