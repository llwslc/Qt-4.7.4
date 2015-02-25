#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>

#include "qexcel.h"
#include "common.h"
#include "database.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QStandardItemModel *stdModel;

    QTimer *timeUpdate;

    QTimer *autoRead;

    int autoReadFlag;

    QSqlQuery query;

private slots:

    void initDatabase();

    void updateTime();

    void readAuto();

    void readXlsFunc();

    void saveXlsFunc();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_8_clicked();

    void on_timeEdit_editingFinished();

    void on_timeEdit_2_editingFinished();

    void on_checkBox_clicked();

    void tableViewRowChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
