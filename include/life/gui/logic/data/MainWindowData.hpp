#ifndef MAINWINDOWDATA_HPP
#define MAINWINDOWDATA_HPP

#include <configure.h>

#include <QObject>

#include <life/common/logging/Logger.hpp>
#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

class MainWindowData : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString pApplicationName READ getApplicationName CONSTANT)

    DV_DECL_POINTER_ALIAS(MainWindowData)

private:
    QString applicationName;

public:
    explicit MainWindowData(QObject* parent = nullptr) :
        QObject(parent),
        applicationName(dvlife::PROJECT_UI_NAME) {

        traceEnter;
        traceExit;
    }

    ~MainWindowData() {
        traceEnter;
        traceExit;
    }

    QString getApplicationName() const {
        return applicationName;
    }

};

DV_LIFE_CLOSE_NAMESPACE

#endif // MAINWINDOWDATA_HPP
