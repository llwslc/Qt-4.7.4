#ifndef STAFFDIALOG_H
#define STAFFDIALOG_H

#include <QDialog>
#include "myfunc.h"
#include "wardrobedialog.h"
#include "passworddialog.h"

namespace Ui {
    class staffDialog;
}

class staffDialog : public QDialog
{
    Q_OBJECT

public:
    explicit staffDialog(QWidget *parent = 0);
    ~staffDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::staffDialog *ui;
    wardrobeDialog warw;
    passwordDialog pwdw;
};

#endif // STAFFDIALOG_H
