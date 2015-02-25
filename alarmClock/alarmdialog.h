#ifndef ALARMDIALOG_H
#define ALARMDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class alarmDialog;
}

class alarmDialog : public QDialog
{
    Q_OBJECT

public:
    explicit alarmDialog(QWidget *parent = 0);
    ~alarmDialog();

private slots:
    void on_timeEdit_timeChanged(const QTime &date);

    void on_timeEdit_2_timeChanged(const QTime &date);

    void on_timeEdit_3_timeChanged(const QTime &date);

    void on_timeEdit_4_timeChanged(const QTime &date);

    void on_timeEdit_5_timeChanged(const QTime &date);

    void on_checkBox_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_checkBox_4_clicked();

    void on_checkBox_5_clicked();

private:
    Ui::alarmDialog *ui;
};

#endif // ALARMDIALOG_H
