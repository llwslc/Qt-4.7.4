#ifndef MYCOURSEDIALOG_H
#define MYCOURSEDIALOG_H

#include "common.h"

namespace Ui {
    class myCourseDialog;
}

class myCourseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit myCourseDialog(QWidget *parent = 0);
    ~myCourseDialog();

    void showEvent(QShowEvent *);

    QString userid;
    QString classid;

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::myCourseDialog *ui;
};

#endif // MYCOURSEDIALOG_H
