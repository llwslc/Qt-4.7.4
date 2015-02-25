#ifndef CRACKERDIALOG_H
#define CRACKERDIALOG_H

#include "common.h"

namespace Ui {
    class crackerDialog;
}

class crackerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit crackerDialog(QWidget *parent = 0);
    ~crackerDialog();

    void init();
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::crackerDialog *ui;
};

#endif // CRACKERDIALOG_H
