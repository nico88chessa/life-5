#ifndef THEMECONSTANTS_HPP
#define THEMECONSTANTS_HPP

#include <QObject>
#include <QColor>


class ThemeConstants : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString font READ getFont CONSTANT)
    Q_PROPERTY(QColor primary READ getPrimary CONSTANT)
    Q_PROPERTY(QColor primaryLight READ getPrimaryLight CONSTANT)
    Q_PROPERTY(QColor primaryDark READ getPrimaryDark CONSTANT)
    Q_PROPERTY(QColor secondary READ getSecondary CONSTANT)
    Q_PROPERTY(QColor secondaryLight READ getSecondaryLight CONSTANT)
    Q_PROPERTY(QColor secondaryDark READ getSecondaryDark CONSTANT)

    Q_PROPERTY(QColor foregroundOnPrimary READ getForegroundOnPrimary CONSTANT)
    Q_PROPERTY(QColor foregroundOnPrimaryLight READ getForegroundOnPrimaryLight CONSTANT)
    Q_PROPERTY(QColor foregroundOnPrimaryDark READ getForegroundOnPrimaryDark CONSTANT)
    Q_PROPERTY(QColor foregroundOnSecondary READ getForegroundOnSecondary CONSTANT)
    Q_PROPERTY(QColor foregroundOnSecondaryLight READ getForegroundOnSecondaryLight CONSTANT)
    Q_PROPERTY(QColor foregroundOnSecondaryDark READ getForegroundOnSecondaryDark CONSTANT)

    Q_PROPERTY(QColor background READ getBackground CONSTANT)
    Q_PROPERTY(QColor foreground READ getForeground CONSTANT)

    Q_PROPERTY(QColor textHighEmphasis READ getTextHighEmphasis CONSTANT)
    Q_PROPERTY(QColor textMediumEmphasis READ getTextMediumEmphasis CONSTANT)
    Q_PROPERTY(QColor textDisabled READ getTextDisabled CONSTANT)

    Q_PROPERTY(QColor controlActive READ getControlActive CONSTANT)
    Q_PROPERTY(QColor controlInactive READ getControlInactive CONSTANT)
    Q_PROPERTY(QColor controlDisabled READ getControlDisabled CONSTANT)

    Q_PROPERTY(QColor overlayLight READ getOverlayLight CONSTANT)
    Q_PROPERTY(QColor overlayDark READ getOverlayDark CONSTANT)

    Q_PROPERTY(QColor inactive READ getInactive CONSTANT)
    Q_PROPERTY(QColor disabled READ getDisabled CONSTANT)

private:
    QString font;

    QColor primary;
    QColor primaryLight;
    QColor primaryDark;
    QColor secondary;
    QColor secondaryLight;
    QColor secondaryDark;

    QColor foregroundOnPrimary;
    QColor foregroundOnPrimaryLight;
    QColor foregroundOnPrimaryDark;
    QColor foregroundOnSecondary;
    QColor foregroundOnSecondaryLight;
    QColor foregroundOnSecondaryDark;

    QColor background;
    QColor foreground;

    QColor textHighEmphasis;
    QColor textMediumEmphasis;
    QColor textDisabled;

    QColor controlActive;
    QColor controlInactive;
    QColor controlDisabled;

    QColor overlayLight;
    QColor overlayDark;

    QColor inactive;
    QColor disabled;

public:
    explicit ThemeConstants(QObject* parent = nullptr);

public slots:
    QString getFont() const;

    QColor getPrimary() const;
    QColor getPrimaryLight() const;
    QColor getPrimaryDark() const;
    QColor getSecondary() const;
    QColor getSecondaryLight() const;
    QColor getSecondaryDark() const;

    QColor getForegroundOnPrimary() const;
    QColor getForegroundOnPrimaryLight() const;
    QColor getForegroundOnPrimaryDark() const;
    QColor getForegroundOnSecondary() const;
    QColor getForegroundOnSecondaryLight() const;
    QColor getForegroundOnSecondaryDark() const;

    QColor getBackground() const;
    QColor getForeground() const;

    QColor getTextHighEmphasis() const;
    QColor getTextMediumEmphasis() const;
    QColor getTextDisabled() const;

    QColor getControlActive() const;
    QColor getControlInactive() const;
    QColor getControlDisabled() const;

    QColor getOverlayLight() const;
    QColor getOverlayDark() const;

    QColor getInactive() const;
    QColor getDisabled() const;

};

#endif // THEMECONSTANTS_HPP
