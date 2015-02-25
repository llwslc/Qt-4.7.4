#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTimeOut()));
    timer->start(1000);

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);
    Phonon::createPath(mediaObject, audioOutput);

    mediaObject->setTickInterval(1000);
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::on_pushButton_clicked()
{
    //课程管理
    coursew.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //闹钟管理
    alarmw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //铃声管理
    musicw.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //人员管理
    userw.show();
}


void mainDialog::checkTimeOut()
{
    //闹钟
    QSqlQuery query;
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    QString alarmclock = QString("");
    QString musicPath = QString("");

    query.exec("select alarmclock from alarmtime where userid = " + userid);
    while(query.next())
    {
        alarmclock = query.value(0).toString();
    }

    if(currentTime == alarmclock)
    {
        //播放歌曲
        query.exec("select path from music where alarmsing = 1");
        while(query.next())
        {
            musicPath = query.value(0).toString();
        }
        if(musicPath.isEmpty())
        {
            //NULL
        }
        else
        {
            mediaObject->stop();
            mediaObject->setCurrentSource(Phonon::MediaSource(musicPath));
            mediaObject->play();
        }

        QMessageBox message(QMessageBox::NoIcon, "timeOut", "Time out!", QMessageBox::Yes, NULL);
        if(message.exec() == QMessageBox::Yes)
        {
                mediaObject->stop();
        }
    }
}

void mainDialog::on_pushButton_5_clicked()
{
    //日历管理
    mainw.show();
}
