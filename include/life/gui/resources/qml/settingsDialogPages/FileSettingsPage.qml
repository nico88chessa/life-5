import QtQuick 2.12
import QtQuick.Layouts 1.12

import dv.life.controllers 1.0
import dv.theme.controls 1.0


Item {

    id: fsSettings

    List {
        id: groupMenu
        contentModel: SettingsDialogCtrl.settingsGroupModel
        delegate: groupDelegate
        width: 244

        Component {
            id: groupDelegate

            SingleLineList {
                z:1
                width: groupMenu.width
                labelFont: ThemeConstants.font
                label: itemName
                visible: itemIsActive
                isActive: ListView.view.indexActive === index
            }
        }

    }

    Component {
        id: deferredParametersPage
        Item {
            property int groupIndex

            Rectangle {
                anchors.fill: parent
                color: "#FF5522"
            }
            ListView {
                height: parent.height
//                anchors.left: groupMenu.right
                width: parent.width - groupMenu.width
                model: SettingsDialogCtrl.settingsGroupParameterModel(groupIndex)

                delegate: Item {
                    width: parent.width
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 60
                    Text {
                        x: 0
                        width: 100
                        text: parameterName
                    }
                    TextField {
                        x: 30
                        width: 100
                        text: parameterValue
                        onEditingFinished: parameterValue = parseInt(text)
                    }
                    Text {
                        x: 60
                        width: 100
                        text: parameterType
                    }
                }
            }
        }
    }

    StackLayout {
        id: groupStack

        anchors.left: groupMenu.right
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        currentIndex: groupMenu.indexActive

        Component.onCompleted: {
//            console.debug("PASSSA")
//            console.debug("Size: "+SettingsDialogCtrl.settingsGroupModel.rowCount())
            var groupsSize = SettingsDialogCtrl.settingsGroupModel.rowCount()
            for (var i=0; i<groupsSize; ++i)
                deferredParametersPage.createObject(groupStack, {groupIndex:i} )
        }

    }



    Button {
        x:100
        y:100
        focus: true
        enabled: true
        onClicked: SettingsDialogCtrl.testAdd();
    }

}
