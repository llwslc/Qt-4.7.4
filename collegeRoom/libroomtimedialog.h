#ifndef LIBROOMTIMEDIALOG_H
#define LIBROOMTIMEDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class libroomTimeDialog;
}

class libroomTimeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit libroomTimeDialog(QWidget *parent = 0);
    ~libroomTimeDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
    void initComboBox();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_tableView_clicked(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::libroomTimeDialog *ui;
};

#endif // LIBROOMTIMEDIALOG_H
