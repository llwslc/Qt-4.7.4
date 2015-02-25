#ifndef MYJOB_H
#define MYJOB_H

#include <QObject>
#include <QThread>
#include <qDebug>
#include <QTimer>

class myJob : public QObject
{
    Q_OBJECT
public:
    explicit myJob(QObject *parent = 0);

    int i;
    QTimer *pTimer;

signals:
    void sendMyInt(int i);

public slots:
    void startThreadSlot();

};

#endif // MYJOB_H
