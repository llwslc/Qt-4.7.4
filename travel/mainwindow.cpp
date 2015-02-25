#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //景点
    placew.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    //酒店
    hotelw.show();
}

void MainWindow::on_pushButton_3_clicked()
{
    //地图
    mapw.show();
}

void MainWindow::on_pushButton_4_clicked()
{
    //人员
    userw.show();
}
