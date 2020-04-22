#ifndef MAINWINDOWCTRL_HPP
#define MAINWINDOWCTRL_HPP

#include <configure.h>

#include <QScopedPointer>

#include <life/gui/logic/BaseController.hpp>
#include <life/gui/logic/data/MainWindowData.hpp>


DV_LIFE_OPEN_NAMESPACE

class MainWindowCtrl : public BaseController {
    Q_OBJECT
    Q_PROPERTY(MainWindowData* pData READ getData CONSTANT FINAL)

    DV_DECL_POINTER_ALIAS(MainWindowCtrl)

private:
    QScopedPointer<MainWindowData> data;
    int test;

public:
    explicit MainWindowCtrl(QObject *parent = nullptr);
    explicit MainWindowCtrl(QQmlEngine* qmlEngine,
                       QJSEngine* jsEngine,
                       QObject* parent = nullptr);
    ~MainWindowCtrl();

    MainWindowData* getData();

public slots:
    void calledTest() {
        traceEnter;
        traceExit;
    }

};

DV_LIFE_CLOSE_NAMESPACE

#endif // MAINWINDOWCTRL_HPP
