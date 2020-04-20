import QtQuick 2.12
import QtQuick.Controls 2.12

import dv.theme.controls 1.0


Control {

    id: appBar

    property string title
    property Component leftItem
    property list<Component> rightItems

    QtObject {
        id: innerObj
        readonly property int maxRightItems: 3
        readonly property int rightItemsSpace: 0

        property list<Component> instancedItems;
        property int instancedWidth : 0
    }

    width: parent ? parent.width : 1000
    height: 56
    bottomInset: 0
    topInset: 0
    leftInset: 0
    rightInset: 0
//    padding: 16
    horizontalPadding: 12
    verticalPadding: 4
    background: Rectangle {
        id: appBarRect
        width: parent.implicitContentWidth
        height: parent.implicitContentHeight
        color: ThemeConstants.primary
        border.width: 0
    }

    Component.onCompleted: {
        innerObj.instancedWidth = appBar.width
    }

    onWidthChanged: {

        var instancedItemsSize = innerObj.instancedItems.length
        for (var i=0; i<instancedItemsSize; i++) {
            var item = innerObj.instancedItems[i]
            item.x = item.x + (appBar.width - innerObj.instancedWidth)
        }
        innerObj.instancedWidth = appBar.width

    }

    contentItem: Item {

        id: contentItem
        width: appBar.implicitContentWidth
        height: appBar.implicitContentHeight
        anchors.verticalCenter: appBar.verticalCenter

        Text {
            id: appBarTitle
            color: ThemeConstants.foregroundOnPrimary
            text: appBar.title
            x: 56
            anchors.verticalCenter: parent.verticalCenter
            font {
                pixelSize: 20
                family: "Roboto"
                weight: Font.Medium
            }
        }

        Component.onCompleted: {

            if (leftItem)
                leftItem.createObject(contentItem, {x:0, y:0})

            var iterations = Math.min(innerObj.maxRightItems, appBar.rightItems.length)
//            console.info("Iter: "+iterations)
            var rightPosition = appBar.availableWidth

            for (var i=0; i<iterations; i++) {

//                console.info("rPos: "+appBar.width-rightItems[i].width-20*i)

                var rItem = appBar.rightItems[i].createObject(contentItem)//, {x:appBar.width-rightItems[i].width-20*i, y:0})
//                console.info("appBar.width: "+appBar.availableWidth)
//                console.info("rItem.width: "+rItem.width)
//                rItem.id = "rightButton" + i
                rItem.x = rightPosition - rItem.width - innerObj.rightItemsSpace*i
//                rItem.y = 0
                rItem.anchors.verticalCenter = contentItem.verticalCenter
                rightPosition = rItem.x
                innerObj.instancedItems.push(rItem)

            }
        }

    }

}
