#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateTimeTimer = new QTimer(this);
    connect(updateTimeTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    updateTimeTimer->start(UPDATETIMEONESECOND);

    isOnlineTimer = new QTimer(this);
    connect(isOnlineTimer, SIGNAL(timeout()), this, SLOT(isOnlineTest()));
    isOnlineTimer->start(UPDATETIMEONESECOND);

    ipNetworkAccessManager = new QNetworkAccessManager(this);
    connect(ipNetworkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(ipNetworkReplyFinish(QNetworkReply *)));

    placeNetworkAccessManager = new QNetworkAccessManager(this);
    connect(placeNetworkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(placeNetworkReplyFinish(QNetworkReply *)));

    weatherNetworkAccessManager = new QNetworkAccessManager(this);
    connect(weatherNetworkAccessManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(weatherNetworkReplyFinish(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    daydressDateEdit->setDate(QDate::currentDate());
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(BKGPAINTERX, BKGPAINTERY, QPixmap(":/images/main_background.png"));
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

void MainWindow::isOnlineTest()
{
    //联网测试
    QString html;
    QNetworkConfigurationManager mgr;
    if(mgr.isOnline())
    {
        isOnlineTimer->stop();

        html = QString("http://www.whatismyip.com.tw/");
        ipNetworkAccessManager->get(QNetworkRequest(QUrl(html)));
    }
    else
    {
        isOnlineTimer->start(ISONLINETENSECONDS);
    }

#ifdef DEBUGLEVELONE
    qDebug() << mgr.isOnline() << endl;
#endif
}

void MainWindow::closeEvent(QCloseEvent *)
{
}

void MainWindow::ipNetworkReplyFinish(QNetworkReply *networkReply)
{
    //IP地址解析
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString all = codec->toUnicode(networkReply->readAll());
    networkReply->deleteLater();

    int stopInt = all.indexOf("</h2>");
    all = all.left(stopInt);

    int startInt = all.indexOf(">");
    int lengthInt = all.length();

    while(all.indexOf(">") != STRINGNOTFINDINDEX)
    {
        startInt = all.indexOf(">");
        lengthInt = all.length();
        all = all.right(lengthInt - startInt - INTNUMBERDECREMENT);
    }

#ifdef DEBUGLEVELONE
    qDebug() << "IP地址为 : " << all << endl;
#endif

    //网易有道IP地址API接口
    QString html = QString("http://www.youdao.com/smartresult-xml/search.s?type=ip&q=" + all);
    placeNetworkAccessManager->get(QNetworkRequest(QUrl(html)));
}

void MainWindow::placeNetworkReplyFinish(QNetworkReply *networkReply)
{
    //地点解析
    QTextCodec *codec=QTextCodec::codecForName("GBK");
    QString all=codec->toUnicode(networkReply->readAll());
    networkReply->deleteLater();

#ifdef DEBUGLEVELTWO
    qDebug() << "地址解析为 : " << all << endl;
#endif

    int stopInt = all.indexOf("</location>");
    all = all.left(stopInt);

    int startInt = all.indexOf(">");
    int lengthInt = all.length();

    while(all.indexOf(">") != STRINGNOTFINDINDEX)
    {
        startInt = all.indexOf(">");
        lengthInt = all.length();
        all = all.right(lengthInt - startInt - INTNUMBERDECREMENT);
    }

    stopInt = all.indexOf("市");
    all = all.left(stopInt);
    startInt = all.indexOf("省");
    lengthInt = all.length();
    all = all.right(lengthInt - startInt - INTNUMBERDECREMENT);

#ifdef DEBUGLEVELTWO
    qDebug() << "市级解析为 : " << all << endl;
#endif

    weatherPlace->setText("<font color='white'>" + all + "</font>");

    QSqlQuery query;
    QString cityCode;
    query.exec("select * from weathercity where name = '" + all + "'");
    while(query.next())
    {
        cityCode = query.value(SQLWEATHERCITYCODEINDEX).toString();
    }

    //中国天气网6天数据API接口
    QString html = QString("http://m.weather.com.cn/data/" + cityCode + ".html");
    weatherNetworkAccessManager->get(QNetworkRequest(QUrl(html)));
}

void MainWindow::weatherNetworkReplyFinish(QNetworkReply *networkReply)
{
    //天气预报解析
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QString all=codec->toUnicode(networkReply->readAll());
    networkReply->deleteLater();
    qDebug() << all << endl;
    QStringList list=all.split(",");
    qDebug() << list << endl;

    QString todayTemp, weather, image;

    foreach (QString temp, list)
    {
        if(temp.indexOf("temp1") != STRINGNOTFINDINDEX)
        {
            temp = temp.left(temp.length() - INTNUMBERDECREMENT);
            todayTemp = temp.right(temp.length() - temp.indexOf("\":\"") - WEATHERFINDSTRINGLENGTH);
        }
        //if(temp.indexOf("weather1") != STRINGNOTFINDINDEX)
        if(temp.indexOf("img_title_single") != STRINGNOTFINDINDEX)
        {
            temp = temp.left(temp.length() - INTNUMBERDECREMENT);
            weather = temp.right(temp.length() - temp.indexOf("\":\"") - WEATHERFINDSTRINGLENGTH);
        }
        if(temp.indexOf("img1\":\"") != STRINGNOTFINDINDEX)
        {
            temp = temp.left(temp.length() - INTNUMBERDECREMENT);
            image = temp.right(temp.length() - temp.indexOf("\":\"") - WEATHERFINDSTRINGLENGTH);
        }
    }

    weatherTemp->setText("<font color='white'>" + todayTemp + "</font>");
    weatherTitle->setText("<font color='white'>" + weather + "</font>");

    qDebug() << image;
    weatherImage->setButtonPicture(QPixmap(":/weather/" + image + ".png"));
    weatherImage->setPressPicture(QPixmap(":/weather/" + image + ".png"));
    weatherImage->setReleasePicture(QPixmap(":/weather/" + image + ".png"));
}

void MainWindow::updateTime()
{
    //刷新时间
    //钟表小时高位
    digiClockHourHigh->setButtonPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("hh").mid(0, 1) + ".png"));
    digiClockHourHigh->setPressPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("hh").mid(0, 1) + ".png"));
    digiClockHourHigh->setReleasePicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("hh").mid(0, 1) + ".png"));
    //钟表小时低位
    digiClockHourLow->setButtonPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("hh").mid(1, 1) + ".png"));
    digiClockHourLow->setPressPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("hh").mid(1, 1) + ".png"));
    digiClockHourLow->setReleasePicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("hh").mid(1, 1) + ".png"));
    //钟表分钟高位
    digiClockMinuteHigh->setButtonPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("mm").mid(0, 1) + ".png"));
    digiClockMinuteHigh->setPressPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("mm").mid(0, 1) + ".png"));
    digiClockMinuteHigh->setReleasePicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("mm").mid(0, 1) + ".png"));
    //钟表分钟低位
    digiClockMinuteLow->setButtonPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("mm").mid(1, 1) + ".png"));
    digiClockMinuteLow->setPressPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("mm").mid(1, 1) + ".png"));
    digiClockMinuteLow->setReleasePicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("mm").mid(1, 1) + ".png"));
    //钟表秒数高位
    digiClockSecondHigh->setButtonPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("ss").mid(0, 1) + ".png"));
    digiClockSecondHigh->setPressPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("ss").mid(0, 1) + ".png"));
    digiClockSecondHigh->setReleasePicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("ss").mid(0, 1) + ".png"));
    //钟表秒数低位
    digiClockSecondLow->setButtonPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("ss").mid(1, 1) + ".png"));
    digiClockSecondLow->setPressPicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("ss").mid(1, 1) + ".png"));
    digiClockSecondLow->setReleasePicture(QPixmap(":/digiclock/" + QTime::currentTime().toString("ss").mid(1, 1) + ".png"));
    if(QTime::currentTime().toString("ss").toInt()%INTEVENNUMBERFLAG)
    {
        //钟表隔位点高位
        digiClockPointsHigh->setButtonPicture(QPixmap(":/digiclock/points_transparent.png"));
        digiClockPointsHigh->setPressPicture(QPixmap(":/digiclock/points_transparent.png"));
        digiClockPointsHigh->setReleasePicture(QPixmap(":/digiclock/points_transparent.png"));
        //钟表隔位点低位
        digiClockPointsLow->setButtonPicture(QPixmap(":/digiclock/points_transparent.png"));
        digiClockPointsLow->setPressPicture(QPixmap(":/digiclock/points_transparent.png"));
        digiClockPointsLow->setReleasePicture(QPixmap(":/digiclock/points_transparent.png"));
    }
    else
    {
        //钟表隔位点高位
        digiClockPointsHigh->setButtonPicture(QPixmap(":/digiclock/points.png"));
        digiClockPointsHigh->setPressPicture(QPixmap(":/digiclock/points.png"));
        digiClockPointsHigh->setReleasePicture(QPixmap(":/digiclock/points.png"));
        //钟表隔位点低位
        digiClockPointsLow->setButtonPicture(QPixmap(":/digiclock/points.png"));
        digiClockPointsLow->setPressPicture(QPixmap(":/digiclock/points.png"));
        digiClockPointsLow->setReleasePicture(QPixmap(":/digiclock/points.png"));
    }

    digiClockDateBkgText->setText("<font color='#dff5fa'>" + QDate::currentDate().toString("dddd MMM dd yyyy") + "</font>");
}

void MainWindow::myclothesButton_clicked()
{
    //我的衣橱
    mainPressed = MYCLOTHESPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "myclothesButton_clicked()" << endl;
#endif
}

void MainWindow::fashionButton_clicked()
{
    //风格搭配
    mainPressed = FASHIONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "fashionButton_clicked()" << endl;
#endif
}

void MainWindow::daydressButton_clicked()
{
    //每日装扮
    mainPressed = DAYDRESSPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "daydressButton_clicked()" << endl;
#endif
}

void MainWindow::settingButton_clicked()
{
    //主页
    mainPressed = SETTINGPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "settingButton_clicked()" << endl;
#endif
}

void MainWindow::clothesButton_clicked()
{
    //我的衣橱->衣服
    mainPressed = NOBUTTONPRESSED;
    typePressed = CLOTHESBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "clothesButton_clicked()" << endl;
#endif
}

void MainWindow::bagButton_clicked()
{
    //我的衣橱->包包
    mainPressed = NOBUTTONPRESSED;
    typePressed = BAGBUTTONRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "bagButton_clicked()" << endl;
#endif
}

void MainWindow::shoeButton_clicked()
{
    //我的衣橱->鞋帽
    mainPressed = NOBUTTONPRESSED;
    typePressed = SHOEBUTTONRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "shoeButton_clicked()" << endl;
#endif
}

void MainWindow::decoButton_clicked()
{
    //我的衣橱->饰品
    mainPressed = NOBUTTONPRESSED;
    typePressed = DECOBUTTONRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "decoButton_clicked()" << endl;
#endif
}

void MainWindow::cosButton_clicked()
{
    //我的衣橱->化妆品
    mainPressed = NOBUTTONPRESSED;
    typePressed = COSBUTTONRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "cosButton_clicked()" << endl;
#endif
}

void MainWindow::labelButton_clicked()
{
    //我的衣橱->自定义
    mainPressed = NOBUTTONPRESSED;
    typePressed = LABELBUTTONRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "labelButton_clicked()" << endl;
#endif
}

void MainWindow::springButton_clicked()
{
    //风格搭配->春季
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = SPRINGBUTTONRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "springButton_clicked()" << endl;
#endif
}

void MainWindow::summerButton_clicked()
{
    //风格搭配->夏季
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = SUMMERBUTTONRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "summerButton_clicked()" << endl;
#endif
}

void MainWindow::autumnButton_clicked()
{
    //风格搭配->秋季
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = AUTUMNBUTTONRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "autumnButton_clicked()" << endl;
#endif
}

void MainWindow::winterButton_clicked()
{
    //风格搭配->冬季
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = WINTERBUTTONRESSED;
    classtypePressed = NOBUTTONPRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "winterButton_clicked()" << endl;
#endif
}

void MainWindow::workplaceButton_clicked()
{
    //风格搭配->职场
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = WORKPLACEBUTTONRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "workplaceButton_clicked()" << endl;
#endif
}

void MainWindow::banquetButton_clicked()
{
    //风格搭配->宴会
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = BANQUETBUTTONRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "banquetButton_clicked()" << endl;
#endif
}

void MainWindow::leisureButton_clicked()
{
    //风格搭配->休闲
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = LEISUREBUTTONRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "leisureButton_clicked()" << endl;
#endif
}

void MainWindow::sportButton_clicked()
{
    //风格搭配->运动
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = SPORTBUTTONRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "sportButton_clicked()" << endl;
#endif
}

void MainWindow::otherButton_clicked()
{
    //风格搭配->其他
    mainPressed = NOBUTTONPRESSED;
    typePressed = NOBUTTONPRESSED;
    seasonPressed = NOBUTTONPRESSED;
    classtypePressed = OTHERBUTTONRESSED;

#ifdef DEBUGLEVELTHREE
    qDebug() << "otherButton_clicked()" << endl;
#endif
}

void MainWindow::addButton_clicked()
{
    //添加按钮
    if(mainPressed == DAYDRESSPRESSED)
    {
        insertDayDressList();
    }
    else
    {
        globaWindowsPos = this->QWidget::pos(); //获取窗口位置
        addPressed = true;
        this->hide();
        clothesw.exec();

        this->move(globaWindowsPos);   //调整窗口位置
        this->show();
    }
}

void MainWindow::delButton_clicked()
{
    //删除按钮
    QSqlQuery query;

    if(mainPressed != DAYDRESSPRESSED)
    {
        if(clothesListWidget->currentRow() == LISTWIDGETNOSELECT)
        {
            //NULL
        }
        else
        {
            selectClothesIdNumInt = clothesListWidget->item(clothesListWidget->currentRow(), clothesListWidget->currentColumn())->text().toInt();
            query.exec("delete from clothes where clothesid = '" + QString::number(selectClothesIdNumInt, NUMBERTOSTRINGBASE) + "'");
            secondLayerButton_clicked();
        }
    }
    else
    {
        if(daydressListWidget->currentRow() == LISTWIDGETNOSELECT)
        {
            //NULL
        }
        else
        {
            selectDaydressIdNumInt = daydressListWidget->item(daydressListWidget->currentRow(), daydressListWidget->currentColumn())->text().toInt();
            query.exec("delete from daydress where daydressid = '" + QString::number(selectDaydressIdNumInt, NUMBERTOSTRINGBASE) + "'");
            daydressListWidget_update();
        }
    }
}

void MainWindow::secondLayerButton_clicked()
{
    //第二层按钮点击
    QSqlQuery query;
    QString filterStr;
    int filterInt = INTNUMBERINIT;
    int currentRow = INTNUMBERINIT;

    while(clothesListWidget->rowCount())
        clothesListWidget->removeRow(clothesListWidget->rowCount()-INTNUMBERDECREMENT);

#ifdef DEBUGLEVELTWO
    qDebug() << "clothesListWidget->rowCount() = " << clothesListWidget->rowCount() << endl;
#endif

    if(typePressed != NOBUTTONPRESSED)
    {
        filterStr = "type";
        filterInt = typePressed;
    }
    else
    {
        //NULL
    }
    if(seasonPressed != NOBUTTONPRESSED)
    {
        filterStr = "season";
        filterInt = seasonPressed;
    }
    else
    {
        //NULL
    }
    if(classtypePressed != NOBUTTONPRESSED)
    {
        filterStr = "classtype";
        filterInt = classtypePressed;
    }
    else
    {
        //NULL
    }

#ifdef DEBUGLEVELTWO
    qDebug() << filterStr << filterInt << endl;
#endif

    query.exec("select * from clothes where " + filterStr + " = '" + QString::number(filterInt, NUMBERTOSTRINGBASE) + "'");
    while(query.next())
    {
        QTableWidgetItem *tableWidgetItem = new QTableWidgetItem(QTableWidgetItem::Type);
        tableWidgetItem->setIcon(QIcon(QPixmap(query.value(SQLCLOTHESPICPATHINDEX).toString()).scaled(CLOTHESLISTWIDGETPICWIDTH, CLOTHESLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        tableWidgetItem->setText(query.value(SQLCLOTHESIDNUMINDEX).toString());
        tableWidgetItem->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        currentRow = clothesListWidget->rowCount();  //插入到最后

#ifdef DEBUGLEVELTWO
        qDebug() << "currentRow" << currentRow << endl;
#endif

        if(currentRow == INTNUMBERINIT)
        {
            clothesListWidget->insertRow(currentRow);
            clothesListWidget->setRowHeight(currentRow, CLOTHESLISTWIDGETCOLUMNHEIGHT);
            clothesListWidget->setIconSize(QSize(CLOTHESLISTWIDGETPICWIDTH, CLOTHESLISTWIDGETPICHEIGHT));
            clothesListWidget->setItem(currentRow, CLOTHESLISTWIDGETITEMLEFT, tableWidgetItem);  //插入该Item
        }
        else
        {
            currentRow--;
            if(clothesListWidget->item(currentRow, CLOTHESLISTWIDGETITEMLEFT) == NULL)
            {
                clothesListWidget->setItem(currentRow, CLOTHESLISTWIDGETITEMLEFT, tableWidgetItem);
            }
            else
            {
                if(clothesListWidget->item(currentRow, CLOTHESLISTWIDGETITEMRIGHT) == NULL)
                {
                    clothesListWidget->setItem(currentRow, CLOTHESLISTWIDGETITEMRIGHT, tableWidgetItem);
                }
                else
                {
                    currentRow++;
                    clothesListWidget->insertRow(currentRow);
                    clothesListWidget->setRowHeight(currentRow, CLOTHESLISTWIDGETCOLUMNHEIGHT);
                    clothesListWidget->setIconSize(QSize(CLOTHESLISTWIDGETPICWIDTH, CLOTHESLISTWIDGETPICHEIGHT));
                    clothesListWidget->setItem(currentRow, CLOTHESLISTWIDGETITEMLEFT, tableWidgetItem);  //插入该Item
                }
            }
        }
    }

    QTableWidgetItem *addPicItem = new QTableWidgetItem(QTableWidgetItem::Type);
    addPicItem->setIcon(QIcon(QPixmap(":/images/cloth_addpic_normal.png").scaled(CLOTHESLISTWIDGETPICWIDTH, CLOTHESLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    addPicItem->setText(QString::number(INTNUMBERINIT, NUMBERTOSTRINGBASE));
    addPicItem->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

#ifdef DEBUGLEVELTWO
    qDebug() << "currentRow" << currentRow << endl;
#endif

    if(clothesListWidget->item(currentRow, CLOTHESLISTWIDGETITEMLEFT) == NULL)
    {
        clothesListWidget->setItem(currentRow, CLOTHESLISTWIDGETITEMLEFT, addPicItem);
    }
    else
    {
        if(clothesListWidget->item(currentRow, CLOTHESLISTWIDGETITEMRIGHT) == NULL)
        {
            clothesListWidget->setItem(currentRow, CLOTHESLISTWIDGETITEMRIGHT, addPicItem);
        }
        else
        {
            //NULL
        }
    }
}

void MainWindow::clothesListWidget_DoubleClicked(const QModelIndex &index)
{
    //图片列表双击
    globaWindowsPos = this->QWidget::pos();

    selectClothesIdNumInt = clothesListWidget->item(clothesListWidget->currentRow(), clothesListWidget->currentColumn())->text().toInt();

#ifdef DEBUGLEVELTWO
    qDebug() << "selectClothesIdNumInt = " << selectClothesIdNumInt << endl;
#endif

    if(selectClothesIdNumInt == INTNUMBERINIT)
    {
        addPressed = true;
    }
    else
    {
        addPressed = false;
    }

    globaWindowsPos = this->QWidget::pos(); //获取窗口位置
    this->hide();
    clothesw.exec();

    this->move(globaWindowsPos);   //调整窗口位置
    this->show();
}

void MainWindow::insertDayDressList()
{
    //插入行每日装扮
    int currentRow = INTNUMBERINIT;
    currentRow = daydressListWidget->rowCount();

#ifdef DEBUGLEVELTWO
    qDebug() << "currentRow" << currentRow << endl;
#endif

    daydressListWidget->insertRow(currentRow);
    daydressListWidget->setRowHeight(currentRow,DAYDRESSLISTWIDGETCOLUMNHEIGHT);
    daydressListWidget->setIconSize(QSize(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT));

    QTableWidgetItem *tableWidgetItemUpclothes1 = new QTableWidgetItem(QTableWidgetItem::Type);
    tableWidgetItemUpclothes1->setIcon(QIcon(QPixmap(":/images/daydress_list_upclothes_1.png").scaled(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    tableWidgetItemUpclothes1->setText(QString::number(INTNUMBERINIT, NUMBERTOSTRINGBASE));
    tableWidgetItemUpclothes1->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    daydressListWidget->setItem(currentRow, DAYDRESSLISTWIDGETITEMUPCLOTHESONE, tableWidgetItemUpclothes1);

    QTableWidgetItem *tableWidgetItemUpclothes2 = new QTableWidgetItem(QTableWidgetItem::Type);
    tableWidgetItemUpclothes2->setIcon(QIcon(QPixmap(":/images/daydress_list_upclothes_2.png").scaled(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    tableWidgetItemUpclothes2->setText(QString::number(INTNUMBERINIT, NUMBERTOSTRINGBASE));
    tableWidgetItemUpclothes2->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    daydressListWidget->setItem(currentRow, DAYDRESSLISTWIDGETITEMUPCLOTHESTWO, tableWidgetItemUpclothes2);

    QTableWidgetItem *tableWidgetItemDownClothes = new QTableWidgetItem(QTableWidgetItem::Type);
    tableWidgetItemDownClothes->setIcon(QIcon(QPixmap(":/images/daydress_list_downclothes.png").scaled(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    tableWidgetItemDownClothes->setText(QString::number(INTNUMBERINIT, NUMBERTOSTRINGBASE));
    tableWidgetItemDownClothes->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    daydressListWidget->setItem(currentRow, DAYDRESSLISTWIDGETITEMDOWNCLOTHES, tableWidgetItemDownClothes);

    QTableWidgetItem *tableWidgetItemBag = new QTableWidgetItem(QTableWidgetItem::Type);
    tableWidgetItemBag->setIcon(QIcon(QPixmap(":/images/daydress_list_bag.png").scaled(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    tableWidgetItemBag->setText(QString::number(INTNUMBERINIT, NUMBERTOSTRINGBASE));
    tableWidgetItemBag->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    daydressListWidget->setItem(currentRow, DAYDRESSLISTWIDGETITEMBAG, tableWidgetItemBag);

    QTableWidgetItem *tableWidgetItemShoe = new QTableWidgetItem(QTableWidgetItem::Type);
    tableWidgetItemShoe->setIcon(QIcon(QPixmap(":/images/daydress_list_shoe.png").scaled(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    tableWidgetItemShoe->setText(QString::number(INTNUMBERINIT, NUMBERTOSTRINGBASE));
    tableWidgetItemShoe->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    daydressListWidget->setItem(currentRow, DAYDRESSLISTWIDGETITEMSHOE, tableWidgetItemShoe);

    QTableWidgetItem *tableWidgetItemDeco = new QTableWidgetItem(QTableWidgetItem::Type);
    tableWidgetItemDeco->setIcon(QIcon(QPixmap(":/images/daydress_list_deco.png").scaled(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    tableWidgetItemDeco->setText(QString::number(INTNUMBERINIT, NUMBERTOSTRINGBASE));
    tableWidgetItemDeco->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
    daydressListWidget->setItem(currentRow, DAYDRESSLISTWIDGETITEMDECO, tableWidgetItemDeco);
}

void MainWindow::daydressListWidget_update()
{
    //每日装扮列表数据更新
    QSqlQuery query;
    int currentRow = INTNUMBERINIT;
    QString preDate, nextDate;

    while(daydressListWidget->rowCount())
        daydressListWidget->removeRow(daydressListWidget->rowCount()-INTNUMBERDECREMENT);

#ifdef DEBUGLEVELTWO
    qDebug() << "daydressListWidget->rowCount() = " << daydressListWidget->rowCount() << endl;
#endif

    query.exec("select * from daydress order by matchdate");
    while(query.next())
    {
        preDate = query.value(SQLDAYDRESSDATEINDEX).toString();
        if(preDate != nextDate)
        {
            insertDayDressList();
            currentRow = daydressListWidget->rowCount();
            currentRow--;

            QTableWidgetItem *tableWidgetItem = new QTableWidgetItem(QTableWidgetItem::Type);
            tableWidgetItem->setIcon(QIcon(QPixmap(query.value(SQLDAYDRESSPICPATHINDEX).toString()).scaled(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
            tableWidgetItem->setText(query.value(SQLDAYDRESSIDNUMINDEX).toString());
            tableWidgetItem->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
            daydressListWidget->setItem(currentRow, query.value(SQLDAYDRESSTYPEINDEX).toInt(), tableWidgetItem);
        }
        else
        {
            currentRow = daydressListWidget->rowCount();
            currentRow--;

            QTableWidgetItem *tableWidgetItem = new QTableWidgetItem(QTableWidgetItem::Type);
            tableWidgetItem->setIcon(QIcon(QPixmap(query.value(SQLDAYDRESSPICPATHINDEX).toString()).scaled(DAYDRESSLISTWIDGETPICWIDTH, DAYDRESSLISTWIDGETPICHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
            tableWidgetItem->setText(query.value(SQLDAYDRESSIDNUMINDEX).toString());
            tableWidgetItem->setTextAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
            daydressListWidget->setItem(currentRow, query.value(SQLDAYDRESSTYPEINDEX).toInt(), tableWidgetItem);
        }
        nextDate = query.value(SQLDAYDRESSDATEINDEX).toString();
    }
}

void MainWindow::daydressListWidget_Clicked(const QModelIndex &index)
{
    //每日装扮列表单击
    QSqlQuery query;

    for(int i=INTNUMBERINIT; i<daydressListWidget->columnCount(); i++)
    {
        selectDaydressIdNumInt = daydressListWidget->item(daydressListWidget->currentRow(), i)->text().toInt();
        if(selectDaydressIdNumInt != INTNUMBERINIT)
            break;
    }

    query.exec("select * from daydress where daydressid = '" + QString::number(selectDaydressIdNumInt, NUMBERTOSTRINGBASE) + "'");
    while(query.next())
        daydressDateEdit->setDate(QDate::fromString(query.value(SQLDAYDRESSDATEINDEX).toString(), "yyyy.MM.dd"));
}

void MainWindow::daydressListWidget_DoubleClicked(const QModelIndex &index)
{
    //每日装扮列表双击
    QSqlQuery query;

    selectDaydressIdNumInt = daydressListWidget->item(daydressListWidget->currentRow(), daydressListWidget->currentColumn())->text().toInt();

    daydressColSelectInt = daydressListWidget->currentColumn();

    if(selectDaydressIdNumInt == INTNUMBERINIT)
    {
        switch(daydressColSelectInt)
        {
        case DAYDRESSLISTWIDGETITEMNOSELECT:
            break;
        case DAYDRESSLISTWIDGETITEMUPCLOTHESONE:
        case DAYDRESSLISTWIDGETITEMUPCLOTHESTWO:
        case DAYDRESSLISTWIDGETITEMDOWNCLOTHES:
            clothesButton_clicked();
            break;
        case DAYDRESSLISTWIDGETITEMBAG:
            bagButton_clicked();
            break;
        case DAYDRESSLISTWIDGETITEMSHOE:
            shoeButton_clicked();
            break;
        case DAYDRESSLISTWIDGETITEMDECO:
            decoButton_clicked();
            break;
        default:
            break;
        }

        globaWindowsPos = this->QWidget::pos();
        this->hide();
        filterw.exec();

        this->move(globaWindowsPos);
        this->show();
    }
    else
    {
        query.exec("select * from daydress where daydressid = '" + QString::number(selectDaydressIdNumInt, NUMBERTOSTRINGBASE) + "'");
        while(query.next())
            selectClothesIdNumInt = query.value(SQLDAYDRESSCLOTHESIDINDEX).toInt();

        qDebug() << selectClothesIdNumInt;

        globaWindowsPos = this->QWidget::pos();
        addPressed = false;
        this->hide();
        clothesw.exec();

        this->move(globaWindowsPos);
        this->show();
    }
}
