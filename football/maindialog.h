#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "mysqldata.h"
#include "accountsdialog.h"
#include "gamedialog.h"
#include "playerdialog.h"
#include "scoredialog.h"

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
    accountsDialog accw;
    gameDialog gamew;
    playerDialog playerw;
    scoreDialog scorew;
};

#endif // MAINDIALOG_H
