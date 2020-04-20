import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T

import dv.theme.controls 1.0


T.TextField {
    id: control

    property string helperText

    readonly property int defaultFontPixelSize: 16
    readonly property int placeholderFontPixelSize: 12
    readonly property int helperFontPixelSize: 12
    readonly property int horizontalPadding: 12
    readonly property int bottomInsetDefault: 16

    implicitWidth: implicitBackgroundWidth + leftInset + rightInset
                   || Math.max(contentWidth, placeholder.implicitWidth) + leftPadding + rightPadding
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding,
                             placeholder.implicitHeight + topPadding + bottomPadding)

    topInset: 0
    leftInset: 0
    rightInset: 0
    bottomInset: bottomInsetDefault + helperFontMetrics.descent
    mouseSelectionMode: TextEdit.SelectCharacters
    selectByMouse: true

    padding: 0
    leftPadding: horizontalPadding
    rightPadding: horizontalPadding

    verticalAlignment: TextInput.AlignVCenter
    font.pixelSize: defaultFontPixelSize

    hoverEnabled: true
    color: enabled ? ThemeConstants.textHighEmphasis : ThemeConstants.textDisabled
    selectionColor: ThemeConstants.secondaryLight
    selectedTextColor: ThemeConstants.textHighEmphasis
    placeholderTextColor: ThemeConstants.textHighEmphasis
    font.family: ThemeConstants.font

    helperText: "Inserisci il testo"

    Text {
        id: placeholder
//        readonly property bool isPrimary: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        readonly property bool isPrimary: !control.activeFocus && !control.length && !control.preeditText

        FontMetrics {
            id: placeholderFontMetrics
            font.family: control.font.family
        }

        x: control.leftPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.implicitBackgroundHeight - (control.topPadding + control.bottomPadding)

        text: control.placeholderText
        font.family: control.font.family
        font.pixelSize: isPrimary ? control.font.pixelSize : control.placeholderFontPixelSize

        color: control.enabled ? ( control.activeFocus ? ThemeConstants.secondary : control.hovered ? ThemeConstants.textHighEmphasis : ThemeConstants.textMediumEmphasis ) : ThemeConstants.textDisabled
        visible: true
        elide: Text.ElideRight
        renderType: control.renderType
        anchors.baseline: isPrimary ? control.verticalCenter: control.top
        anchors.baselineOffset: isPrimary ? placeholderFontMetrics.height/2: 20

    }

    background: Rectangle {
        implicitWidth: 280
        implicitHeight: 56
        border.width: 0
        color: ThemeConstants.background
        clip: true
        Rectangle {
            border.width: control.activeFocus ? 2 : 1
            border.color: control.enabled ? ( control.activeFocus ? ThemeConstants.secondary : control.hovered ? ThemeConstants.controlActive : ThemeConstants.controlInactive ) : ThemeConstants.controlDisabled
            color: "transparent"
            anchors.fill: parent
            anchors.leftMargin: parent.anchors.leftMargin - border.width
            anchors.rightMargin: parent.anchors.rightMargin - border.width
            anchors.topMargin: parent.anchors.topMargin - border.width
        }
    }

    Text {
        id: helperText

        readonly property bool isVisible: !control.length && !control.preeditText

        FontMetrics {
            id: helperFontMetrics
            font.family: control.font.family
        }

        x: control.leftPadding
        width: control.width - (control.leftPadding + control.rightPadding)
        height: control.bottomInset

        text: control.helperText
        font.family: control.font.family
        font.pixelSize: control.helperFontPixelSize
        anchors.baseline: control.bottom
        anchors.baselineOffset: -helperFontMetrics.descent
        color: control.enabled ? ThemeConstants.textMediumEmphasis : ThemeConstants.textDisabled
        verticalAlignment: TextInput.AlignBottom
        visible: true
        elide: Text.ElideRight
        renderType: control.renderType

    }

}
