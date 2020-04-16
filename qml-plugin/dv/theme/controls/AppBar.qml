import QtQuick 2.12
import QtQuick.Controls 2.12

import dv.theme.controls 1.0


Control {

    id: appBar

    property string title
    property Component leftItem
    property list<Component> rightItems

    readonly property int maxRightItems: 1
    readonly property int rightItemsSpace: 24

    property list<Component> instancedItems;
    property int instancedWidth : 0

    width: parent ? parent.width : 1000
    height: 56
    bottomInset: 0
    topInset: 0
    leftInset: 0
    rightInset: 0
    padding: 16
    background: Rectangle {
        id: appBarRect
        width: parent.implicitContentWidth
        height: parent.implicitContentHeight
        color: ThemeConstants.primary
        border.width: 0
    }

    Component.onCompleted: {
        instancedWidth = appBar.width
        appBar.statusReady = true
    }

    onWidthChanged: {

        for (var i=0; i<instancedItems.length; i++) {
            instancedItems[i].x = instancedItems[i].x + (appBar.width - appBar.instancedWidth)
        }
        appBar.instancedWidth = appBar.width

    }


    contentItem: Item {

        id: contentItem
        width: appBar.implicitContentWidth
        height: appBar.implicitContentHeight

        Text {
            id: appBarTitle
            color: ThemeConstants.fontColor
            text: appBar.title
            x: 56
            font {
                pixelSize: 20
                family: "Roboto"
                weight: Font.Medium
            }
        }

        Component.onCompleted: {

            if (leftItem)
                leftItem.createObject(contentItem, {x:0, y:0})

            var iterations = Math.min(maxRightItems, appBar.rightItems.length)
//            console.info("Iter: "+iterations)
            var rightPosition = appBar.availableWidth

            for (var i=0; i<iterations; i++) {

                //                console.info("rPos: "+appBar.width-rightItems[i].width-20*i)

                var rItem = appBar.rightItems[i].createObject(contentItem, {id: "ciao"})//, {x:appBar.width-rightItems[i].width-20*i, y:0})
//                console.info("appBar.width: "+appBar.availableWidth)
//                console.info("rItem.width: "+rItem.width)
                //                rItem.id = "rightButton" + i
                rItem.x = rightPosition - rItem.width - rightItemsSpace*i
                rItem.y = 0
                rightPosition = rItem.x
                instancedItems.push(rItem)

            }
        }

    }

}
