#include "ThemeConstants.hpp"

#include <QColor>


static constexpr QRgb rgba2Hex(int r, int g, int b, int a = 255) {
    int rgba = 0;
    rgba |= b << 0;
    rgba |= g << 8;
    rgba |= r << 16;
    rgba |= a << 24;
    return rgba;
}


/*
Primary #1A3C6F rgb(26, 60, 111)
PrimaryLight #4D669F rgb(77, 102, 159)
PrimaryDark #001744 rgb(0, 23, 68)

Secondary #F48903 rgb(244, 137, 4)
SecondaryLight #FFBA45 rgb(255, 186, 69)
SecondaryDark #BB5B00 rgb(187, 91, 0)
*/

ThemeConstants::ThemeConstants(QObject* parent) : QObject(parent),
    font("Roboto"),
    primary(rgba2Hex(26, 60, 111)),
    primaryLight(rgba2Hex(77, 102, 159)),
    primaryDark(rgba2Hex(0, 23, 68)),
    secondary(rgba2Hex(244, 137, 4)),
    secondaryLight(rgba2Hex(255, 186, 69)),
    secondaryDark(rgba2Hex(187, 91, 0)),
    foregroundOnPrimary(rgba2Hex(255, 255, 255)),
    foregroundOnPrimaryLight(rgba2Hex(255, 255, 255)),
    foregroundOnPrimaryDark(rgba2Hex(255, 255, 255)),
    foregroundOnSecondary(rgba2Hex(0, 0, 0)),
    foregroundOnSecondaryLight(rgba2Hex(0, 0, 0)),
    foregroundOnSecondaryDark(rgba2Hex(255, 255, 255)),
    background(rgba2Hex(255, 255, 255)),
    foreground(rgba2Hex(0, 0, 0)),
    textHighEmphasis(QColor::fromRgba(rgba2Hex(0, 0, 0, 222))), // 255 * 0.87 (https://material.io/design/color/text-legibility.html#text-backgrounds)
    textMediumEmphasis(QColor::fromRgba(rgba2Hex(0, 0, 0, 153))), // 255 * 0.60
    textDisabled(QColor::fromRgba(rgba2Hex(0, 0, 0, 97))), //  255 * 0.38
    controlActive(QColor::fromRgba(rgba2Hex(0, 0, 0, 222))), // 255 * 0.87 (https://material.io/design/color/text-legibility.html#text-types)
    controlInactive(QColor::fromRgba(rgba2Hex(0, 0, 0, 153))), //  255 * 0.60
    controlDisabled(QColor::fromRgba(rgba2Hex(0, 0, 0, 97))), // 255 * 0.38
    overlayLight(rgba2Hex(0, 0, 0)),
    overlayDark(rgba2Hex(255, 255, 255)),
    inactive(QColor::fromRgba(rgba2Hex(0, 0, 0, 66))),  // opacity 66 = 255 * 0.26
    disabled(QColor::fromRgba(rgba2Hex(0, 0, 0, 31))) // opacity 31 = 255 * 0.12
{

}

QString ThemeConstants::getFont() const { return font; }

QColor ThemeConstants::getPrimary() const { return primary; }

QColor ThemeConstants::getPrimaryLight() const { return primaryLight; }

QColor ThemeConstants::getPrimaryDark() const { return primaryDark; }

QColor ThemeConstants::getSecondary() const { return secondary; }

QColor ThemeConstants::getSecondaryLight() const { return secondaryLight; }

QColor ThemeConstants::getSecondaryDark() const { return secondaryDark; }

QColor ThemeConstants::getForegroundOnPrimary() const { return foregroundOnPrimary; }

QColor ThemeConstants::getForegroundOnPrimaryLight() const { return foregroundOnPrimaryLight; }

QColor ThemeConstants::getForegroundOnPrimaryDark() const { return foregroundOnPrimaryDark; }

QColor ThemeConstants::getForegroundOnSecondary() const { return foregroundOnSecondary; }

QColor ThemeConstants::getForegroundOnSecondaryLight() const { return foregroundOnSecondaryLight; }

QColor ThemeConstants::getForegroundOnSecondaryDark() const { return foregroundOnSecondaryDark; }

QColor ThemeConstants::getBackground() const { return background; }

QColor ThemeConstants::getForeground() const { return foreground; }

QColor ThemeConstants::getTextHighEmphasis() const { return textHighEmphasis; }

QColor ThemeConstants::getTextMediumEmphasis() const { return textMediumEmphasis; }

QColor ThemeConstants::getTextDisabled() const { return textDisabled; }

QColor ThemeConstants::getControlActive() const { return controlActive; }

QColor ThemeConstants::getControlInactive() const { return controlInactive; }

QColor ThemeConstants::getControlDisabled() const { return controlDisabled; }

QColor ThemeConstants::getOverlayLight() const { return overlayLight; }

QColor ThemeConstants::getOverlayDark() const { return overlayDark; }

QColor ThemeConstants::getInactive() const { return inactive; }

QColor ThemeConstants::getDisabled() const { return disabled; }
