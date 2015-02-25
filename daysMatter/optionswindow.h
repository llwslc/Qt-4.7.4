#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include <QMainWindow>
#include "common.h"

namespace Ui {
    class optionsWindow;
}

class optionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit optionsWindow(QWidget *parent = 0);
    ~optionsWindow();

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::optionsWindow *ui;
    void closeEvent(QCloseEvent *e);
};

#endif // OPTIONSWINDOW_H
