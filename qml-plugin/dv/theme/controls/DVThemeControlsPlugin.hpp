#ifndef DVTHEMEPLUGIN_HPP
#define DVTHEMEPLUGIN_HPP


#include <QQmlExtensionPlugin>


class DVThemeControlsPlugin : public QQmlExtensionPlugin {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "dv.theme.controls/1.0")

public:
    DVThemeControlsPlugin();

    void registerTypes(const char* uri);

};

#endif // DVTHEMEPLUGIN_HPP
