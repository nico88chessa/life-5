#ifndef QMLBASECONTROLLER_HPP
#define QMLBASECONTROLLER_HPP

#include <configure.h>

#include <QObject>
#include <QQmlEngine>

#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

class QmlBaseController : public QObject {
    Q_OBJECT

public:
    DV_DECL_POINTER_ALIAS(QmlBaseController)

protected:
    /* NOTE NIC 09/04/2020: QQmlEngine, QJSEngine
     * non so a cosa servono e/o possono essere utili;
     * intanto li tengo;
     */
    QQmlEngine* qmlEngine;
    QJSEngine* jsEngine;


public:
    explicit QmlBaseController(QObject* parent = nullptr) :
        QmlBaseController(nullptr, nullptr, parent) { }

    explicit QmlBaseController(QQmlEngine* qmlEngine,
                     QJSEngine* jsEngine,
                     QObject* parent = nullptr) :
        QObject(parent), qmlEngine(qmlEngine), jsEngine(jsEngine) { }

    virtual ~QmlBaseController() { }

};

DV_LIFE_CLOSE_NAMESPACE

#endif // QMLBASECONTROLLER_HPP
