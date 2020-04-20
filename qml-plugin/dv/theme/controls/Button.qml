import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T

import dv.theme.controls 1.0


T.Button {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding)

    horizontalPadding: 16
    verticalPadding: 0

    height: 36

    bottomInset: 0
    topInset: 0
    leftInset: 0
    rightInset: 0

    icon.width: 24
    icon.height: 24
    icon.color: control.checked || control.highlighted ? control.palette.brightText :
                control.flat && !control.down ? (control.visualFocus ? control.palette.highlight : control.palette.windowText) : control.palette.buttonText

    font {
        family: ThemeConstants.font
        pointSize: 14
        weight: Font.DemiBold
    }

    contentItem: IconLabel {
        spacing: control.spacing
        mirrored: control.mirrored
        display: control.display

        icon: control.icon
        text: control.text
        font: control.font
        color: control.enabled ? ThemeConstants.foregroundOnPrimary : ThemeConstants.inactive
        opacity: 1
    }

    background: Item {
        anchors.fill: parent

        Rectangle {
            id: normal
            anchors.fill: parent
            color: control.enabled ? ThemeConstants.primary : ThemeConstants.disabled
            opacity: 1
            visible: true
            radius: 4

            Rectangle {
                id: rectHover
                anchors.fill: parent
                color: ThemeConstants.overlayDark
                opacity: 0.08
                visible: false
                radius: 4
            }

            Rectangle {
                id: rectFocus
                anchors.fill: parent
                color: ThemeConstants.overlayDark
                opacity: 0.24
                visible: false
                radius: 4
            }

            Rectangle {
                id: rectActivated
                anchors.fill: parent
                color: ThemeConstants.overlayDark
                opacity: 0.08
                visible: false
                radius: 4
            }

            Rectangle {
                id: rectPressed
                anchors.fill: parent
                color: ThemeConstants.overlayDark
                opacity: 0.12
                visible: false
                radius: 4
            }
        }

    }

    hoverEnabled: true
    onHoveredChanged: rectHover.visible = enabled && (!focus && hovered)
    onFocusChanged: rectFocus.visible = enabled && focus
    onPressedChanged: rectPressed.visible = enabled && focus && pressed

}
