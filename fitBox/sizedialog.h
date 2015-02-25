#ifndef SIZEDIALOG_H
#define SIZEDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class sizeDialog;
}

class sizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sizeDialog(QWidget *parent = 0);
    ~sizeDialog();
void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::sizeDialog *ui;
};

#endif // SIZEDIALOG_H
