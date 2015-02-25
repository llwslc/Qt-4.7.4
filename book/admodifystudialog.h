#ifndef ADMODIFYSTUDIALOG_H
#define ADMODIFYSTUDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
class adModifyStuDialog;
}

class adModifyStuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adModifyStuDialog(QWidget *parent = 0);
    ~adModifyStuDialog();

    QString picPath;

    void showEvent(QShowEvent *);

signals:
    void modifyStu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::adModifyStuDialog *ui;
};

#endif // ADMODIFYSTUDIALOG_H
