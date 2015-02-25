#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QtDebug>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QtNetwork>
#include <QHash>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QByteArray>
#include <QObject>
#include <QWebView>
#include <QFile>
#include <QWebFrame>
#include <QDebug>
#include <QTextStream>
#include <QIODevice>
#include <QEvent>
#include <QNetworkConfigurationManager>

#include "win7tts.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Win7TTS tts;

    QTimer *timer;

    void closeEvent(QCloseEvent *);

private slots:
    void onlinetest();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
