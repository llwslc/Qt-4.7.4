#ifndef PICSHOWDIALOG_H
#define PICSHOWDIALOG_H

#include <QDialog>
#include "myfunc.h"

namespace Ui {
class picShowDialog;
}

class picShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit picShowDialog(QWidget *parent = 0);
    ~picShowDialog();

    int totalInt;
    int curInt;

    QTimer *timer;

    void showEvent(QShowEvent *);

    void paintEvent(QPaintEvent *);

private slots:
    void checkTimeOut();
private:
    Ui::picShowDialog *ui;
};

#endif // PICSHOWDIALOG_H
