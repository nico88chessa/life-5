#ifndef DVTHEMEPLUGIN_HPP
#define DVTHEMEPLUGIN_HPP


#include <QQmlExtensionPlugin>


class DVThemeControlsPlugin : public QQmlExtensionPlugin {

    Q_OBJECT
    Q_PLUGIN_METADATA(IID "dv.theme.controls/1.0")

public:
    DVThemeControlsPlugin();

    virtual void registerTypes(const char* uri) override;

};

#endif // DVTHEMEPLUGIN_HPP
