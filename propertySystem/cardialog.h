#ifndef CARDIALOG_H
#define CARDIALOG_H

#include <QDialog>
#include "mydatabase.h"

namespace Ui {
    class carDialog;
}

class carDialog : public QDialog
{
    Q_OBJECT

public:
    explicit carDialog(QWidget *parent = 0);
    ~carDialog();

    QSqlRelationalTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::carDialog *ui;
};

#endif // CARDIALOG_H
