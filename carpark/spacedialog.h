#ifndef SPACEDIALOG_H
#define SPACEDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class spaceDialog;
}

class spaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit spaceDialog(QWidget *parent = 0);
    ~spaceDialog();

    QSqlRelationalTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::spaceDialog *ui;
};

#endif // SPACEDIALOG_H
