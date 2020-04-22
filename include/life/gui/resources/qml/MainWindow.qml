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


    Loader {
        anchors.fill: parent
        id: settingsDialogLoader
    }

//    Image {
//        source: "qrc:///icons/menu-24px.svg"
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

    Rectangle { id: r11; x: 470; y: 275; width: 50; height: 50; color: "#AAFF0000"; visible: true; opacity: 0.12 }
    Rectangle { id: r12; x: 495; y: 275; width: 50; height: 50; color: "#AAFF0000"; visible: true; opacity: 0.08 }

    Rectangle { id: r01; x: 470; y: 350; width: 400; height: 50; color: "#FF6200EE"; visible: true; opacity: 1 }
    Rectangle { id: r02; x: 525; y: 350; width: 50; height: 50; color: "#FFFFFFFF"; visible: true; opacity: 0.08 }
    Rectangle { id: r03; x: 555; y: 350; width: 50; height: 50; color: "#FFFFFFFF"; visible: true; opacity: 0.16 }
    Rectangle { id: r04; x: 585; y: 350; width: 50; height: 50; color: "#FFFFFFFF"; visible: true; opacity: 0.24 }
    Rectangle { id: r05; x: 615; y: 350; width: 50; height: 50; color: "#FFFFFFFF"; visible: true; opacity: 0.32 }

    Rectangle { id: r003; x: 555; y: 425; width: 50; height: 50; color: "#FF6200EE"; visible: true; opacity: 1 }
    Rectangle { id: r004; x: 585; y: 425; width: 50; height: 50; color: "#FF6200EE"; visible: true; opacity: 0.08 }
    Rectangle { id: r005; x: 615; y: 425; width: 50; height: 50; color: "#FF6200EE"; visible: true; opacity: 0.12 }

    Rectangle { id: r1; x: 470; y: 500; width: 50; height: 50; color: "#FF1A3C6F"; visible: true; opacity: 1 }
    Rectangle { id: r2; x: 525; y: 500; width: 50; height: 50; color: "#FF1A3C6F"; visible: true; opacity: 0.08 }
    Rectangle { id: r3; x: 555; y: 500; width: 50; height: 50; color: "#FF1A3C6F"; visible: true; opacity: 0.12 }

    Rectangle { id: r4; x: 470; y: 575; width: 50; height: 50; color: "#FF000000"; visible: true; opacity: 1; }
    Rectangle { id: r5; x: 525; y: 575; width: 50; height: 50; color: "#FF000000"; visible: true; opacity: 0.04; }
    Rectangle { id: r6; x: 555; y: 575; width: 50; height: 50; color: "#FF000000"; visible: true; opacity: 0.08; }
    Rectangle { id: r7; x: 585; y: 575; width: 50; height: 50; color: "#FF000000"; visible: true; opacity: 0.12; }

    Rectangle { id: testRectMD0; x: 675; y: 675; width: 50; height: 50; color: "#AAFF0000"; visible: true; opacity: 0.5; }
    Rectangle { id: testRectMD1; x: 700; y: 700; width: 50; height: 50; color: "#AAFF0000"; visible: true; }
    Rectangle { id: testRectMD2; x: 725; y: 725; width: 50; height: 50; color: "#44FF0000"; visible: true; }


    AppBar {
        id: appBar
        x: 0
        y: 0
        title: DV.MainwindowCtrl.pData.pApplicationName
        leftItem: Component {
            id: menuButton
            AppMenuButton {
                icon.source: "qrc:/icons/menu-24px.svg"
                icon.width: 24
                icon.height: 24
            }
        }

            /*Component {
            id: menuButton
            Image {
                id: menuImage
                source: "qrc:/icons/menu-24px.svg"
                sourceSize.width: 48
                sourceSize.height: 48
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

        }*/
        rightItems: [
            Component {
                id: settingsButton
                Image {
                    id: settingsImage
                    source: "qrc:/icons/settings-24px.svg"
                    sourceSize.height: 48
                    ColorOverlay {
                        anchors.fill: parent
                        source: parent
                        color: ThemeConstants.foregroundOnPrimary
                    }

                    MouseArea {
                        id: settingsImageArea
                        anchors.fill: parent
                        onClicked: {
                            if (settingsDialogLoader.status == Loader.Null) {
                                settingsDialogLoader.source = "qrc:/qml/SettingsDialog.qml"
                            }
                            settingsDialogLoader.item.visible = true
                        }
                    }
                }
            },
            Component {
                id: fbTest
                AppMenuButton {
                    icon.source: "qrc:/icons/settings-24px.svg"
                    onClicked: {
                        if (settingsDialogLoader.status == Loader.Null) {
                            settingsDialogLoader.source = "qrc:/qml/SettingsDialog.qml"
                        }
                        settingsDialogLoader.item.visible = true
                    }
                }
            },
            Component {
                id: fbTest2
                AppMenuButton {
                    icon.source: "qrc:/icons/settings-24px.svg"
                }
            }
        ]

    }

    Button {
        id: buttonTest
        width: 100
        x: 30
        y: 700
    }

    Button {
        id: buttonTest2
        x: 150
        y: 700
        text: "BUTTON"
    }

    Button {
        id: buttonTest3
        x: 270
        y: 700
        enabled: false
        text: "DISABLED"
    }

    FloatingButton {
        id: fb1
        x: 270
        y: 500
        icon.source: "qrc:/icons/settings-24px.svg"
    }

    FloatingButton {
        id: fb2
        x: 170
        y: 500
    }

    TextField {
        x:20
        y:100
        placeholderText: "PROVA 2"
        helperText: "Inserisci il testo"
    }

    TextField {
        x:320
        y:100
        enabled: false
        text: "SAIDM"
        placeholderText: "PROVA 2"
        helperText: "Inserisci il testo"
    }

    ////////////////////////////////////////////////////////////////////////

//    Rectangle {
//        id: rectItem
//        width: 50
//        height: 50
//        color: "#FFAAFF"
//        x: 400
//        y: 100
//        MouseArea {
//            anchors.fill: parent
//            hoverEnabled: true
//            onEntered: rectItem.color = "#FF22FF"
//            onExited: rectItem.color = "#FFFFAF"
//        }
//    }

//    ListView {
//        id: testListview
//        width: 180
//        height: parent.height

//        x: 0
//        y: 100
//        highlight: Rectangle {
//            color: "#FFAA00"
//            radius: 5
//            z: 3
//        }
//        interactive: true
//        focus: true

//        model: ListModel  {
//            ListElement {
//                name: "Bill Smith"
//                number: "555 3264"
//            }
//            ListElement {
//                name: "John Brown"
//                number: "555 8426"
//            }
//            ListElement {
//                name: "Bill Smith"
//                number: "555 3264"
//            }
//            ListElement {
//                name: "John Brown"
//                number: "555 8426"
//            }
//            ListElement {
//                name: "Bill Smith"
//                number: "555 3264"
//            }
//            ListElement {
//                name: "John Brown"
//                number: "555 8426"
//            }
//        }

//        delegate: Item {

//            height: 20
//            width: parent.width
//            z: 4
//            focus: true

//            Rectangle {
//                id: rectItemTest
//                anchors.fill: parent
//                color: "#FFAAFF"
//                z: -3
//            }

//            Text {
//                text: activeFocus ? "YEAH " + name + ": " + number : "NOO " + name + ": " + number;
//                height: 20
//                z:4
//            }

//            MouseArea {
//                anchors.fill: parent
//                onClicked: testListview.currentIndex = index
//                hoverEnabled: true
//                onEntered: {
//                    console.debug("ENTRO")
//                    rectItemTest.color = "#FFFFAF"
//                }
//                onExited: {
//                    console.debug("ESCO")
//                    rectItemTest.color = "#FFAAFF"
//                }
//            }
//        }
//        onCurrentItemChanged: console.log(model.get(testListview.currentIndex).name + ' selected')

//    }

}
