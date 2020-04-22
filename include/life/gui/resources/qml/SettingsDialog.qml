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

    Item {
        id: iMainMenu
        clip: true
        anchors.left: parent.leftPadding
        height: parent.height
        width: 244

        Rectangle {
            id: rMainMenu
            color: ThemeConstants.background
            anchors {
                fill: parent
                leftMargin: -border.width
                topMargin: -border.width
                bottomMargin: -border.width
            }

            border {
                width: 1
                color: ThemeConstants.overlayLight
            }
        }

        Component {
            id: cMenuItem

            SingleLineList {
                /* NOTA: il parent di questo e' ContentItem, non la listView (vedere sotto ListView)
                  lo z: del ContentItem e': 0, per questo ho dovuto mettere come z: -1 nella
                  MouseArea della listView
                  vedere link https://doc.qt.io/qt-5/qtquick-visualcanvas-visualparent.html
                  per capire le gerarchie (z funziona fra nodi fratelli e genitore), non fra i
                  fratelli dei genitori (come in questo caso)
                  MouseArea della ListView e' fratello di ContentItem, non del delegate
                  */
                z:1
                width: rMainMenu.width
                labelFont: ThemeConstants.font
                label: itemLabel
                image: itemImage
//                enabled: itemIsEnabled
                isActive: ListView.view.indexActive === index

            }
        }

        ListView {

            id: lvMainMenu

            property int indexActive//: -1

//            currentIndex: -1
            anchors.fill: parent
            interactive: false
            focus: true
            keyNavigationEnabled: true
            // elevo lo z del contentItem (di default sarebbe 0)
            // in questo modo la MouseArea sulla ListView funziona correttamente perche'
            // passa sotto al content Item
            contentItem.z: 1

            model: SettingsDialogCtrl.menuModel
            /* Lascio perche' non si sa mai
              delegate: SingleLineList {
                  width: rMainMenu.width
                  labelFont: "Roboto"
                  label: mLabel
                  image: mImage
                  focus: ListView.isCurrentItem
                  isActive: index == lvMainMenu.indexActive
                  onActivated: {
                      lvMainMenu.indexActive = index;
                      lvMainMenu.currentIndex = index;
                      rr.x = rr.x + ((index % 2 == 0) ? 1 : -1) * 10 * index
                  }
              }
              */

            MouseArea {
                id: maMenu
                // z: -1 non serve perche' ho impostato contentItem.z=0
                hoverEnabled: true
                anchors.fill: parent
                propagateComposedEvents: false
                onClicked: {
                    var indexActive = lvMainMenu.indexAt(mouse.x, mouse.y)
                    lvMainMenu.currentIndex = indexActive
                    lvMainMenu.indexActive = indexActive
                }
            }

            delegate: cMenuItem

            Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Enter:
                case Qt.Key_Space:
                case Qt.Key_Return: lvMainMenu.indexActive = lvMainMenu.currentIndex;
                }
            }

        }

    }


    StackLayout {
        id: slStack

        anchors.left: iMainMenu.right
        anchors.top: settingsDialog.contentItem.top
        anchors.bottom: settingsDialog.contentItem.bottom
        anchors.right: settingsDialog.contentItem.right

        currentIndex: lvMainMenu.indexActive

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
