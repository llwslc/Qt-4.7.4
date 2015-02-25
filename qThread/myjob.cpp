#include "myjob.h"

myJob::myJob(QObject *parent) :
    QObject(parent)
{
    i = 0;
    pTimer = new QTimer(this);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(startThreadSlot()));
}

void myJob::startThreadSlot()
{
    i++;
    emit sendMyInt(i);

    qDebug() << "start : " << i;
    pTimer->start(1000);
}
