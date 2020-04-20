import QtQuick 2.12
import QtQuick.Controls 2.12
//import QtQuick.Dialogs 1.2

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

//    Rectangle {
//        id: rr
//        width: 50; height: 50; visible: true
//        x:200
//        y:200
//        color: "#FF00F6"
//        opacity: 1
//    }

    Item {
        clip: true
        anchors.left: parent.leftPadding
        height: parent.height
        width: 244

        Rectangle {
            id: rMenulist
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
            id: singleLine

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
                width: rMenulist.width
                labelFont: ThemeConstants.font
                label: mLabel
                image: mImage
                isActive: ListView.view.indexActive === index

            }
        }

        ListView {

            id: testListview

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

            model: SettingsCtrl.data.menuModel
            /* Lascio perche' non si sa mai
              delegate: SingleLineList {
                  width: rMenulist.width
                  labelFont: "Roboto"
                  label: mLabel
                  image: mImage
                  focus: ListView.isCurrentItem
                  isActive: index == testListview.indexActive
                  onActivated: {
                      testListview.indexActive = index;
                      testListview.currentIndex = index;
                      rr.x = rr.x + ((index % 2 == 0) ? 1 : -1) * 10 * index
                  }
              }
              */

            MouseArea {
                id: testMouseArea
                // z: -1 non serve perche' ho impostato contentItem.z=0
                hoverEnabled: true
                anchors.fill: parent
                propagateComposedEvents: false
                onClicked: {
                    var indexActive = testListview.indexAt(mouse.x, mouse.y)
                    testListview.currentIndex = indexActive
                    testListview.indexActive = indexActive
                }
            }

            delegate: singleLine

            Keys.onPressed: {
                switch (event.key) {
                case Qt.Key_Enter:
                case Qt.Key_Space:
                case Qt.Key_Return: testListview.indexActive = testListview.currentIndex;
                }
            }

        }

    }

}
