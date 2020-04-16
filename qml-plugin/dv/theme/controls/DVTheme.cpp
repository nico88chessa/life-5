#include "DVTheme.hpp"



DVTheme::DVTheme(QObject* parent) : QObject(parent) {

}

DVTheme* DVTheme::qmlAttachedProperties(QObject* object) {
    return new DVTheme(object);
}

