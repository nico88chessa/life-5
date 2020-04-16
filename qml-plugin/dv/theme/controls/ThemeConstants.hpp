#ifndef THEMECONSTANTS_HPP
#define THEMECONSTANTS_HPP

#include <QColor>
#include <QObject>


class ThemeConstants : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString font READ getFont CONSTANT)
    Q_PROPERTY(QColor fontColor READ getFontColor CONSTANT)
    Q_PROPERTY(QColor primary READ getPrimary CONSTANT)
    Q_PROPERTY(QColor primaryLight READ getPrimaryLight CONSTANT)
    Q_PROPERTY(QColor primaryDark READ getPrimaryDark CONSTANT)
    Q_PROPERTY(QColor secondary READ getSecondary CONSTANT)
    Q_PROPERTY(QColor secondaryLight READ getSecondaryLight CONSTANT)
    Q_PROPERTY(QColor secondaryDark READ getSecondaryDark CONSTANT)

private:
    QString font;
    QColor fontColor;

    QColor primary;// "#1A3C6F"
    QColor primaryLight;// "#4D669E"
    QColor primaryDark;// "#001743"
    QColor secondary;// "#F48904"
    QColor secondaryLight;// "#FFBA45"
    QColor secondaryDark; //"#BB5B00"

public:
    explicit ThemeConstants(QObject* parent = nullptr);

public slots:
    QString getFont() const;
    QColor getFontColor() const;

    QColor getPrimary() const;
    QColor getPrimaryLight() const;
    QColor getPrimaryDark() const;
    QColor getSecondary() const;
    QColor getSecondaryLight() const;
    QColor getSecondaryDark() const;


signals:
    void primaryChanged();

};

#endif // THEMECONSTANTS_HPP
