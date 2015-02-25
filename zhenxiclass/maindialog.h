#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "common.h"
#include "userdialog.h"
#include "studentdialog.h"
#include "idnumdialog.h"
#include "namedialog.h"
#include "phonedialog.h"
#include "stuiddialog.h"


namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    userDialog userw;
    studentDialog stuw;
    idnumDialog idnumw;
    nameDialog namew;
    phoneDialog phonew;
    stuidDialog stuidw;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
