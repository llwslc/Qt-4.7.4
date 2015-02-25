#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tts.initSpeech();
    ui->horizontalSlider->setValue((tts.rate()+10)*5);
    ui->horizontalSlider_2->setValue(tts.volume());

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onlinetest()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
}

void MainWindow::onlinetest()
{
}

void MainWindow::on_pushButton_clicked()
{
    //·¢Éú
    QString text = ui->plainTextEdit->toPlainText();
    tts.speak(text);
}

void MainWindow::on_pushButton_2_clicked()
{
    tts.stop();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    //0~99 -> -10~10
    value = (value+1)/5-10;
    tts.setRate(value);
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    tts.setVolume(value);
}
