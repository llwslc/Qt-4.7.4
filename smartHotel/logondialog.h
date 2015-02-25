#ifndef LOGONDIALOG_H
#define LOGONDIALOG_H

#include <QDialog>
#include "common.h"
#include "admindialog.h"
#include "userroomdialog.h"
#include "win_qextserialport.h"

namespace Ui {
    class logonDialog;
}

class logonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit logonDialog(QWidget *parent = 0);
    ~logonDialog();

    adminDialog adminw;
    userRoomDialog *userw;
    Win_QextSerialPort *myCom;//´®¿Ú

private slots:
    void readMyCom();

    void on_loginBut_clicked();

    void on_cancelBut_clicked();

private:
    Ui::logonDialog *ui;
};

#endif // LOGONDIALOG_H
