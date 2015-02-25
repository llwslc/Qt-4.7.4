#ifndef USERROOMDIALOG_H
#define USERROOMDIALOG_H

#include <QDialog>
#include "common.h"
#include "roomitem.h"
#include "lightoneitem.h"
#include "lighttwoitem.h"
#include "lightthritem.h"
#include "timeitem.h"
#include "win_qextserialport.h"

namespace Ui {
    class userRoomDialog;
}

class userRoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit userRoomDialog(QWidget *parent = 0);
    ~userRoomDialog();

    QGraphicsScene scene;

    roomItem *room;
    timeItem *time;

    lightOneItem *light1;
    lightTwoItem *light2;
    lightThrItem *light3;

    QTimer *lightTimer;
    Win_QextSerialPort *myCom;//´®¿Ú

private slots:
    void readMyCom();

    void lightAuto();

    void lightTimeOut();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

    void on_checkBox_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_timeEdit_timeChanged(const QTime &date);

    void on_timeEdit_2_timeChanged(const QTime &date);

    void on_timeEdit_3_timeChanged(const QTime &date);

    void on_timeEdit_4_timeChanged(const QTime &date);

    void on_timeEdit_5_timeChanged(const QTime &date);

    void on_timeEdit_6_timeChanged(const QTime &date);

private:
    Ui::userRoomDialog *ui;
};

#endif // USERROOMDIALOG_H
