#ifndef ADMODIFYBOOKDIALOG_H
#define ADMODIFYBOOKDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
class adModifyBookDialog;
}

class adModifyBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adModifyBookDialog(QWidget *parent = 0);
    ~adModifyBookDialog();

    void showEvent(QShowEvent *);

signals:
    void modifyBook();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::adModifyBookDialog *ui;
};

#endif // ADMODIFYBOOKDIALOG_H
