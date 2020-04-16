import QtQuick 2.12
import QtQuick.Controls 2.12

import dv.life.controllers 1.0 as DV // da abilitare a rountine

import dv.theme.controls 1.0
import QtGraphicalEffects 1.12


ApplicationWindow {
    id: applicationWindow

    visible: true
    width: 1024
    height: 768
//    minimumWidth: 1024
//    minimumHeight: 768
    flags: Qt.FramelessWindowHint

//    Image {
//        source: "qrc:///icons/menu-black-18dp.svg"
//        x: 100
//        y: 100
//        sourceSize.width: 100
//        sourceSize.height: 100
//        id: testImage

//    }
//    ColorOverlay {
//        anchors.fill: testImage
//        source: testImage
//        color: "#ff0000"
//    }


    AppBar {
        id: appBar
        x: 0
        y: 0
        title: DV.MainwindowCtrl.pData.pApplicationName
        leftItem: Component {
            id: menuButton
            Image {
                id: menuImage
                source: "qrc:/icons/menu-black-18dp.svg"
                sourceSize.width: 24
                sourceSize.height: 24
                ColorOverlay {
                    anchors.fill: parent
                    source: parent
                    color: "#FFFFFF"
                }

                MouseArea {
                    id: menuImageArea
                    anchors.fill: parent
                    onClicked: DV.MainwindowCtrl.calledTest()
                }
            }

        }
        rightItems: [
            Component {
                id: settingsButton
                Image {
                    id: settingsImage
                    source: "qrc:/icons/settings-24px.svg"
                    sourceSize.height: 24
                    ColorOverlay {
                        anchors.fill: parent
                        source: parent
                        color: "#FFFFFF"
                    }

                    MouseArea {
                        id: settingsImageArea
                        anchors.fill: parent
                    }
                }
            },
            Component {
                Rectangle {
                    width: 20
                    height: 20
                    color: "#FF00FF"
                }
            }
        ]

    }

//    Button {
//        x: 176
//        y: 115
//        width: 100
//        height: 30
//    }

//    Button {
//        x: 276
//        y: 215
//        enabled: false
//        width: 100
//        height: 30

//    }

}
