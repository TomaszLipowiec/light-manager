#include "manager.h"

void manager::onConnect()
{
    qDebug() << "Got new client conn! ";
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QAbstractSocket::disconnected, clientConnection, &QObject::deleteLater);
    connect(clientConnection, &QAbstractSocket::stateChanged, this, &manager::onStateChanged);

    qDebug() << "Client addr: "  << clientConnection->peerAddress().toString();
    qDebug() << "Client state: "  << clientConnection->state();

    QByteArray block;
    QDataStream outStream(&block, QIODevice::WriteOnly);
    outStream.setVersion(QDataStream::Qt_6_5);

    outStream << "lm-conn\n";

    connect(clientConnection, &QAbstractSocket::readyRead, this, [=](){
        onMessage(clientConnection);
    });

    clientConnection->write(block);
}

void manager::onDisconnect(){
    qDebug() << "Client is gone!";
}

void manager::onStateChanged(QAbstractSocket::SocketState state){
    qDebug() << "Client changed state: " << state;
}

void manager::onMessage(QTcpSocket *client){
    QByteArray msg;
    msg = client->readAll();
    if(msg[0] == 'l' && msg[1] == 'm')
    {
        //Add avaliable lamp with name
        qDebug() << "Emiting new lamp " << msg;
        emit newLampAdded(QString(msg));

        if(isClient(msg)){
            getClient(msg)->setAddress(client->peerAddress());
        } else {
            lightClient* newClient = new lightClient(client->peerAddress(), msg);
            clientList.append(newClient);
        }
    }
    client->disconnectFromHost();
}

void manager::sendToClient(lightClient* client, QString msg){
    QByteArray block;
    QDataStream outStream(&block, QIODevice::WriteOnly);
    outStream.setVersion(QDataStream::Qt_6_5);
    outStream << msg << "\n";

    QString ip = "http://"+client->address.toString()+"/lm-comm="+msg;
    QNetworkRequest lamp;
    lamp.setUrl(QUrl(ip));

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished,
            this, [=](){
        qDebug() << "Requested";

        QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
        if (reply) {
            // Getting the HTTP status code
            QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            if (statusCode.isValid()) {
                int status = statusCode.toInt();
                qDebug() << "HTTP Status Code:" << status;
            }
            // Additional processing...
            reply->deleteLater();
        } else {
            qDebug() << "No reply";
        }

    } );
    manager->get(lamp);
    qDebug() << "Sended";
}

bool manager::isClient(QString id)
{
    for (qsizetype i = 0; i < clientList.size(); ++i) {
        if (clientList.at(i)->name == id)
        {
            return true;
        }
    }
    return false;
}

lightClient* manager::getClient(QString id)
{
    lightClient *client;
    for (qsizetype i = 0; i < clientList.size(); ++i) {
        if (clientList.at(i)->name == id)
        {
            client = clientList.at(i);
        }
    }
    return client;
}

void manager::clientNotFound(){
    qDebug() << "Client not found";
}

manager::manager(QObject *parent)
    : QObject{parent}
{
    tcpServer = new QTcpServer(this);

    QString ip = "192.168.150.16";
    QHostAddress addr = QHostAddress(ip);

    if(!tcpServer->listen(addr, 35000)){
        qDebug() << "Unable to start the server!";
        return;
    }

    qDebug() << "The server is runing on:" << ip << "\n\n port:" << tcpServer->serverPort();

    connect(tcpServer, &QTcpServer::newConnection, this, &manager::onConnect);
    connect(this, &manager::newLampAdded, this, &manager::addNewLamp);

    readRegisteredDevices();
}

void manager::readRegisteredDevices(){
    QFile devReg("devices.txt");
    if(!devReg.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&devReg);
    while(!in.atEnd()){
        QString line = devReg.readLine();

    }

}

void manager::writeRegisterDevices(){
    QFile devReg("devices.txt");
    if(!devReg.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&devReg);
    for (qsizetype i = 0; i < clientList.size(); ++i) {

    }
    // out <<
}
