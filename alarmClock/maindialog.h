#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "common.h"
#include "alarmdialog.h"
#include "coursedialog.h"
#include "musicdialog.h"
#include "userdialog.h"
#include "mainwindow.h"

namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    alarmDialog alarmw;
    courseDialog coursew;
    musicDialog musicw;
    userDialog userw;
    MainWindow mainw;

    QTimer *timer;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void checkTimeOut();

    void on_pushButton_5_clicked();

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
