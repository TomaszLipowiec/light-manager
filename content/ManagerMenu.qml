import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Studio.Components
import QtQuick.Studio.Effects
import QtQuick.Studio.LogicHelper
import QtQuick.Timeline 1.0

Item {
    id: managerMenu
    width: 1260
    height: 920
    property bool toManager: false
    property bool goToManager: false

    RoundButton {
        id: roundButton
        x: 420
        y: 250
        width: 420
        height: 420
        text: "START"
        font.pixelSize: 50

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton
            onClicked: (mouse)=> {
                managerMenu.goToManager = true
            }
        }

    }

    ArcItem {
        id: arc
        x: 406
        y: 237
        width: 447
        height: 447
        z: -1
        rotation: 0
        strokeWidth: 10
        strokeColor: "#137427"
        end: 0
        fillColor: "#00000000"
    }

    Timeline {
        id: startButton
        animations: [
            TimelineAnimation {
                id: startButtonAnimation
                onFinished: managerMenu.toManager = true
                loops: 1
                running: false
                duration: 1000
                to: 1000
                from: 0
            }
        ]
        startFrame: 0
        enabled: false
        endFrame: 1000

        KeyframeGroup {
            target: arc
            property: "end"
            Keyframe {
                frame: 1
                value: 1
            }

            Keyframe {
                frame: 703
                value: 360
            }
        }
    }
    states: [
        State {
            name: "goingToManager"
            when: managerMenu.goToManager == true

            PropertyChanges {
                target: startButton
                enabled: true
            }

            PropertyChanges {
                target: startButtonAnimation
                running: true
            }
        }

    ]
}
