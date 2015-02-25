#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QtDebug>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QtNetwork>
#include <QHash>
#include <QtSql>
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
#include <Phonon/MediaObject>
#include <Phonon/VideoPlayer>
#include <phonon/audiooutput.h>
#include <phonon/seekslider.h>
#include <phonon/mediaobject.h>
#include <phonon/volumeslider.h>
#include <phonon/backendcapabilities.h>

namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    QNetworkAccessManager *ipNetworkAccessManager;   //ip解析

    QNetworkAccessManager *placeNetworkAccessManager; //地点解析

    QNetworkAccessManager *weatherNetworkAccessManager; //天气解析

    QString placeStr; //地点

    Phonon::SeekSlider *seekSlider;//滑动进度条
    Phonon::MediaObject *mediaObject;//管理媒体资源
    Phonon::AudioOutput *audioOutput;//连接物理设备
    Phonon::VolumeSlider *volumeSlider;//音量
    QToolBar *bar;
    QLCDNumber *timeLcd;//LCD表

    QAction *playAction;
    QAction *pauseAction;
    QAction *stopAction;

    QString musicFile;

    void showEvent(QShowEvent *);

    void paintEvent(QPaintEvent *);

    void ipAnalyze();

    void initDialog();

private slots:

    void ipNetworkReplyFinish(QNetworkReply *);

    void placeNetworkReplyFinish(QNetworkReply *);

    void weatherNetworkReplyFinish(QNetworkReply *);

    void webViewLoadFinished(bool);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void stateChanged(Phonon::State newState, Phonon::State oldState);
    void tick(qint64 time);
    void sourceChanged(const Phonon::MediaSource &source);
    void aboutToFinish();

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
