// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import QtQuick 6.5
import LightManager
import QtQuick.Controls 6.5
import QtQuick.Timeline 1.0


Window {
    width: 1260
    height: 920

    visible: true
    title: "LightManagerFront"
    property bool darkMode: false

    ManagerMenu {
        id: menu
        x: 0
        y: 0
        visible: true
        z: 2
        enabled: true
    }

    Manager {
        id: manager
        x: 0
        y: 0
        visible: false
    }


    StateGroup {
        id: startManagement
        states: [
            State {
                name: "Manager State"
                when: menu.toManager == true

                PropertyChanges {
                    target: menu
                    visible: false
                }

                PropertyChanges {
                    target: manager
                    visible: true
                    z: 1
                }
            }
        ]
    }

    StateGroup {
        id: lightMode
        states: [
            State {
                name: "toDark"
                when: colorsSwitch.checked

                PropertyChanges {
                    target: rectangle
                    x: 0
                    y: 0
                    width: 0
                    height: 920
                    visible: true
                }

                PropertyChanges {
                    target: toDark
                    enabled: true
                }

                PropertyChanges {
                    target: toDarkAnimation
                    running: true
                }

                PropertyChanges {
                    target: gradientStop
                    color: "#ff00301b"
                }

            },
            State {
                name: "toLight"
                when: !colorsSwitch.checked

                PropertyChanges {
                    target: rectangle
                    x: 0
                    y: 0
                    width: 1260
                    height: 920
                    visible: true
                }

                PropertyChanges {
                    target: toLight
                    enabled: true
                }

                PropertyChanges {
                    target: toLightAnimation
                    running: true
                }

                PropertyChanges {
                    target: toLightAnimation
                }

                PropertyChanges {
                    target: toLightAnimation
                }

                PropertyChanges {
                    target: toDarkAnimation
                    running: true
                }

            }
        ]
    }

    Switch {
        id: colorsSwitch
        x: 1081
        y: 813
        scale: 2.5
        z: 2
    }


    Text {
        id: text1
        x: 991
        y: 717
        width: 240
        height: 69
        color: "#ffffff"
        text: qsTr("Switch colors")
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        z: 4
    }


    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 0
        height: 920
        visible: false
        gradient: Gradient {
            orientation: Gradient.Vertical

            GradientStop {
                id: gradientStop
                position: 0
                color: "#ff00301b"
            }

            GradientStop {
                position: 1
                color: "#3e3e3e"
            }
        }
        z: 0
    }

    Timeline {
        id: toLight
        animations: [
            TimelineAnimation {
                id: toLightAnimation
                duration: 1000
                loops: 1
                running: false
                to: 1000
                from: 0
            }
        ]
        enabled: false
        startFrame: 0
        endFrame: 1000

        KeyframeGroup {
            target: rectangle
            property: "width"

            Keyframe {
                frame: 1
                value: 1260
            }

            Keyframe {
                frame: 700
                value: 0
            }
        }
    }

    Timeline {
        id: toDark
        animations: [
            TimelineAnimation {
                id: toDarkAnimation
                duration: 1000
                loops: 1
                running: false
                to: 1000
                from: 0
            }
        ]
        enabled: false
        startFrame: 0
        endFrame: 1000

        KeyframeGroup {
            target: rectangle
            property: "width"


            Keyframe {
                frame: 1
                value: 0
            }

            Keyframe {
                frame: 700
                value: 1260
            }
        }
    }

}
