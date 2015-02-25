#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    audioOutput = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    mediaObject = new Phonon::MediaObject(this);

    connect(mediaObject, SIGNAL(tick(qint64)), this, SLOT(tick(qint64)));
    connect(mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
            this, SLOT(stateChanged(Phonon::State,Phonon::State)));
    connect(mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
            this, SLOT(sourceChanged(Phonon::MediaSource)));
    connect(mediaObject, SIGNAL(aboutToFinish()), this, SLOT(aboutToFinish()));

    Phonon::createPath(mediaObject, audioOutput);

    playAction = new QAction(style()->standardIcon(QStyle::SP_MediaPlay), tr("Play"), this);
    playAction->setShortcut(tr("Ctrl+P"));
    playAction->setDisabled(true);
    pauseAction = new QAction(style()->standardIcon(QStyle::SP_MediaPause), tr("Pause"), this);
    pauseAction->setShortcut(tr("Ctrl+A"));
    pauseAction->setDisabled(true);
    stopAction = new QAction(style()->standardIcon(QStyle::SP_MediaStop), tr("Stop"), this);
    stopAction->setShortcut(tr("Ctrl+S"));
    stopAction->setDisabled(true);

    connect(playAction, SIGNAL(triggered()), mediaObject, SLOT(play()));
    connect(pauseAction, SIGNAL(triggered()), mediaObject, SLOT(pause()) );
    connect(stopAction, SIGNAL(triggered()), mediaObject, SLOT(stop()));

    seekSlider = new Phonon::SeekSlider(this);
    seekSlider->setMediaObject(mediaObject);

    QPalette palette;
    palette.setBrush(QPalette::Light, Qt::darkGray);
    timeLcd = new QLCDNumber;
    timeLcd->setPalette(palette);

    bar = new QToolBar;
    bar->addAction(playAction);
    bar->addAction(pauseAction);
    bar->addAction(stopAction);

    volumeSlider = new Phonon::VolumeSlider(this);
    volumeSlider->setAudioOutput(audioOutput);
    volumeSlider->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

    QHBoxLayout *seekerLayout = new QHBoxLayout;
    seekerLayout->addWidget(seekSlider);
    seekerLayout->addWidget(timeLcd);

    QHBoxLayout *playbackLayout = new QHBoxLayout;
    playbackLayout->addWidget(bar);
    playbackLayout->addStretch();
    playbackLayout->addWidget(volumeSlider);
    playbackLayout->addWidget(ui->comboBox);
    playbackLayout->addWidget(ui->pushButton_6);

    QHBoxLayout *musicLayout = new QHBoxLayout;
    musicLayout->addStretch();
    musicLayout->addWidget(ui->label_4);
    musicLayout->addWidget(ui->timeEdit_2);
    musicLayout->addWidget(ui->pushButton_9);
    musicLayout->addWidget(ui->pushButton_8);
    musicLayout->addWidget(ui->pushButton_7);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(seekerLayout);
    mainLayout->addLayout(playbackLayout);
    mainLayout->addLayout(musicLayout);

    ui->groupBox_3->setLayout(mainLayout);

    timeLcd->display("00:00");

    mediaObject->setTickInterval(1000);

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(":/background.png"));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTimeOut()));
    timer->start(1000);

    QSqlQuery query;
    query.exec("select alarmclock from alarmtime where alarmtimeid = 1");
    while(query.next())
        ui->timeEdit->setTime(QTime::fromString(query.value(0).toString(), "hh:mm:ss"));

    musicFlag = false;

    musicTick = 0;

    connect(&musicw, SIGNAL(addMusic()), this, SLOT(initComboBox()));
    connect(&picw, SIGNAL(addPic()), this, SLOT(initComboBox()));

    initComboBox();

    ui->label_3->setScaledContents(true);
    query.exec("select pic from alarmtime where alarmtimeid = 1");
    while(query.next())
        ui->label_3->setPixmap(QPixmap(query.value(0).toString()));

    query.exec("select musictime from alarmtime where alarmtimeid = 1");
    while(query.next())
        ui->timeEdit_2->setTime(QTime::QTime(query.value(0).toInt()/3600, query.value(0).toInt()/60%60, query.value(0).toInt()%60));

    tryListen = false;
    tryMusicTick = 0;
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/frame.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void mainDialog::on_pushButton_clicked()
{
    //设置闹钟
    QSqlQuery query;
    query.exec("update alarmtime set alarmclock = '" + ui->timeEdit->dateTime().toString("hh:mm:ss") + "' where alarmtimeid = 1");

    QMessageBox::information(NULL, "success", "time set successfully!");
}

void mainDialog::on_comboBox_currentIndexChanged(int index)
{
    //音乐选项卡
}

void mainDialog::on_pushButton_8_clicked()
{
    //试听歌曲
    tryListen = true;

    QString title = ui->comboBox->currentText();
    QString musicPath;
    QSqlQuery query;

    query.exec("select path from music where name = '" + title + "'");
    while(query.next())
        musicPath = query.value(0).toString();

    mediaObject->stop();
    mediaObject->setCurrentSource(Phonon::MediaSource(musicPath));
    mediaObject->play();
}

void mainDialog::on_pushButton_7_clicked()
{
    //设为闹铃
    QString title = ui->comboBox->currentText();
    QString musicPath;
    QSqlQuery query;

    query.exec("select path from music where name = '" + title + "'");
    while(query.next())
        musicPath = query.value(0).toString();

    query.exec("update alarmtime set music = '" + musicPath + "' where alarmtimeid = 1");

    QMessageBox::information(NULL, "success", "music set successfully!");
}

void mainDialog::on_pushButton_9_clicked()
{
    //音乐播放时长设置
    int musictime = 0;
    QSqlQuery query;

    musictime = ui->timeEdit_2->dateTime().toString("h").toInt()*3600 + ui->timeEdit_2->dateTime().toString("m").toInt()*60 + ui->timeEdit_2->dateTime().toString("s").toInt();

    query.exec("update alarmtime set musictime = '" + QString::number(musictime, 10) + "' where alarmtimeid = 1");

    QMessageBox::information(NULL, "success", "time set successfully!");
}

void mainDialog::on_pushButton_6_clicked()
{
    //添加歌曲
    musicw.show();
}

void mainDialog::on_comboBox_2_currentIndexChanged(int index)
{
    //图片组合框
    QString picPath;
    QSqlQuery query;

    query.exec("select path from pic where name = '" + ui->comboBox_2->currentText() + "'");
    while(query.next())
    {
        picPath = query.value(0).toString();
    }

    ui->label_3->setScaledContents(true);
    ui->label_3->setPixmap(QPixmap(picPath));
}

void mainDialog::on_pushButton_2_clicked()
{
    //添加图片
    picw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //上一张
    if(ui->comboBox_2->currentIndex() == 0)
    {
        return;
    }
    else
    {
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->currentIndex()-1);
    }
}

void mainDialog::on_pushButton_4_clicked()
{
    //下一张
    if(ui->comboBox_2->currentIndex() == ui->comboBox_2->count()-1)
    {
        return;
    }
    else
    {
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->currentIndex()+1);
    }
}


void mainDialog::checkTimeOut()
{
    //闹钟
    QSqlQuery query;
    QString currentTime = QTime::currentTime().toString("hh:mm:ss");
    QString alarmclock;
    int musictime = 0;

    query.exec("select alarmclock from alarmtime where alarmtimeid = 1");
    while(query.next())
        alarmclock = query.value(0).toString();

    query.exec("select musictime from alarmtime where alarmtimeid = 1");
    while(query.next())
        musictime = query.value(0).toInt();

    if(currentTime == alarmclock)
    {
        musicPlay();
        picShow();
        musicFlag = true;
        picDia.show();
        QMessageBox::information(NULL, "timeOut", "Time out!");
    }

    if(tryListen == true)
    {
        tryMusicTick++;
    }

    if(tryListen == false)
    {
        tryMusicTick = 0;
    }

    if(tryMusicTick == musictime)
    {
        mediaObject->stop();
        tryListen == false;
    }

    if(musicFlag == true)
    {
        tryListen = false;
        musicTick++;
    }

    if(musicFlag == false)
    {
        musicTick = 0;
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap(":/background.png"));
    }

    if(musicTick == musictime)
    {
        picDia.hide();
        mediaObject->stop();
    }
}

void mainDialog::musicPlay()
{
    //音乐播放
    QString musicPath;
    QSqlQuery query;

    query.exec("select music from alarmtime where alarmtimeid = 1");
    while(query.next())
        musicPath = query.value(0).toString();

    mediaObject->stop();
    mediaObject->setCurrentSource(Phonon::MediaSource(musicPath));
    mediaObject->play();
}

void mainDialog::picShow()
{
    //图片显示
    QString picPath;
    QSqlQuery query;

    query.exec("select pic from alarmtime where alarmtimeid = 1");
    while(query.next())
        picPath = query.value(0).toString();

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(picPath));
}

void mainDialog::stateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
    switch (newState) {
    case Phonon::ErrorState:
        if (mediaObject->errorType() == Phonon::FatalError) {
            QMessageBox::warning(this, tr("Fatal Error"),
                                 mediaObject->errorString());
        } else {
            QMessageBox::warning(this, tr("Error"),
                                 mediaObject->errorString());
        }
        break;
    case Phonon::PlayingState:
        playAction->setEnabled(false);
        pauseAction->setEnabled(true);
        stopAction->setEnabled(true);
        break;
    case Phonon::StoppedState:
        stopAction->setEnabled(false);
        playAction->setEnabled(true);
        pauseAction->setEnabled(false);
        timeLcd->display("00:00");
        musicFlag = false;
        break;
    case Phonon::PausedState:
        pauseAction->setEnabled(false);
        stopAction->setEnabled(true);
        playAction->setEnabled(true);
        break;
    case Phonon::BufferingState:
        break;
    default:
        ;
    }
}

void mainDialog::tick(qint64 time)
{
    QTime displayTime(0, (time/60000)%60, (time/1000)%60);
    timeLcd->display(displayTime.toString("mm:ss"));
}

void mainDialog::sourceChanged(const Phonon::MediaSource &source)
{
    timeLcd->display("00:00");
}

void mainDialog::aboutToFinish()
{
    QSqlQuery query;
    QString musicPath;
    int musictime = 0;

    query.exec("select musictime from alarmtime where alarmtimeid = 1");
    while(query.next())
        musictime = query.value(0).toInt();

    if(musicTick == musictime)
    {
        mediaObject->stop();
        musicFlag = false;
    }
    else
    {
        query.exec("select music from alarmtime where alarmtimeid = 1");
        while(query.next())
            musicPath = query.value(0).toString();

        mediaObject->setCurrentSource(Phonon::MediaSource(musicPath));
        mediaObject->play();
    }
}

void mainDialog::initComboBox()
{
    //初始化组合框
    ui->comboBox->clear();
    ui->comboBox_2->clear();

    QSqlQuery query;
    query.exec("select name from music");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }

    query.exec("select name from pic");
    while(query.next())
    {
        ui->comboBox_2->addItem(query.value(0).toString());
    }
}

void mainDialog::on_timeEdit_2_timeChanged(const QTime &date)
{
    //时间设置更改
    if((ui->timeEdit_2->dateTime().toString("h").toInt()*3600 + ui->timeEdit_2->dateTime().toString("m").toInt()*60 + ui->timeEdit_2->dateTime().toString("s").toInt()) > 120)
        ui->timeEdit_2->setTime(QTime::QTime(0, 2, 0));
}

void mainDialog::on_pushButton_10_clicked()
{
    //睡眠小贴士
    msgw.show();
}
