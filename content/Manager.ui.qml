

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Item {
    id: main
    width: 1260
    height: 920

    transformOrigin: Item.Center

    Text {
        id: managerTitle
        x: 120
        y: 90
        width: 350
        height: 82
        text: qsTr("Light manager")
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    LampColumn {
        id: lampColumn
        x: 0
        y: 0
    }
    states: [
        State {
            name: "Start"
        }
    ]
}
