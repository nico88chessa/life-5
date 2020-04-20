import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T

import QtGraphicalEffects 1.12
import dv.theme.controls 1.0


T.Button {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    horizontalPadding: 16;
    verticalPadding: 0

    height: 56
    width: 56

    icon.width: 24
    icon.height: 24

    contentItem: Item {
        width: icon.width
        height: icon.height
        Image {
            id: image
            source: icon.source
            sourceSize.width: 24
            sourceSize.height: 24
            anchors.centerIn: parent
            ColorOverlay {
                anchors.fill: parent
                source: parent
                color: ThemeConstants.foregroundOnPrimary
            }
        }
    }

    background: Item {
        anchors.fill: parent

        Rectangle {
            id: normal
            anchors.fill: parent
            color: control.enabled ? ThemeConstants.primary : ThemeConstants.disabled
            opacity: 1
            visible: true
            radius: control.width / 2

            Rectangle {
                id: rectHover
                anchors.fill: parent
                color: ThemeConstants.overlayDark
                opacity: 0.08
                visible: false
                radius: control.width / 2
            }

            Rectangle {
                id: rectFocus
                anchors.fill: parent
                color: ThemeConstants.overlayDark
                opacity: 0.24
                visible: false
                radius: control.width / 2
            }

            Rectangle {
                id: rectActivated
                anchors.fill: parent
                color: ThemeConstants.overlayDark
                opacity: 0.08
                visible: false
                radius: control.width / 2
            }

            Rectangle {
                id: rectPressed
                anchors.fill: parent
                color: ThemeConstants.overlayDark
                opacity: 0.12
                visible: false
                radius: control.width / 2
            }
        }

    }

    hoverEnabled: true
    onHoveredChanged: rectHover.visible = enabled && (!focus && hovered)
    onFocusChanged: rectFocus.visible = enabled && focus
    onPressedChanged: rectPressed.visible = enabled && focus && pressed

}
