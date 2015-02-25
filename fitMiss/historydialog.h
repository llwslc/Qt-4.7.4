#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class historyDialog;
}

class historyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit historyDialog(QWidget *parent = 0);
    ~historyDialog();

    void paintEvent(QPaintEvent *);
    QSqlTableModel *currentTableModel;
    QTableView *currentView;

private slots:
    void on_pushButton_clicked();

private:
    Ui::historyDialog *ui;
};

#endif // HISTORYDIALOG_H
