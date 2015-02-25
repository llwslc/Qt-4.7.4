#ifndef NEWADDRESSDIALOG_H
#define NEWADDRESSDIALOG_H

#include "common.h"

namespace Ui {
class newAddressDialog;
}

class newAddressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newAddressDialog(QWidget *parent = 0);
    ~newAddressDialog();

    QString addressidString;
    QString personidString;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

    QString picPath;

signals:
    void newSignal();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::newAddressDialog *ui;
};

#endif // NEWADDRESSDIALOG_H
