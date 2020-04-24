import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

import dv.theme.controls 1.0

Item {

    id: list

    property alias contentModel: listview.model
    property alias delegate: listview.delegate
    property alias indexActive: listview.indexActive
    property alias currentIndex: listview.currentIndex
    property alias currentItem: listview.currentItem

    clip: true
    anchors.left: parent.leftPadding
    implicitWidth: 244
    implicitHeight: parent.height

    Rectangle {
        id: rectangle
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

    ListView {

        id: listview

        property int indexActive: 0
        currentIndex: 0

        anchors.fill: parent
        interactive: false
        focus: true
        keyNavigationEnabled: true
        // elevo lo z del contentItem (di default sarebbe 0)
        // in questo modo la MouseArea sulla ListView funziona correttamente perche'
        // passa sotto al content Item
        contentItem.z: 1

        MouseArea {
            id: maMenu
            // z: -1 non serve perche' ho impostato contentItem.z=0
            hoverEnabled: true
            anchors.fill: parent
            propagateComposedEvents: false
            onClicked: {
                var indexActive = listview.indexAt(mouse.x, mouse.y)
                listview.currentIndex = indexActive
                listview.indexActive = indexActive
            }
        }

        Keys.onPressed: {
            switch (event.key) {
            case Qt.Key_Enter:
            case Qt.Key_Space:
            case Qt.Key_Return: listview.indexActive = listview.currentIndex;
            }
        }

    }

}
