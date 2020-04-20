#ifndef BASECONTROLLER_HPP
#define BASECONTROLLER_HPP

#include <configure.h>

#include <QObject>
#include <QQmlEngine>

#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

class BaseController : public QObject {
    Q_OBJECT

public:
    DV_DECL_POINTER_ALIAS(BaseController)

protected:
    /* NOTE NIC 09/04/2020: QQmlEngine, QJSEngine
     * non so a cosa servono e/o possono essere utili;
     * intanto li tengo;
     */
    QQmlEngine* qmlEngine;
    QJSEngine* jsEngine;


public:
    explicit BaseController(QObject* parent = nullptr) :
        BaseController(nullptr, nullptr, parent) { }

    explicit BaseController(QQmlEngine* qmlEngine,
                     QJSEngine* jsEngine,
                     QObject* parent = nullptr) :
        QObject(parent), qmlEngine(qmlEngine), jsEngine(jsEngine) { }

    virtual ~BaseController() { }

};

DV_LIFE_CLOSE_NAMESPACE

#endif // BASECONTROLLER_HPP
