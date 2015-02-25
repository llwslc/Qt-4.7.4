#include <QtGui>
#include "movieForm.h"

MovieForm::MovieForm(QWidget *parent)
    :QWidget(parent)
{
    resize(640, 480);
    setWindowTitle("视频播放器");
    view = new QLabel("", this);
    view->setGeometry(QRect(30, 30, 370, 335));

    timeLabel = new QLabel(this);
    timeLabel->setGeometry(QRect(30, 370, 150, 20));

    percentLabel = new QLabel(this);
    percentLabel->setGeometry(QRect(180, 370, 50, 20));

    frame = new QFrame(this);
    frame->setGeometry(QRect(30, 390, 571, 80));
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setFrameShadow(QFrame::Raised);

    playBtn = new QPushButton("播放", frame);
    playBtn->setGeometry(QRect(10, 40, 61, 31));
    playBtn->setEnabled(false);
    connect(playBtn, SIGNAL(clicked()), this, SLOT(pause()));

    preBtn = new QPushButton("上一个", frame);
    preBtn->setGeometry(QRect(150, 40, 61, 31));
    connect(preBtn, SIGNAL(clicked()), this, SLOT(pre()));

    nextBtn = new QPushButton("下一个", frame);
    nextBtn->setGeometry(QRect(220, 40, 61, 31));
    connect(nextBtn, SIGNAL(clicked()), this, SLOT(next()));

    currentlBar = new QSlider(frame);
    currentlBar->setGeometry(QRect(9, 10, 551, 16));
    currentlBar->setOrientation(Qt::Horizontal);
    connect(currentlBar, SIGNAL(sliderReleased()), this, SLOT(sliderReleased()));
    connect(currentlBar, SIGNAL(sliderPressed()), this, SLOT(sliderPressed()));
    connect(currentlBar, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));

    stopBtn = new QPushButton("停止", frame);
    stopBtn->setGeometry(QRect(80, 40, 61, 31));
    stopBtn->setEnabled(false);
    connect(stopBtn, SIGNAL(clicked()), this, SLOT(stop()));

    timeBtn = new QPushButton("时间跳转", frame);
    timeBtn->setGeometry(QRect(500, 30, 60, 20));
    connect(timeBtn, SIGNAL(clicked()), this, SLOT(jumpByTime()));

    volumeSlider = new QSlider(frame);
    volumeSlider->setGeometry(QRect(340, 50, 141, 16));
    volumeSlider->setOrientation(Qt::Horizontal);
    volumeSlider->setRange(0, 50);
    volumeSlider->setValue(20);
    connect(volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeVolume(int)));

    view_2 = new QLabel("音量:", frame);
    view_2->setGeometry(QRect(300, 50, 60, 17));

    fullBox = new QCheckBox(frame);
    fullBox->setText("全屏");
    fullBox->setVisible(false);
    fullBox->setGeometry(QRect(380, 30, 78, 16));

    speedBtn = new QPushButton("速度设置", frame);
    speedBtn->setGeometry(QRect(500, 60, 60, 20));
    connect(speedBtn, SIGNAL(clicked()), this, SLOT(setSpeed()));

    list = new QListWidget(this);
    list->setGeometry(QRect(420, 30, 181, 335));
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(playListItem(QListWidgetItem *)));

    addBtn = new QPushButton(QIcon(":/images/add.png"), "", this);
    addBtn->setGeometry(QRect(440, 10, 50, 20));
    addBtn->setStyleSheet("border-style:none");
    connect(addBtn, SIGNAL(clicked()), this, SLOT(add()));

    delBtn = new QPushButton(QIcon(":/images/remove.png"), "", this);
    delBtn->setGeometry(QRect(530, 10, 50, 20));
    delBtn->setStyleSheet("border-style:none");
    connect(delBtn, SIGNAL(clicked()), this, SLOT(del()));

    p = new QProcess(this);
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(dataRecieve()));
    connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(mplayerEnded(int, QProcess::ExitStatus)));

    sliderFlag = 0;
}

MovieForm::~MovieForm()
{
    stop();
    p->kill();
}

void MovieForm::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/images/bj.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void MovieForm::next()
{
    //下一首
    if(list->count() == 0)
    {
        stop();
    }
    else
    {
        if(list->currentRow() == list->count() - 1)
        {
            list->setCurrentRow(0);
        }
        else
        {
            list->setCurrentRow(list->currentRow() + 1);
        }

        play(list->currentItem()->text());
        playBtn->setText("暂停");
    }
}

void MovieForm::pre()
{
    //上一首
    int currentRow = 0;
    if(list->count() == 0)
    {
        stop();
    }
    else
    {
        if(list->currentRow() == 0)
        {
            list->setCurrentRow(list->count() - 1);
        }
        else
        {
            currentRow = list->currentRow() - 1;
            if(currentRow < 0)
            {
                currentRow = 0;
            }
            list->setCurrentRow(currentRow);
        }

        play(list->currentItem()->text());
        playBtn->setText("暂停");
    }
}

void MovieForm::add()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, "choose movies", "/", "Movie (*.m4v *.mp4 *.avi *.wmv *.mpg);;Music (*.mp3)");
    if(fileNames.count() != 0)
    {
        list->addItems(fileNames);
    }
}

void MovieForm::del()
{
    if(list->currentRow() ==  -1)
    {
        QMessageBox::warning(this, "提示", "未选中项目或列表为空", QMessageBox::Yes);
    }
    else
    {
        list->takeItem(list->currentRow());
    }
}

void MovieForm::playListItem(QListWidgetItem *item)
{
    play(item->text());
    playBtn->setText("暂停");
}

void MovieForm::play(QString fileName)
{
    QStringList args;
    p->kill();
    p = new QProcess(this);
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(dataRecieve()));
    //    args << "-slave";
    //    args << "-quiet";
    //    args << "-wid" << QString::number((long)view->winId(), 10);
    //    args << "-zoom";
    //    args << "-x";
    //    args << "370";
    //    args << "-y";
    //    args << "335";
    //    args << "-vo";
    //    args << "x11";

    args.clear();
    args << "-slave";
    args << "-quiet";
    args << "-wid" << QString::number(reinterpret_cast<qlonglong>(view->winId()), 10);
    args << "-vo" << "directx:noaccel";

    args << fileName;
    p->start("MPlayer/mplayer.exe", args);

    if(!p->waitForStarted(3000))
    {
        qDebug() << "check the bug :isplay = 0";
    }

    playBtn->setEnabled(true);
    stopBtn->setEnabled(true);
}


void MovieForm::pause()
{
    p->write("pause\n");
    if(playBtn->text() == "播放")
    {
        connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(dataRecieve()));
        p->write("get_time_length\n");
        p->write("get_time_pos\n");
        p->write("get_percent_pos\n");
        playBtn->setText("暂停");
    }
    else
    {
        disconnect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(dataRecieve()));
        playBtn->setText("播放");
    }
}

void MovieForm::stop()
{
    p->write("quit\n");
    disconnect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(dataRecieve()));
    timeLabel->setText("");
    percentLabel->setText("");
    currentlBar->setValue(0);

    playBtn->setEnabled(false);
    stopBtn->setEnabled(false);
    playBtn->setText("暂停");
}

void MovieForm::changeVolume(int v)
{
    p->write(QString("volume " + QString::number(v) + " 2\n").toUtf8());
}

void MovieForm::setSpeed()
{
    double speed = QInputDialog::getDouble(this, "播放速度设置", "相对于正常速度倍数:");
    if(speed > 0)
        p->write(QString("speed_set " + QString::number(speed) + " 2\n").toUtf8());
}

void MovieForm::closeEvent(QCloseEvent *)
{
    p->kill();
}

void MovieForm::dataRecieve()
{
    p->write("get_time_length\n");
    p->write("get_time_pos\n");
    p->write("get_percent_pos\n");
    while(p->canReadLine())
    {
        QByteArray b = p->readLine();
        if(b.startsWith("ANS_TIME_POSITION"))
        {
            b.replace(QByteArray("\n"), QByteArray(""));
            QString s(b);
            currentStr = s.mid(18);
            if(!sliderFlag)
            {
                currentlBar->setValue(s.mid(18).toFloat());    //更新进度条
            }
        }
        else if((b.startsWith("ANS_LENGTH")))
        {
            b.replace(QByteArray("\n"), QByteArray(""));
            QString s(b);
            totalTime = s.mid(11);
            timeLabel->setText(currentStr + "秒/" + totalTime + "秒  "); //显示时间进度
            if(!sliderFlag)
            {
                currentlBar->setRange(0, s.mid(11).toFloat());
            }
        }
        else if((b.startsWith("ANS_PERCENT_POSITION")))
        {
            b.replace(QByteArray("\n"), QByteArray(""));
            QString s(b);
            currentPercent = s.mid(21);
            percentLabel->setText("(" + currentPercent + "%)");
        }
    }
}

void MovieForm::sliderPressed()
{
    sliderFlag = 1;
}

void MovieForm::sliderReleased()
{
    int value = currentlBar->value();
    p->write(QString("seek " + QString::number(value) + " 2\n").toUtf8());
    sliderFlag = 0;
}

void MovieForm::valueChanged(int value)
{
    if(value == 100)
    {
        next();
    }
}

void MovieForm::jumpByTime()
{
    QDialog *timeDialog = new QDialog(this);
    timeDialog->resize(300, 100);
    minBox = new QSpinBox(timeDialog);
    minBox->setGeometry(QRect(20, 20, 50, 30));
    QLabel *minLabel = new QLabel("分", timeDialog);
    minLabel->setGeometry(QRect(80, 20, 20, 30));

    secBox = new QSpinBox(timeDialog);
    secBox->setGeometry(QRect(100, 20, 50, 30));
    QLabel *secLabel = new QLabel("秒", timeDialog);
    secLabel->setGeometry(QRect(150, 20, 30, 30));

    QPushButton *sureBtn = new QPushButton("确定", timeDialog);
    sureBtn->setGeometry(QRect(180, 20, 70, 30));
    connect(sureBtn, SIGNAL(clicked()), this, SLOT(sureBtnClicked()));
    timeDialog->show();
}

void MovieForm::sureBtnClicked()
{
    int jumpTime = minBox->value()*60 + secBox->value();
    p->write(QString("seek " + QString::number(jumpTime) + " 2\n").toUtf8());
}

void MovieForm::mplayerEnded(int exitCode,QProcess::ExitStatus exitStatus)
{
    disconnect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(dataRecieve()));
    timeLabel->setText("");
    percentLabel->setText("");
    currentlBar->setValue(0);

    playBtn->setEnabled(false);
    stopBtn->setEnabled(false);
    playBtn->setText("播放");
}


