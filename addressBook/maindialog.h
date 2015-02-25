#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "common.h"
#include "logondialog.h"
#include "newaddressdialog.h"
#include "modaddressdialog.h"

namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    logonDialog logonw;
    newAddressDialog neww;
    modAddressDialog modw;

    QString personidString;

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

private slots:
    void init();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
