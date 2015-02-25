#ifndef PHONEDIALOG_H
#define PHONEDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class phoneDialog;
}

class phoneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit phoneDialog(QWidget *parent = 0);
    ~phoneDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::phoneDialog *ui;
};

#endif // PHONEDIALOG_H
