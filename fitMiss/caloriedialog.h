#ifndef CALORIEDIALOG_H
#define CALORIEDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class calorieDialog;
}

class calorieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit calorieDialog(QWidget *parent = 0);
    ~calorieDialog();

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

private:
    Ui::calorieDialog *ui;
};

#endif // CALORIEDIALOG_H
