#ifndef ADSTUDIALOG_H
#define ADSTUDIALOG_H

#include <QDialog>
#include "mydatabase.h"
#include "admodifystudialog.h"

namespace Ui {
class adStuDialog;
}

class adStuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adStuDialog(QWidget *parent = 0);
    ~adStuDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

    QString picPath;

signals:
    void addStu();

private slots:
    void updateStuTable();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::adStuDialog *ui;
    adModifyStuDialog adModifyStuw;
};

#endif // ADSTUDIALOG_H
