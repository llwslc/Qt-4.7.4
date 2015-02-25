#ifndef FISHDIALOG_H
#define FISHDIALOG_H

#include <QDialog>
#include "common.h"
#include "listdialog.h"
#include "recorddialog.h"
#include "mouse.h"
#include "fishitem.h"
#include "baritem.h"
#include "cannonitem.h"
#include "bulletitem.h"
#include "pauseitem.h"
#include "aboutitem.h"

enum gameFlag{MAIN = 0, START, PAUSE};

namespace Ui {
    class fishDialog;
}

class fishDialog : public QDialog
{
    Q_OBJECT

public:
    explicit fishDialog(QWidget *parent = 0);
    ~fishDialog();

    QGraphicsScene scene;

    QTimer FishSwimTimer;
    QTimer FishOutTimer;
    QTimer GameTimer;

    int gameStart;

    barItem *bar;
    cannonItem *cannon;
    pauseItem *pause;
    aboutItem *about;

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QMouseEvent *);

private slots:
    void FishOut();
    void GameOver();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::fishDialog *ui;
    listDialog listw;
    recordDialog recordw;
};

#endif // FISHDIALOG_H
