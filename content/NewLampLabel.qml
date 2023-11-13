import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: item1
    width: 350
    height: 45
    property string labelText: "text"
    property color bgColor: "#7d7676"

    signal addLamp(id: string)

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 350
        height: 45
        color: bgColor
        radius: 15

        Text {
            id: text1
            x: 0
            y: 0
            width: 350
            height: 45
            text: labelText
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

    }


    MouseArea {
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        onClicked: (mouse)=> {
            parent.addLamp(parent.labelText)
            parent.destroy()
        }
    }
}
