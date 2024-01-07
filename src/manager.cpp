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
        this->addClient(msg, client->peerAddress());
    }
    client->disconnectFromHost();
}

void manager::sendToClient(lightClient* client, QString msg){

    QString ip = "http://"+client->address.toString()+"/lm-comm="+msg;
    QNetworkRequest lamp;
    lamp.setUrl(QUrl(ip));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->get(lamp);
    int returnedStatus;
    connect(manager, &QNetworkAccessManager::finished,
            this, [=](){
        QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        if (statusCode.isValid()) {
            int status = statusCode.toInt();
            qDebug() << "HTTP Status Code:" << status;
        } else {
            this->clientDel(client->name);
        }
    } );
}

bool manager::isClient(QString id)
{
    qDebug() << "IsClient clientList size: " << clientList.size();
    for (qsizetype i = 0; i < clientList.size(); ++i) {
        qDebug() << "Searching: " << clientList.at(i)->name;
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
    qDebug() << "GetClient clientList size: " << clientList.size();
    for (qsizetype i = 0; i < clientList.size(); ++i) {
        if (clientList.at(i)->name == id)
        {
            client = clientList.at(i);
        }
    }

    qDebug() << "Got client!";

    return client;
}

int manager::getClientListId(QString id)
{
    int clientListId;
    for (qsizetype i = 0; i < clientList.size(); ++i) {
        if (clientList.at(i)->name == id)
        {
            clientListId = i;
        }
    }
    return clientListId;
}

int manager::getButtonListId(QString id)
{
    int buttonListId;
    for (qsizetype i = 0; i < clientList.size(); ++i) {
        if (buttons.at(i) == id)
        {
            buttonListId = i;
        }
    }
    return buttonListId;
}

void manager::clientNotFound(){
    qDebug() << "Client not found";
}

manager::manager(QObject *parent)
    : QObject{parent}
{
    this->writeRegisterDevices();

    tcpServer = new QTcpServer(this);

    QString ip = "192.168.150.16";
    QHostAddress addr = QHostAddress(ip);

    if(!tcpServer->listen(addr, 35000)){
        qDebug() << "Unable to start the server!";
        return;
    }

    qDebug() << "The server is runing on:" << ip << "\n\n port:" << tcpServer->serverPort();

    connect(tcpServer, &QTcpServer::newConnection, this, &manager::onConnect);
    //connect(this, &manager::newLampAdded, this, &manager::addNewLamp);

    this->readRegisteredDevices();
}

void manager::readRegisteredDevices(){
    qDebug() << "Reading register";
    QFile devReg("devices.txt");
    if(!devReg.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&devReg);
    while(!in.atEnd()){
        QString line = devReg.readLine();
        qDebug() << "Readed line: " << line;
        QString *clientData = new QString[2];
        this->getClientDataFromRegEntry(line, clientData);
        this->isLampAvialable(clientData[0], clientData[1]);
    }
}

void manager::writeRegisterDevices(){
    qDebug() << "Writing register!";
    QFile devReg("devices.txt");
    if(!devReg.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    devReg.resize(0);

    QTextStream out(&devReg);
    for (qsizetype i = 0; i < clientList.size(); ++i) {
        out << this->clientList.at(i)->name << "," << this->clientList.at(i)->address.toString() << "\n";
    }
}

bool manager::isButton(QString id){
    for (qsizetype i = 0; i < buttons.size(); ++i) {
        if (buttons.at(i) == id)
        {
            return true;
        }
    }
    return false;
}

void manager::addClient(QString id, QHostAddress addr){
    //Add avaliable lamp with name
    qDebug() << "Emiting new lamp " << id;
    if(isClient(id)){
        this->getClient(id)->setAddress(addr);
    } else {
        this->addAsAvaliable(id, addr);
        // this->addClientToListAndButton(addr, id);
    }
}

void manager::isLampAvialable(QString id, QString addr){

    QString ip = "http://"+addr+"/lm-comm=2="+id;
    QNetworkRequest lamp;
    lamp.setUrl(QUrl(ip));
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply* reply = manager->get(lamp);

    qDebug() << "Is lam av!";

    connect(manager, &QNetworkAccessManager::finished,
        this, [=](){
            QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            if (statusCode.isValid()) {
                int status = statusCode.toInt();
                if(status == 200){
                    addClientToListAndButton(QHostAddress(addr), id);
                }
            } else {
                if(this->isButton(id))
                {
                    this->clientDel(id);
                }
            }
    } );
}

void manager::clientDel(QString id){
    this->clientList.removeAt(this->getClientListId(id));
    this->buttons.removeAt(this->getButtonListId(id));
    emit lampGone(id);
    this->writeRegisterDevices();
}

void manager::addClientToListAndButton(QHostAddress addr, QString id)
{
    lightClient* newClient = new lightClient(addr, id);
    if(!this->isButton(id))
    {
        emit lampConnected(id);
    }
    clientList.append(newClient);
    this->writeRegisterDevices();
}

void manager::getClientDataFromRegEntry(QString regEntry, QString *clientData){
    int commaPlace = 0;
    QString addr;
    for (qsizetype i = 0; i < regEntry.size(); i++) {
        if (regEntry.at(i) == QChar(',')){
            qDebug() << "Found comma";
            clientData[0] = regEntry.sliced(0, i);
            commaPlace = i;
        }
        if( commaPlace != 0 && i > commaPlace && ((regEntry.at(i) >= QChar('0')) && (regEntry.at(i) <= QChar('9'))) || regEntry.at(i) == QChar('.') )
        {
            addr.append(regEntry.at(i));
        }
    }
    clientData[1] = addr;
}

void manager::addAsAvaliable(QString id, QHostAddress addr){
   emit newLampAdded(id, addr.toString());
}
