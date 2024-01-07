#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QNetworkRequest>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include "lightclient.h"


class manager : public QObject
{
    Q_OBJECT

public:
    explicit manager(QObject *parent = nullptr);
private:
    QTcpServer *tcpServer = nullptr;
    QList <lightClient*> clientList;
    QList <QString> buttons;
    lightClient* getClient(QString id);
    bool isClient(QString id);
    bool isButton(QString id);
    void sendToClient(lightClient* client, QString msg);
    void clientNotFound();
    void readRegisteredDevices();
    void writeRegisterDevices();
    void addClient(QString id, QHostAddress addr);
    void isLampAvialable(QString id, QString addr);
    void getClientDataFromRegEntry(QString regEntry, QString *clientData);
    void addClientToListAndButton(QHostAddress addr, QString id);
    void clientDel(QString id);
    int getClientListId(QString id);
    int getButtonListId(QString id);
    void addAsAvaliable(QString id, QHostAddress addr);
private slots:
    void onConnect();
    void onDisconnect();
    void onMessage(QTcpSocket *client);
    void onStateChanged(QAbstractSocket::SocketState state);
signals:
    void newLampAdded(QString id, QString addr);
    void turnOn(QString id);
    void turnOff(QString id);
    void lampConnected(QString id);
    void lampDisconnected(QString id);
    void lampGone(QString id);
public slots:
    void addNewLamp(QString id, QString addr){
        qDebug() << "AddedNewLamp";
        this->addClientToListAndButton(QHostAddress(addr), id);
    };
    void addConnected(QString id){
        qDebug() << "AddedConnected";
        emit lampConnected(id);
    };
    void turnLampOn(QString id){
        qDebug() << "Lamp turned on " << id;



        sendToClient(getClient(id), "1");
        // emit turnOn("3");
    };
    void turnLampOff(QString id){
        qDebug() << "Lamp turned off" << id;
        isClient(id) == true ? sendToClient(getClient(id), "0") : clientNotFound();
    };
    void addToButtonList(QString id){
        // emit newLampAdded(id);
    };
};

#endif // MANAGER_H
