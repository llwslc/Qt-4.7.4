#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include <QDialog>
#include "myfunc.h"

namespace Ui {
    class messageDialog;
}

class messageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit messageDialog(QWidget *parent = 0);
    ~messageDialog();

    void paintEvent(QPaintEvent *);

private:
    Ui::messageDialog *ui;
};

#endif // MESSAGEDIALOG_H
