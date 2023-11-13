#include "manager.h"

manager::manager(QObject *parent)
    : QObject{parent}
{}
void manager::test(){
    qDebug() << "TEST";
}
