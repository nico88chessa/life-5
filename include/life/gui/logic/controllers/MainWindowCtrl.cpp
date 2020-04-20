#include <life/gui/logic/controllers/MainWindowCtrl.hpp>

#include <life/common/logging/Logger.hpp>
#include <life/gui/logic/FactoryQml.hpp>


using namespace dvlife;

MainWindowCtrl::MainWindowCtrl(QObject *parent) :
    MainWindowCtrl(nullptr, nullptr, parent) {

    traceEnter;
    traceExit;

}

MainWindowCtrl::MainWindowCtrl(MAYBE_UNUSED QQmlEngine* qmlEngine, MAYBE_UNUSED QJSEngine* jsEngine,
                     QObject* parent) :
    BaseController(qmlEngine, jsEngine, parent),
    data(new MainWindowData()) {

    traceEnter;
    traceExit;

}

MainWindowCtrl::~MainWindowCtrl() {

    traceEnter;
    traceExit;

}

MainWindowData* MainWindowCtrl::getData() {

    traceEnter;
    traceExit;
    return data.get();

}
