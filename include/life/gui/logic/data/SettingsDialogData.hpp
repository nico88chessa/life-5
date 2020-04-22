#ifndef SETTINGSDIALOGDATA_HPP
#define SETTINGSDIALOGDATA_HPP

#include <configure.h>

#include <QObject>
#include <QString>
#include <QList>
//#include <QAbstractItemModel>

#include <life/common/MacroUtils.hpp>


DV_LIFE_OPEN_NAMESPACE

/**
 * NOTE NIC 20/04/2020: gestione eccezioni
 * per ora metto sotto namespace le varie eccezioni; e' da valutare
 * se fare una classe standard sottonamespace dv::life con le eccezioni
 * che sono comuni a varie classi
 */
namespace menucontainer {

class IndexOutOfBoundException : public std::exception {
public:
    IndexOutOfBoundException() { }

    virtual const char* what() const noexcept {
        return "Index out of bound exception";
    }
};

}


class MenuItem {
    DV_DECL_POINTER_ALIAS(MenuItem)

private:
    QString label;
    QString image;
    bool enabled;

public:
    MenuItem(const QString& label="", const QString& image="", bool enabled = true) :
        label(label), image(image), enabled(enabled) { }

    QString getLabel() const { return label; }
    void setLabel(const QString& value) { label = value; }

    QString getImage() const { return image; }
    void setImage(const QString& value) { image = value; }

    bool isEnabled() const { return enabled; }
    void setEnabled(bool value) { enabled = value; }

    friend std::ostream& operator<<(std::ostream& os, const MenuItem& item);

};



class MenuContainer : public QObject {
    Q_OBJECT

    DV_DECL_POINTER_ALIAS(MenuContainer)

private:
    QList<MenuItem> items;

public:
    explicit MenuContainer(QObject* parent = nullptr);

    virtual ~MenuContainer();

    int size() const noexcept;

    void addItem(const MenuItem& item, int index) noexcept;

    void appendItem(const MenuItem& item) noexcept;

    void setItem(const MenuItem& item, int index) noexcept(false);

    /**
     * @brief itemAt
     * @param index
     * @throw IndexOutOfBoundException se index non e' valido
     * @return
     */
    MenuItem itemAt(int index) const noexcept(false);

    /**
     * @brief removeItem
     * @param index
     * @throw IndexOutOfBoundException se index non e' valido
     * @return
     */
    void removeItem(int index) noexcept(false);

protected:
    bool isIndexValid(int index) const noexcept;

signals:
    void beforeInsert(int index);
    void afterInsert(int index);

    void dataChanged(int index);

    void beforeRemove(int index);
    void afterRemove(int index);

};



class SettingsDialogData : public QObject {
    Q_OBJECT

public:
    DV_DECL_POINTER_ALIAS(SettingsDialogData)

private:
    MenuContainer menuContainer;

public:
    explicit SettingsDialogData(QObject* parent = nullptr);

    MenuContainer::Ptr getMenuContainer();
};


DV_LIFE_CLOSE_NAMESPACE

Q_DECLARE_METATYPE(dv::life::MenuItem)

#endif // SETTINGSDATA_HPP
