#ifndef SGROUPDIALOG_H
#define SGROUPDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class sgroupDialog;
}

class sgroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit sgroupDialog(QWidget *parent = 0);
    ~sgroupDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

    void showEvent(QShowEvent *);

private slots:

    void initComboBox_2();

    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::sgroupDialog *ui;
};

#endif // SGROUPDIALOG_H
