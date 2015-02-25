#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    //网页相关
    QFile file(":/map.html");
    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(NULL, "Unable to open file", file.errorString());
    }
    QTextStream out(&file);
    QString output = out.readAll();

    ui->webView->setHtml(output);
    connect(ui->webView, SIGNAL(loadFinished(bool)), this, SLOT(webViewLoadFinished(bool)));

    //定位API
    ipNetworkAccessManager = new QNetworkAccessManager(this);
    connect(ipNetworkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(ipNetworkReplyFinish(QNetworkReply *)));

    placeNetworkAccessManager = new QNetworkAccessManager(this);
    connect(placeNetworkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(placeNetworkReplyFinish(QNetworkReply *)));

    weatherNetworkAccessManager = new QNetworkAccessManager(this);
    connect(weatherNetworkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(weatherNetworkReplyFinish(QNetworkReply*)));

    initDialog();

    //音乐播放相关
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
    playbackLayout->addWidget(ui->pushButton_9);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(seekerLayout);
    mainLayout->addLayout(playbackLayout);

    ui->stackedWidget->widget(3)->setLayout(mainLayout);

    timeLcd->display("00:00");

    mediaObject->setTickInterval(1000);
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::showEvent(QShowEvent *)
{
}

void mainDialog::paintEvent(QPaintEvent *)
{
}

void mainDialog::webViewLoadFinished(bool)
{
}

void mainDialog::ipAnalyze()
{
    QString html = QString("http://www.whatismyip.com.tw/");
    ipNetworkAccessManager->get(QNetworkRequest(QUrl(html)));
}

void mainDialog::ipNetworkReplyFinish(QNetworkReply *networkReply)
{
    //API调用完成
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString all = codec->toUnicode(networkReply->readAll());
    networkReply->deleteLater();

    int stopInt = all.indexOf("</h2>");
    all = all.left(stopInt);

    int startInt = all.indexOf(">");
    int lengthInt = all.length();

    while(all.indexOf(">") != -1)
    {
        startInt = all.indexOf(">");
        lengthInt = all.length();
        all = all.right(lengthInt-startInt-1);
    }
    qDebug() << all << endl;

    //网易有道IP地址API接口
    QString html = QString("http://www.youdao.com/smartresult-xml/search.s?type=ip&q=" + all);
    qDebug() << html << endl;
    placeNetworkAccessManager->get(QNetworkRequest(QUrl(html)));
}

void mainDialog::placeNetworkReplyFinish(QNetworkReply *networkReply)
{
    //API调用完成
    QTextCodec *codec=QTextCodec::codecForName("GBK");
    QString all=codec->toUnicode(networkReply->readAll());
    networkReply->deleteLater();

    qDebug() << all << endl;

    int stopInt = all.indexOf("</location>");
    all = all.left(stopInt);

    int startInt = all.indexOf(">");
    int lengthInt = all.length();

    while(all.indexOf(">") != -1)
    {
        startInt = all.indexOf(">");
        lengthInt = all.length();
        all = all.right(lengthInt-startInt-1);
    }
    ui->label_2->setText("当前位置 : " + all);

    stopInt = all.indexOf("市");
    all = all.left(stopInt);
    startInt = all.indexOf("省");
    lengthInt = all.length();
    all = all.right(lengthInt-startInt-1);
    placeStr = all;

    qDebug() << placeStr << endl;

    QSqlQuery query;
    QString coordinatex, coordinatey, zoomlevel;
    query.exec("select * from city where name = '" + placeStr + "'");
    while(query.next())
    {
        coordinatex = query.value(2).toString();
        coordinatey = query.value(3).toString();
        zoomlevel = query.value(4).toString();
    }

    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("myPlace(%1, %2, %3)").arg(coordinatex).arg(coordinatey).arg(zoomlevel);
    frame->evaluateJavaScript(cmd);
}


void mainDialog::on_pushButton_2_clicked()
{
    //定位当前位置
    ipAnalyze();
}

void mainDialog::on_pushButton_3_clicked()
{
    //自驾搜索
    ui->stackedWidget->setCurrentIndex(0);
}

void mainDialog::on_pushButton_4_clicked()
{
    //周边搜索
    ui->stackedWidget->setCurrentIndex(1);
}

void mainDialog::on_pushButton_5_clicked()
{
    //其他省市
    ui->stackedWidget->setCurrentIndex(2);
}

void mainDialog::on_pushButton_6_clicked()
{
    //音乐播放
    ui->stackedWidget->setCurrentIndex(3);
}

void mainDialog::on_pushButton_7_clicked()
{
    //天气预报
    ui->stackedWidget->setCurrentIndex(4);
}

void mainDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    //查找其他省市编辑框文字输入变化
    QString cityName;
    cityName = ui->lineEdit_2->text().trimmed();
    ui->comboBox->clear();

    QSqlQuery query;
    query.exec("select name from city where name like '%" + cityName + "%'");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }
}

void mainDialog::initDialog()
{
    ui->label_2->setText("当前位置 : ");
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    ui->comboBox->clear();
    ui->comboBox_2->clear();
    QSqlQuery query;
    query.exec("select name from city");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }
    query.exec("select name from weathercity");
    while(query.next())
    {
        ui->comboBox_2->addItem(query.value(0).toString());
    }
}

void mainDialog::on_pushButton_clicked()
{
    //两个地点查询
    if((ui->lineEdit->text().trimmed() == "") || (ui->lineEdit_3->text().trimmed() == ""))
    {
        QMessageBox::information(NULL, "warring", "Empty!");
        return;
    }

    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("setRouteLine('%1', '%2')").arg(ui->lineEdit_3->text().trimmed()).arg(ui->lineEdit->text().trimmed());
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_8_clicked()
{
    //外省选择
    QString cityName;
    cityName = ui->comboBox->currentText();

    QSqlQuery query;
    QString coordinatex, coordinatey, zoomlevel;
    query.exec("select * from city where name = '" + cityName + "'");
    while(query.next())
    {
        coordinatex = query.value(2).toString();
        coordinatey = query.value(3).toString();
        zoomlevel = query.value(4).toString();
    }

    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("myPlace(%1, %2, %3)").arg(coordinatex).arg(coordinatey).arg(zoomlevel);
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_9_clicked()
{
    //选择音乐文件
    musicFile = QFileDialog::getOpenFileName(this, tr("Open mp3"), ".", tr("Image Files(*.mp3)"));
    if(musicFile.length() == 0)
    {
        //QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    }
    else
    {
        //QMessageBox::information(NULL, tr("Path"), tr("You selected ") + musicFile);
    }

    mediaObject->stop();
    mediaObject->setCurrentSource(Phonon::MediaSource(musicFile));
    mediaObject->play();
}

void mainDialog::on_lineEdit_4_textChanged(const QString &arg1)
{
    //天气预报城市编辑框修改
    QString cityName;
    cityName = ui->lineEdit_4->text().trimmed();
    ui->comboBox_2->clear();

    QSqlQuery query;
    query.exec("select name from weathercity where name like '%" + cityName + "%'");
    while(query.next())
    {
        ui->comboBox_2->addItem(query.value(0).toString());
    }
}

void mainDialog::on_pushButton_11_clicked()
{
    //天气预报城市选择
    QString cityName;
    cityName = ui->comboBox_2->currentText();

    QSqlQuery query;
    QString cityCode;
    query.exec("select * from weathercity where name = '" + cityName + "'");
    while(query.next())
    {
        cityCode = query.value(2).toString();
    }

    //中国天气网API接口
    QString html = QString("http://www.weather.com.cn/data/cityinfo/" + cityCode + ".html");
    qDebug() << html << endl;
    weatherNetworkAccessManager->get(QNetworkRequest(QUrl(html)));
}

void mainDialog::on_pushButton_10_clicked()
{
    //天气预报当前城市
    ui->lineEdit_4->setText(placeStr);

    ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(ui->lineEdit_4->text().trimmed()));

    on_pushButton_11_clicked();
}

void mainDialog::on_pushButton_14_clicked()
{
    //普通地图
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("setMapTypeId_ROADMAP()");
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_15_clicked()
{
    //卫星地图
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("setMapTypeId_SATELLITE()");
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_16_clicked()
{
    //混合地图
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("setMapTypeId_HYBRID()");
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_12_clicked()
{
    //放大地图
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("getZoom()");
    int zoomLevel = frame->evaluateJavaScript(cmd).toInt();

    qDebug() << zoomLevel << endl;

    if(zoomLevel == 18)
    {
        return;
    }

    zoomLevel++;

    cmd = QString("setZoom(%1)").arg(zoomLevel);
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_13_clicked()
{
    //缩小地图
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("getZoom()");
    int zoomLevel = frame->evaluateJavaScript(cmd).toInt();

    qDebug() << zoomLevel << endl;

    if(zoomLevel == 0)
    {
        return;
    }

    zoomLevel--;

    cmd = QString("setZoom(%1)").arg(zoomLevel);
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_17_clicked()
{
    //清除路线
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("clearRoute()");
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_18_clicked()
{
    //清空标记
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("clearPoint()");
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_19_clicked()
{
    //附近的加油站
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("searchPoint('加油站')");
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_20_clicked()
{
    //附近的银行
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("searchPoint('银行')");
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_21_clicked()
{
    //附近的饭店
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("searchPoint('饭店')");
    frame->evaluateJavaScript(cmd);
}

void mainDialog::on_pushButton_22_clicked()
{
    //附近的搜索
    if(ui->lineEdit_5->text().trimmed() == "")
    {
        QMessageBox::information(NULL, "warring", "Empty!");
        return;
    }

    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("searchPoint('%1')").arg(ui->lineEdit_5->text().trimmed());
    frame->evaluateJavaScript(cmd);
}

void mainDialog::stateChanged(Phonon::State newState, Phonon::State /* oldState */)
{
    //音乐状态改变
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
    //音乐时间显示
    QTime displayTime(0, (time/60000)%60, (time/1000)%60);
    timeLcd->display(displayTime.toString("mm:ss"));
}

void mainDialog::sourceChanged(const Phonon::MediaSource &source)
{
    //歌曲切换
    timeLcd->display("00:00");
}

void mainDialog::aboutToFinish()
{
    //音乐结束
}

void mainDialog::weatherNetworkReplyFinish(QNetworkReply *networkReply)
{
    //天气预报下载完成
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QString all=codec->toUnicode(networkReply->readAll());
    networkReply->deleteLater();
    qDebug() << all << endl;
    QStringList list=all.split(",");
    qDebug() << list << endl;

    QString temp1, temp2, weather;

    foreach (QString temp, list) {
        if(temp.indexOf("temp1") != -1)
        {
            temp = temp.left(temp.length()-1);
            temp1 = temp.right(temp.length() - temp.indexOf("\":\"") -3);
        }
        if(temp.indexOf("temp2") != -1)
        {
            temp = temp.left(temp.length()-1);
            temp2 = temp.right(temp.length() - temp.indexOf("\":\"") -3);
        }
        if(temp.indexOf("weather") != -1)
        {
            temp = temp.left(temp.length()-1);
            weather = temp.right(temp.length() - temp.indexOf("\":\"") -3);
        }
    }

    ui->label_6->setText(QString("天气情况 : %1, 温度 : %2~%3").arg(weather).arg(temp1).arg(temp2));
}
