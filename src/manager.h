#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QDebug>

class manager : public QObject
{
    Q_OBJECT

public:
    explicit manager(QObject *parent = nullptr);
signals:
    void onConnect();
    void onDisconnect();
    void newLampAdded(QString id);
    void turnOn(QString id);
    void turnOff(QString id);
    void lampConnected(QString id);
    void lampDisconnected(QString id);
public slots:
    void addNewLamp(){
        qDebug() << "AddedNewLamp";
        emit newLampAdded("1");
    };
    void addConnected(int id){
        qDebug() << "AddedConnected";
        emit lampConnected("2");
    };
    void turnLampOn(){
        qDebug() << "Lamp turned on";
        emit turnOn("3");
    };
    void turnLampOff(){
        qDebug() << "Lamp turned off" ;
        emit turnOff("4");
    };

};

#endif // MANAGER_H
