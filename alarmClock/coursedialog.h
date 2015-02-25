#ifndef COURSEDIALOG_H
#define COURSEDIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class courseDialog;
}

class courseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit courseDialog(QWidget *parent = 0);
    ~courseDialog();

    void showEvent(QShowEvent *);

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::courseDialog *ui;
};

#endif // COURSEDIALOG_H
