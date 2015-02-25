#ifndef USINFODIALOG_H
#define USINFODIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class usInfoDialog;
}

class usInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit usInfoDialog(QWidget *parent = 0);
    ~usInfoDialog();

    QString stuCode;

    void setStuCode(QString);

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::usInfoDialog *ui;
};

#endif // USINFODIALOG_H
