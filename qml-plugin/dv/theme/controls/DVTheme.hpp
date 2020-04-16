#ifndef DVTHEME_HPP
#define DVTHEME_HPP

#include <QObject>
#include <QQmlEngine>
#include <QColor>

static constexpr qreal ALPHA_FOCUS = 0.24;
static constexpr qreal ALPHA_HOVER = 0.08;
static constexpr qreal ALPHA_SELECTED = 0.16;
static constexpr qreal ALPHA_ACTIVATED = 0.24;
static constexpr qreal ALPHA_PRESSED = 0.32;
static constexpr qreal ALPHA_DRAGGED = 0.16;

//QColor getHover(const QColor& other) {
//    QColor newColor(other);
//    newColor.setAlphaF(ALPHA_FOCUS);
//    return newColor;
//}
//QColor getFocus(const QColor& other) {
//    QColor newColor(other);
//    newColor.setAlphaF(ALPHA_HOVER);
//    return newColor;
//}
//QColor getSelected(const QColor& other) {
//    QColor newColor(other);
//    newColor.setAlphaF(ALPHA_SELECTED);
//    return newColor;
//}
//QColor getActivated(const QColor& other) {
//    QColor newColor(other);
//    newColor.setAlphaF(ALPHA_ACTIVATED);
//    return newColor;
//}
//QColor getPressed(const QColor& other) {
//    QColor newColor(other);
//    newColor.setAlphaF(ALPHA_PRESSED);
//    return newColor;
//}
//QColor getDragged(const QColor& other) {
//    QColor newColor(other);
//    newColor.setAlphaF(ALPHA_DRAGGED);
//    return newColor;
//}


//QColor getPrimaryHover(const QColor& other);
//QColor getPrimaryFocus(const QColor& other);
//QColor getPrimarySelected(const QColor& other);
//QColor getPrimaryActivated(const QColor& other);
//QColor getPrimaryPressed(const QColor& other);
//QColor getPrimaryDragged(const QColor& other);

//QColor getPrimaryHoverOnWhiteSurface(const QColor& other);
//QColor getPrimaryFocusOnWhiteSurface(const QColor& other);
//QColor getPrimarySelectedOnWhiteSurface(const QColor& other);
//QColor getPrimaryActivatedOnWhiteSurface(const QColor& other);
//QColor getPrimaryPressedOnWhiteSurface(const QColor& other);
//QColor getPrimaryDraggedOnWhiteSurface(const QColor& other);

class DVTheme : public QObject {
    Q_OBJECT

private:


public:
    explicit DVTheme(QObject* parent = nullptr);

    static DVTheme* qmlAttachedProperties(QObject* object);

};

QML_DECLARE_TYPEINFO(DVTheme, QML_HAS_ATTACHED_PROPERTIES)

#endif // DVTHEME_HPP
