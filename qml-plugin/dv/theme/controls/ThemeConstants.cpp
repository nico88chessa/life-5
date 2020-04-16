#include "ThemeConstants.hpp"


ThemeConstants::ThemeConstants(QObject* parent) : QObject(parent),
    font("Roboto"),
    fontColor(QColor(QStringLiteral("#FFFFFF"))),
    primary(QColor(QStringLiteral("#1A3C6F"))),
    primaryLight(QColor(QStringLiteral("#4D669E"))),
    primaryDark(QColor(QStringLiteral("#001743"))),
    secondary(QColor(QStringLiteral("#F48904"))),
    secondaryLight(QColor(QStringLiteral("#FFBA45"))),
    secondaryDark(QColor(QStringLiteral("#BB5B00"))) {

}

QString ThemeConstants::getFont() const { return font; }

QColor ThemeConstants::getFontColor() const { return fontColor; }

QColor ThemeConstants::getPrimary() const { return primary; }

QColor ThemeConstants::getPrimaryLight() const { return primaryLight; }

QColor ThemeConstants::getPrimaryDark() const { return primaryDark; }

QColor ThemeConstants::getSecondary() const { return secondary; }

QColor ThemeConstants::getSecondaryLight() const { return secondaryLight; }

QColor ThemeConstants::getSecondaryDark() const { return secondaryDark; }
