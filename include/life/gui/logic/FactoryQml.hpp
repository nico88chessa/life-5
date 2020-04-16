#ifndef FACTORYQML_HPP
#define FACTORYQML_HPP

#include <configure.h>

#include <type_traits>

#include <QObject>
#include <QScopedPointer>
#include <QQmlEngine>

#include <life/common/logging/Logger.hpp>


DV_LIFE_OPEN_NAMESPACE

template<typename T>
struct hasQMLEngineConstructor {
    static constexpr bool value = std::is_constructible_v<T, QQmlEngine*, QJSEngine*>;
};



class FactoryQml {
private:
    FactoryQml() { }
    Q_DISABLE_COPY(FactoryQml)

public:
    static FactoryQml& instance() {
        static FactoryQml instance;
        return instance;
    }

    // metodo chiamato se al costruttore di T posso passare (QQmlEngine*, QJSEngine*)
    template <typename T, std::enable_if_t<hasQMLEngineConstructor<T>::value, int> = 0 >
    QObject* getInstance(MAYBE_UNUSED QQmlEngine* qmlEngine, MAYBE_UNUSED QJSEngine* jsEngine) {

        traceEnter;

        static QScopedPointer<T> instance;

        if (!instance) {
            instance.reset(new T(qmlEngine, jsEngine)); // qui inizializzo l'oggetto di tipo T la prima volta sola
            qmlEngine->setObjectOwnership(instance.data(), QQmlEngine::CppOwnership);
        }

        traceExit;
        return instance.data();

    }

    // metodo chiamato se al costruttore di T NON posso passare (QQmlEngine*, QJSEngine*)
    template <typename T, std::enable_if_t<!hasQMLEngineConstructor<T>::value, int> = 0 >
    QObject* getInstance(MAYBE_UNUSED QQmlEngine* qmlEngine, MAYBE_UNUSED QJSEngine* jsEngine) {

        traceEnter;

        static QScopedPointer<T> instance;

        if (!instance){
            instance.reset(new T()); // qui inizializzo l'oggetto di tipo T la prima volta sola
            qmlEngine->setObjectOwnership(instance.data(), QQmlEngine::CppOwnership);
        }

        traceExit;
        return instance.data();

    }

};

DV_LIFE_CLOSE_NAMESPACE

#endif // FACTORYQML_HPP
