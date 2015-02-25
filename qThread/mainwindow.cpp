#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    pMyJob = new myJob;
    pMyThread = new QThread;
    pMyJob->moveToThread(pMyThread);
    connect(pMyThread, SIGNAL(started()), pMyJob, SLOT(startThreadSlot()));
    connect(pMyJob, SIGNAL(sendMyInt(int)), this, SLOT(getMyJobInt(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    pMyThread->start();
}

void MainWindow::on_pushButton_2_clicked()
{
    pMyThread->quit();
}

void MainWindow::getMyJobInt(int i)
{
    qDebug() << "get : " << i;
}

void MainWindow::on_pushButton_3_clicked()
{
    pMyJob->startThreadSlot();
}
