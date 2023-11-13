import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    width: 200
    height: 100
    property string labelText: "labelText"

    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 200
        height: 100
        color: "#00593737"

    }

    Label {
        id: label
        x: 49
        y: 8
        width: 103
        height: 33
        text: labelText
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pointSize: 15
    }

    Switch {
        id: switch1
        x: 42
        y: 42
        text: qsTr("on/off")
    }
}
