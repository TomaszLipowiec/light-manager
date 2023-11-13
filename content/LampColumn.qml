import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts

Item {
    id: lampColumn
    width: 1260
    height: 920

    QtObject{
        id: lightEngine

        function sf(){
            console.log("eo nn")
            appManager.addNewLamp()
        }

    }

    function switchLight(status,id)
    {
        console.log("ConFun! "+id+" "+status)
    }

    Connections{
        target: appManager
        function onNewLampAdded(id)
        {
            console.log("I got signal with id "+id)
        }

        function onLampConnected()
        {
            console.log("I got lamp connected with id "+id)
        }
    }

    signal addNewLamp(id: int)
    signal addConnected(id: int)
    signal turnOn(id: int)
    signal trunOff(id: int)

    function addLampLabel(id){
        var lampComponent = Qt.createComponent("NewLampLabel.qml")
        var obj = lampComponent.createObject(avaliableLamps)
        obj.labelText = id
        // obj.onClicked = addConnectedLamp(id)
        obj.addLamp.connect(addConnectedLamp)

        lightEngine.sf()
    }

    function addConnectedLamp(id){
        var lampComponent = Qt.createComponent("RemoteLamp.qml")
        var obj = lampComponent.createObject(connectedLamps)
        obj.labelText = id
        obj.switchLight.connect(switchLight)

            //     = function (){
            // if(obj.switchLight()){
            //     appManager.turnOn(id)
            // } else {
            //     appManager.turnOff(id)
            // }
        // }
    }

    Text {
        id: newLampSection
        x: 138
        y: 342
        text: qsTr("Add new remote lamp")
        font.pixelSize: 30
    }

    Column {
        id: connectedLamps
        x: 668
        width: 200
        height: 612
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        leftPadding: 0
        topPadding: 0
        anchors.verticalCenterOffset: 0
        anchors.leftMargin: 917
        spacing: 20
    }

    Column {
        id: avaliableLamps
        x: 100
        y: 400
        width: 400
        height: 400
        spacing: 15
        leftPadding: 25
    }

    Button {
        id: button
        x: 143
        y: 256
        text: qsTr("Add")
        onClicked: addLampLabel("New")
    }

    Button {
        id: button1
        x: 818
        y: 127
        text: qsTr("add")
        onClicked: addConnectedLamp("Conn")
    }

    Text {
        id: newLampSection1
        x: 900
        y: 67
        text: qsTr("Connected lamps")
        font.pixelSize: 30
        rotation: -0.145
    }

}
