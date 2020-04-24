import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

//import "./settingsDialogParts" OK
import "qrc:/qml/settingsDialogPages"


import dv.life.controllers 1.0
import dv.theme.controls 1.0


Dialog {

    id: settingsDialog
    width: parent && (parent.width > 0) ? (parent.width - 100) : 640
    height: parent && (parent.height > 0) ? (parent.height - 100) : 480
    visible: false
    modal: true
    closePolicy: "NoAutoClose"
    anchors.centerIn: Overlay.overlay
    padding: 0
    focus: true

    background: Rectangle {
        color: ThemeConstants.background
        border.width: 0
    }

    List {
        id: settingsMenu
        contentModel: SettingsDialogCtrl.menuModel
        delegate: menuDelegate
        width: 244

        Component {
            id: menuDelegate

            SingleLineList {
                /* NOTA: il parent di questo e' ContentItem, non la listView (vedere List.qml)
                   lo z: del ContentItem e': 0, per questo ho dovuto mettere come z: -1 nella
                   MouseArea della listView
                   vedere link https://doc.qt.io/qt-5/qtquick-visualcanvas-visualparent.html
                   per capire le gerarchie (z funziona fra nodi fratelli e genitore), non fra i
                   fratelli dei genitori (come in questo caso)
                   MouseArea della ListView e' fratello di ContentItem, non del delegate
                   */
                z:1
                width: settingsMenu.width
                labelFont: ThemeConstants.font
                label: itemLabel
                image: itemImage
                isActive: ListView.view.indexActive === index

            }
        }

    }

    StackLayout {
        id: slStack

        anchors.left: settingsMenu.right
        anchors.top: settingsDialog.contentItem.top
        anchors.bottom: settingsDialog.contentItem.bottom
        anchors.right: settingsDialog.contentItem.right

        currentIndex: settingsMenu.indexActive

        FileSettingsPage {

        }
        Rectangle {
            color: 'teal'
        }
        Rectangle {
            color: 'plum'
        }
    }

}
