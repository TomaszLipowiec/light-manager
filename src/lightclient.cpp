#include "lightclient.h"

lightClient::lightClient(QObject *parent)
    : QObject{parent}
{}

lightClient::lightClient(QHostAddress address, QString name){
    this->address = address;
    this->name = name;
}

void lightClient::setAddress(QHostAddress addr)
{
    this->address = addr;
}
