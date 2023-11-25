#ifndef LIGHTCLIENT_H
#define LIGHTCLIENT_H

#include <QObject>
#include <QTcpSocket>

class lightClient : public QObject
{
    Q_OBJECT
public:
    explicit lightClient(QObject *parent = nullptr);
    lightClient(QHostAddress address, QString name);
    QHostAddress address;
    QString name;
    void setAddress(QHostAddress);
signals:
};

#endif // LIGHTCLIENT_H
