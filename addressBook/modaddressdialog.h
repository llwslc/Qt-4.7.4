#ifndef MODADDRESSDIALOG_H
#define MODADDRESSDIALOG_H

#include "common.h"

namespace Ui {
class modAddressDialog;
}

class modAddressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit modAddressDialog(QWidget *parent = 0);
    ~modAddressDialog();

    QString addressidString;
    QString personidString;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

    QString picPath;

signals:
    void modSignal();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::modAddressDialog *ui;
};

#endif // MODADDRESSDIALOG_H
