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
    lightClient* getClient(QString id);
    bool isClient(QString id);
    void sendToClient(lightClient* client, QString msg);
    void clientNotFound();
    void readRegisteredDevices();
    void writeRegisterDevices();
private slots:
    void onConnect();
    void onDisconnect();
    void onMessage(QTcpSocket *client);
    void onStateChanged(QAbstractSocket::SocketState state);
signals:
    void newLampAdded(QString id);
    void turnOn(QString id);
    void turnOff(QString id);
    void lampConnected(QString id);
    void lampDisconnected(QString id);
public slots:
    void addNewLamp(QString id){
        qDebug() << "AddedNewLamp";

    };
    void addConnected(int id){
        qDebug() << "AddedConnected";
        emit lampConnected("2");
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

};

#endif // MANAGER_H
