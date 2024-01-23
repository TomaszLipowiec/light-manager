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
        if(status){
            appManager.turnLampOn(id)
        }
        else{
            appManager.turnLampOff(id);
        }
    }

    Connections{
        target: appManager
        function onNewLampAdded(id, addr)
        {
            console.log("I got signal with id "+id);
            addLampLabel(id, addr);
        }

        function onLampConnected(id, addr)
        {
            //console.log("I got lamp connected with id "+id+"  "+adrr);
            //addConnectedLamp(id);

        }

        function onLampGone(id)
        {
            for(let i=0; i<connectedLamps.children.length; i++){
                if(connectedLamps.children[i].labelText == id)
                {
                    connectedLamps.children[i].destroy();
                }
            }
        }
    }

    signal addNewLamp(id: int)
    signal addConnected(id: int)
    signal turnOn(id: int)
    signal trunOff(id: int)

    function addLampLabel(id, addr){
        var lampComponent = Qt.createComponent("NewLampLabel.qml")
        var obj = lampComponent.createObject(avaliableLamps)
        obj.labelText = id
        obj.clientAddr = addr
        // obj.onClicked = addConnectedLamp(id)
        obj.addLamp.connect(addConnectedLamp)
    }

    function addConnectedLamp(id, addr){
        var lampComponent = Qt.createComponent("RemoteLamp.qml")
        var obj = lampComponent.createObject(connectedLamps)
        obj.labelText = id
        appManager.addNewLamp(id, addr);
        obj.switchLight.connect(switchLight);
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

    Text {
        id: newLampSection1
        x: 900
        y: 67
        text: qsTr("Connected lamps")
        font.pixelSize: 30
        rotation: -0.145
    }

}
