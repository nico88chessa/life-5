#ifndef SETTINGSDATA_HPP
#define SETTINGSDATA_HPP

#include <configure.h>

#include <QObject>
#include <QString>
#include <QAbstractItemModel>

#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

namespace inner {

class MenuItem {
public:
    DV_DECL_POINTER_ALIAS(MenuItem)

private:
    QString label;
    QString image;
    bool enabled;

public:
    MenuItem(const QString& label, const QString& image="", bool enabled = true) :
        label(label), image(image), enabled(enabled) { }

    QString getLabel() const { return label; }
    void setLabel(const QString& value) { label = value; }

    QString getImage() const { return image; }
    void setImage(const QString& value) { image = value; }

    bool isEnabled() const { return enabled; }
    void setEnabled(bool value) { enabled = value; }

    friend std::ostream& operator<<(std::ostream& os, const dvlife::inner::MenuItem& item);

};



class MenuModel : public QAbstractListModel {
    Q_OBJECT

public:
    DV_DECL_POINTER_ALIAS(MenuModel)

    enum MenuModelRole : int {
        MenuLabel = Qt::UserRole + 1,
        MenuImage,
        MenuEnabled
    };

private:
    QList<MenuItem> menu;

public:
    explicit MenuModel(QObject* parent = nullptr);

public:
    void appendMenuItem(const MenuItem& item);
    int rowCount(const QModelIndex& parent) const;
    QVariant data(const QModelIndex& index, int role) const;

    QHash<int, QByteArray> roleNames() const;
};

}



class SettingsData : public QObject {
    Q_OBJECT

    Q_PROPERTY(QAbstractListModel* menuModel READ getMenuModel)

public:
    DV_DECL_POINTER_ALIAS(SettingsData)

private:
    inner::MenuModel menuModel;

public:

    explicit SettingsData(QObject* parent = nullptr);

    inner::MenuModel::Ptr getMenuModel();
};


DV_LIFE_CLOSE_NAMESPACE

#endif // SETTINGSDATA_HPP
