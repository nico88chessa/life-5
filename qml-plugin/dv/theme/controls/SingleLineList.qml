import QtQuick 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.12

import dv.theme.controls 1.0


Control {

    id: controlId

    property string label
    property url image
    property string labelFont
    property bool isActive

    readonly property int paddingDefault: 16
    readonly property int heightDefault: 56
    readonly property int widthDefault: 244

    padding: paddingDefault
    height: visible ? heightDefault : 0
    width: widthDefault

    QtObject {
        id: innerObj
        readonly property int labelImageDistance: 32
        property bool urlValid
    }

    background: Item {
        anchors.fill: parent

        Rectangle {
            id: rectHover
            anchors.fill: parent
            color: ThemeConstants.overlayLight
            opacity: 0.04
            visible: false
        }

        Rectangle {
            id: rectFocus
            anchors.fill: parent
            color: ThemeConstants.overlayLight
            opacity: 0.12
            visible: false
        }

        Rectangle {
            id: rectActivated
            anchors.fill: parent
            color: ThemeConstants.primary
            opacity: 0.08
            visible: false
        }

        Rectangle {
            id: rectPressed
            anchors.fill: parent
            color: controlId.isActive ? ThemeConstants.primary : ThemeConstants.overlayLight
            opacity: 0.12
            visible: false
        }

    }

    onFocusChanged: rectFocus.visible = activeFocus
    onIsActiveChanged: rectActivated.visible = isActive
    onHoveredChanged: rectHover.visible = hovered && !activeFocus

    MouseArea {
        id: controlMouseArea
        propagateComposedEvents: true
        hoverEnabled: true
        anchors.fill: parent
        //onEntered: {
        //    rectHover.visible = hovered
        //}
        //onExited: {
        //    rectHover.visible = hovered
        //}
//        onClicked: {
//            mouse.accepted = false
//        }
        //onPressed: {
        //    rectPressed.visible = true
        //    mouse.accepted = true
        //}
        onContainsPressChanged: {
            rectPressed.visible = controlMouseArea.containsPress
        }
    }

    contentItem: Item {

        id: content

        Image {
            visible: innerObj.urlValid
            id: itemImage
            x: 0
            y: 0
            sourceSize.width: controlId.image ? 24 : 0
            sourceSize.height: 24
            source: controlId.image
            ColorOverlay {
                anchors.fill: parent
                source: parent
                color: controlId.isActive ? ThemeConstants.primary : ThemeConstants.textHighEmphasis
            }
        }

        Label {
            id: itemLabel
            color: controlId.isActive ? ThemeConstants.primary : ThemeConstants.textHighEmphasis
            text: label
            x: innerObj.urlValid ? itemImage.width + innerObj.labelImageDistance : 0
            anchors.verticalCenter: parent.verticalCenter
            font {
                family: controlId.labelFont
                pixelSize: 16
                weight: Font.Medium
            }
        }
    }

    Component.onCompleted: {
        innerObj.urlValid = controlId.image.toString().length > 0
    }

}
