#ifndef STOREDIALOG_H
#define STOREDIALOG_H

#include "common.h"
#include "bgupitem.h"
#include "bgdownitem.h"
#include "manitem.h"
#include "thinkitem.h"
#include "recorddialog.h"
#include "listdialog.h"

namespace Ui {
    class storeDialog;
}

class storeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit storeDialog(QWidget *parent = 0);
    ~storeDialog();

    QGraphicsScene scene;
    int sceneWidth;
    int sceneHeight;

    int heartCount;

    bgUpItem *bgUp;
    bgDownItem *bgDown;
    manItem *man;
    thinkItem *think;

    recordDialog recordw;
    listDialog listw;

    int setCup;
    int setCol;

    int score;

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_clicked();

    void on_pushButton_19_clicked();

private:
    Ui::storeDialog *ui;
};

#endif // STOREDIALOG_H
