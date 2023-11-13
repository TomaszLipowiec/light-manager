import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: remoteLamp
    width: 200
    height: 100
    property string labelText: "labelText"
    property bool activaton: false

    signal switchLight(status: bool, id: string)

    // function switchLight(){
    //     console.log("switchLight")
    //     remoteLamp.activaton = !remoteLamp.activaton
    // }

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
        id: lightSwitch
        x: 42
        y: 42
        checked: false
        onCheckedChanged: {
            parent.activaton = !parent.activaton
            parent.switchLight(parent.activaton, parent.labelText)
        }
    }
}
