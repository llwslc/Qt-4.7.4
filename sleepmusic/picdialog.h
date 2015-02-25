#ifndef PICDIALOG_H
#define PICDIALOG_H

#include <QDialog>
#include "myfunc.h"

namespace Ui {
    class picDialog;
}

class picDialog : public QDialog
{
    Q_OBJECT

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

    void paintEvent(QPaintEvent *);

signals:
    void addPic();

public:
    explicit picDialog(QWidget *parent = 0);
    ~picDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::picDialog *ui;
};

#endif // PICDIALOG_H
