#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "common.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QString sourcePath;

    int fileCount;
    int singerCount;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
