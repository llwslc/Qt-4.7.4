#ifndef CHECKINDIALOG_H
#define CHECKINDIALOG_H

#include <QDialog>
#include "func.h"

namespace Ui {
    class checkinDialog;
}

class checkinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit checkinDialog(QWidget *parent = 0);
    ~checkinDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void initComboBox();

    void showEvent(QShowEvent *);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_5_clicked();

private:
    Ui::checkinDialog *ui;
};

#endif // CHECKINDIALOG_H
