#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "common.h"
#include "cardialog.h"
#include "incomedialog.h"
#include "spacedialog.h"
#include "userdialog.h"

namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::mainDialog *ui;
    carDialog carw;
    spaceDialog spacew;
    incomeDialog incomew;
    userDialog userw;
};

#endif // MAINDIALOG_H
