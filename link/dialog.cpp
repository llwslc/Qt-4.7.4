#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->pushButton_5->setEnabled(false);
    ui->pushButton_2->setEnabled(false);

    initPixmaps();
    gamePause = false; //暂停标志
    gameStart = false; //游戏开始标志
    gameOver = false; //游戏结束标志
    gameOnline = 0; //单机
    preMan.clear(); //前一个棋子选择
    nextMan.clear(); //后一个棋子选择
    manNum = 10;
    manTypeNum = 10;
    manWide = 10;
    manHigh = 10;
    manSum = manNum * manNum;
    manLeft = manSum;
    ui->progressBar->setValue(manLeft*100/manSum);
    ui->progressBar_2->setValue(0);

    gameTime.start();

    connect(&chatDlg, SIGNAL(linkGameStart()), this, SLOT(on_pushButton_clicked()));
    connect(&chatDlg, SIGNAL(linkGameAgree()), this, SLOT(gameOnlineRandomp()));
    connect(&chatDlg, SIGNAL(linkGameLevel()), this, SLOT(gameOnlineLevel()));
    connect(&chatDlg, SIGNAL(linkGameServer()), this, SLOT(gameOnlineServer()));
    connect(&chatDlg, SIGNAL(linkGameClient()), this, SLOT(gameOnlineClient()));
    connect(&chatDlg, SIGNAL(linkGameProgressBar()), this, SLOT(gameOnlineProgressBar()));
    connect(&chatDlg, SIGNAL(linkGameOver()), this, SLOT(gameOnlineGameOver()));
    connect(&chatDlg, SIGNAL(linkGamePlayerOne()), this, SLOT(gamePlayerOne()));
    connect(&chatDlg, SIGNAL(linkGamePlayerTwo()), this, SLOT(gamePlayerTwo()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    //游戏开始
    gameStart = true;
    gameOver = false;
    ui->pushButton->setText("重新开始");
    ui->pushButton_5->setEnabled(true);

    if (gamePause == true)
    {
        //游戏暂停,不可以点击重新开始游戏
        ui->pushButton->setEnabled(false);
    }
    else
    {
        ui->pushButton->setEnabled(true);
    }
    preMan.clear();
    nextMan.clear();

    if(gameOnline == 1)
    {
        //主机
        chatDlg.linkSendMessage("data" + chessmanDataToMessage());
    }
    else if(gameOnline == 2)
    {
        //接受者
        gameLevelSetValue();
    }
    else
    {
        gameLevel = ui->comboBox->currentIndex(); //游戏等级
        gameRole = gameLevel;
        gameLevelSetValue();
        chessmanData = new int* [manNum];
        for(int i=0; i<manNum; i++)
            chessmanData[i] = new int[manNum];
        randomp(); //生成随机地图
    }

    gameTime.restart(); //计时开始

    update(); //刷新界面
}

void Dialog::on_pushButton_3_clicked()
{
    //排行榜
    listDlg.show();
}

void Dialog::on_pushButton_4_clicked()
{
    //更换背景图
    QString tempfile;
    tempfile = QFileDialog::getOpenFileName(this,
         tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));

    if (!backgroundPixmap.load(tempfile))
    {
        return;
    }

    update();
}

void Dialog::on_pushButton_5_clicked()
{
    //游戏暂停
    if (gamePause == true)
    {
        gamePause = false;
        ui->pushButton_5->setText("暂停游戏");
        ui->pushButton->setEnabled(true);
    }
    else
    {
        gamePause = true;
        ui->pushButton_5->setText("开始游戏");
        ui->pushButton->setEnabled(false);
    }

    update(GAMEAEROX, GAMEAEROY, BOARDWIDE, BOARDWIDE); //只更新面板
}

void Dialog::on_pushButton_2_clicked()
{
    //多人游戏
    gameOnline = 1;
    chatDlg.linkSendMessage("game");
}

void Dialog::paintEvent(QPaintEvent *)
{
    //绘图
    int i = 0;
    int j = 0;
    int selectXY = 0;
    QPixmap temp;
    QPainter painter(this);

    temp = backgroundPixmap.scaled(BOARDWIDE, BOARDHIGH, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(GAMEAEROX, GAMEAEROY, temp);

    if(gamePause == true)
    {
        painter.drawPixmap(GAMEAEROX, GAMEAEROY, QPixmap(":/pic/pause.png"));
    }
    else
    {
        if(gameStart == true)
        {
            for(i=0; i<manNum; i++)
                for(j=0; j<manNum; j++)
                {
                    selectXY = 0;
                    if(preMan.getX() == j)
                        if(preMan.getY() == i)
                            if(preMan.getType() != NOCHESSMAN)
                                selectXY = REDUCEXY;

                    temp = pixmaps[chessmanData[i][j]].scaled((manWide-2*selectXY), (manHigh-2*selectXY), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                    painter.drawPixmap(GAMEAEROX+(manWide*j)+selectXY, GAMEAEROY+(manHigh*i)+selectXY, temp);
                }
        }
        else
        {
            painter.drawPixmap(GAMEAEROX, GAMEAEROY, QPixmap(":/pic/start.png"));
        }
    }

    if(gameOver == true)
    {
        painter.drawPixmap(GAMEAEROX, GAMEAEROY, QPixmap(":/pic/over.png"));
    }
}

void Dialog::mousePressEvent(QMouseEvent *event)
{
    //鼠标压下
    int x = 0;
    int y = 0;

    if(gameStart == true)
    {
        if(gamePause == true)
        {
        }
        else
        {
            x = (event->pos().x() - GAMEAEROX) / manWide;
            y = (event->pos().y() - GAMEAEROY) / manHigh;
            if(preMan.typeExist() == true)
            {
                if(nextMan.typeExist() == true)
                {
                }
                else
                {
                    nextMan.set(x, y, chessmanData[y][x]);
                    update(GAMEAEROX, GAMEAEROY, BOARDWIDE, BOARDWIDE);
                    matchChessman();
                }
            }
            else
            {
                preMan.set(x, y, chessmanData[y][x]);
                update(GAMEAEROX, GAMEAEROY, BOARDWIDE, BOARDWIDE);
            }
        }
    }
}

void Dialog::gameOnlineRandomp()
{
    //多人游戏随机地图
    gameLevel = ui->comboBox->currentIndex(); //游戏等级
    gameRole = gameLevel;

    ui->progressBar_2->setValue(100);

    gameRole += NUMTOUNICODE;
    chatDlg.linkSendMessage("level" + QString(QChar(gameRole)));
    gameRole -= NUMTOUNICODE;

    gameLevelSetValue();

    chessmanData = new int* [manNum];
    for(int i=0; i<manNum; i++)
        chessmanData[i] = new int[manNum];

    randomp();

    on_pushButton_clicked(); //开始游戏
}

void Dialog::gameOnlineLevel()
{
    gameLevel = gameRole;

    ui->progressBar_2->setValue(100);
}

void Dialog::gameOnlineServer()
{
    //主机
    gameOnline = 1;
}

void Dialog::gameOnlineClient()
{
    //从机
    gameOnline = 2;
}

void Dialog::gamePlayerOne()
{
    //只有一个玩家
    ui->pushButton_2->setEnabled(false);
}

void Dialog::gamePlayerTwo()
{
    //有多个玩家
    ui->pushButton_2->setEnabled(true);
}

void Dialog::gameOnlineProgressBar()
{
    //更新右侧进度条
    ui->progressBar_2->setValue(onlineManLeft);
}

void Dialog::gameOnlineGameOver()
{
    //游戏结束
    gameOnline = false;
    gameOver = true;
    update(GAMEAEROX, GAMEAEROY, BOARDWIDE, BOARDWIDE); //只更新面板
}

void Dialog::gameLevelSetValue()
{
    switch(gameLevel)
    {
    case 0:
        //等级1
        manNum = LEVELONEMANNUM; //棋盘棋子个数 10*10 20*20 25*25
        manTypeNum = LEVELONETYPENUM; //棋盘棋子类型数目  10 15 25
        break;
    case 1:
        manNum = LEVELTWOMANNUM;
        manTypeNum = LEVELTWOTYPENUM;
        break;
    case 2:
        manNum = LEVELTHREEMANNUM;
        manTypeNum = LEVELTHREETYPENUM;
        break;
    default:
        manNum = LEVELONEMANNUM;
        manTypeNum = LEVELONETYPENUM;
        break;
    }
    manWide = BOARDWIDE / manNum;
    manHigh = BOARDHIGH / manNum;

    manSum = manNum * manNum;
    manLeft = manSum;
    ui->progressBar->setValue(manLeft*100/manSum);
}

void Dialog::randomp()
{
    //随机地图
    int i = 0;
    int j = 0;
    int k = 0;
    int lastX = 0;
    int lastY = 0;
    int typeNum = 0;

    qsrand(QTime::currentTime().toString("hms").toInt());
    for(i=0; i<manNum; i++)
        for(j=0; j<manNum; j++)
            chessmanData[i][j] = qrand() % (manTypeNum+1);  //取到(0~manTypeNum)


    //去掉单数
    for(i=1; i<=manTypeNum; i++)
    {
        typeNum = 0;
        for(j=0; j<manNum; j++)
        {
            for(k=0; k<manNum; k++)
            {
                if(chessmanData[j][k] == i)
                {
                    lastX = k;
                    lastY = j;
                    typeNum++;
                }
            }
        }

        if(typeNum%2==1)
        {
            chessmanData[lastY][lastX] = NOCHESSMAN;
        }
    }

    //从总数中去掉0
    for(i=0; i<manNum; i++)
        for(j=0; j<manNum; j++)
            if(chessmanData[i][j] == NOCHESSMAN)
            {
                manSum--;
                manLeft--;
            }
}

bool Dialog::matchChessman()
{
    bool matchFlag = false;
    if(preMan.typeExist() == true)
    {
        if(nextMan.typeExist() == true)
        {
            if(preMan == nextMan)
            {
                if((preMan.getX()==nextMan.getX())&&(preMan.getY()==nextMan.getY()))
                {
                    //同一个棋子
                }
                else
                {
                    if(matchDirect(preMan, nextMan))
                    {
                        matchFlag = true;
                    }

                    if((matchOneCorner(preMan, nextMan))||(matchTwoCorner(preMan, nextMan)))
                    {
                        matchFlag = true;
                    }
                }
            }
            else
            {
                //棋子类型不匹配
            }
        }
        else
        {
            //棋子没有数据
        }
    }
    else
    {
        //棋子没有数据
    }

    if(matchFlag == true)
    {
        //画线 刷新
        chessmanData[preMan.getY()][preMan.getX()] = NOCHESSMAN;
        chessmanData[nextMan.getY()][nextMan.getX()] = NOCHESSMAN;
        manLeft -= 2;
        ui->progressBar->setValue(manLeft*100/manSum);
        update(GAMEAEROX, GAMEAEROY, BOARDWIDE, BOARDWIDE); //只更新面板

        if(gameOnline != 0)
        {
            chatDlg.linkSendMessage("left" + QString(QChar(manLeft*100/manSum + NUMTOUNICODE)));
        }
        else
        {
        }

        if(manLeft == 0)
        {
            //完成
            if(gameOnline != 0)
            {
                chatDlg.linkSendMessage("win");
                gameOver = true;
                update(GAMEAEROX, GAMEAEROY, BOARDWIDE, BOARDWIDE); //只更新面板
            }
            else
            {
                gameOver = true;
                update(GAMEAEROX, GAMEAEROY, BOARDWIDE, BOARDWIDE); //只更新面板
                recordDlg.show();
            }
        }
    }
    else
    {
    }

    preMan.clear();
    nextMan.clear();

    return matchFlag;
}

bool Dialog::matchDirect(chessman preManTmp, chessman nextManTmp)
{
    //两棋子的x或y坐标必须有且只有一个相同才能直接相连
    if(!((preManTmp.getX()==nextManTmp.getX())||(preManTmp.getY()==nextManTmp.getY())))
        return false;

    //判断两棋子间是否有其他图片阻隔
    int i ;
    bool match_x = false;
    if(preManTmp.getX() == nextManTmp.getX())
    {
        match_x = true;
        if(preManTmp.getY() > nextManTmp.getY())
            for(i=preManTmp.getY()-1; i>nextManTmp.getY(); --i)
                if(chessmanData[i][preManTmp.getX()] != NOCHESSMAN)
                    match_x = false;
        if(nextManTmp.getY() > preManTmp.getY())
            for(i=nextManTmp.getY()-1; i>preManTmp.getY(); --i)
                if(chessmanData[i][preManTmp.getX()] != NOCHESSMAN)
                    match_x = false;
    }

    bool match_y = false;
    if(preManTmp.getY() == nextManTmp.getY())
    {
        match_y = true;
        if(preManTmp.getX() > nextManTmp.getX())
            for(i=preManTmp.getX()-1; i>nextManTmp.getX(); --i)
                if(chessmanData[preManTmp.getY()][i] != NOCHESSMAN)
                    match_y = false;
        if(nextManTmp.getX() > preManTmp.getX())
            for(i=nextManTmp.getX()-1; i>preManTmp.getX(); --i)
                if(chessmanData[preManTmp.getY()][i] != NOCHESSMAN)
                    match_y = false;
    }

    if(match_x || match_y)
    {
        return true ;
    }

    return false ;
}

bool Dialog::matchOneCorner(chessman preManTmp, chessman nextManTmp)
{
    chessman manTmp;

    manTmp.set(preManTmp.getX(), nextManTmp.getY(), chessmanData[preManTmp.getX()][nextManTmp.getY()]);
    if( chessmanData[nextManTmp.getY()][preManTmp.getX()] == NOCHESSMAN
            && matchDirect(preManTmp, manTmp)
            && matchDirect(nextManTmp, manTmp))
    {
        return true ;
    }

    manTmp.set(nextManTmp.getX(), preManTmp.getY(), chessmanData[nextManTmp.getX()][preManTmp.getY()]);
    if(chessmanData[preManTmp.getY()][nextManTmp.getX()] == NOCHESSMAN
            && matchDirect(preManTmp, manTmp)
            && matchDirect(nextManTmp, manTmp))
    {
        return true ;
    }
    return false ;
}

bool Dialog::matchTwoCorner(chessman preManTmp, chessman nextManTmp)
{
    int i;
    chessman manTmp;

    //转化为a与c能直接相连，而c与b可以通过有一个转角的折线相连的情况
    for(i=preManTmp.getX()-1; i>0; --i)
        if(chessmanData[preManTmp.getY()][i] == NOCHESSMAN)
        {
            manTmp.set(i, preManTmp.getY(), NOCHESSMAN);
            if(matchOneCorner(manTmp, nextManTmp) )
            {
                return true ;
            }
        }
        else
        {
            break;
        }

    for(i=preManTmp.getX()+1; i<manNum; ++i)
        if(chessmanData[preManTmp.getY()][i] == NOCHESSMAN)
        {
            manTmp.set(i, preManTmp.getY(), NOCHESSMAN);
            if(matchOneCorner(manTmp, nextManTmp) )
            {
                return true ;
            }
        }
        else
        {
            break;
        }

    for(i=preManTmp.getY()-1; i>0; --i)
        if(chessmanData[i][preManTmp.getX()] == NOCHESSMAN)
        {
            manTmp.set(preManTmp.getX(), i, NOCHESSMAN);
            if(matchOneCorner(manTmp, nextManTmp) )
            {
                return true ;
            }
        }
        else
        {
            break;
        }

    for(i=preManTmp.getY()+1; i<manNum; ++i)
        if(chessmanData[i][preManTmp.getX()] == NOCHESSMAN)
        {
            manTmp.set(preManTmp.getX(), i, NOCHESSMAN);
            if(matchOneCorner(manTmp, nextManTmp) )
            {
                return true ;
            }
        }
        else
        {
            break;
        }

    return false ;
}

void Dialog::initPixmaps()
{
    pixmaps.append(QPixmap(":/pic/0.png"));
    pixmaps.append(QPixmap(":/pic/1.png"));
    pixmaps.append(QPixmap(":/pic/2.png"));
    pixmaps.append(QPixmap(":/pic/3.png"));
    pixmaps.append(QPixmap(":/pic/4.png"));
    pixmaps.append(QPixmap(":/pic/5.png"));
    pixmaps.append(QPixmap(":/pic/6.png"));
    pixmaps.append(QPixmap(":/pic/7.png"));
    pixmaps.append(QPixmap(":/pic/8.png"));
    pixmaps.append(QPixmap(":/pic/9.png"));
    pixmaps.append(QPixmap(":/pic/10.png"));
    pixmaps.append(QPixmap(":/pic/11.png"));
    pixmaps.append(QPixmap(":/pic/12.png"));
    pixmaps.append(QPixmap(":/pic/13.png"));
    pixmaps.append(QPixmap(":/pic/14.png"));
    pixmaps.append(QPixmap(":/pic/15.png"));
    pixmaps.append(QPixmap(":/pic/16.png"));
    pixmaps.append(QPixmap(":/pic/17.png"));
    pixmaps.append(QPixmap(":/pic/18.png"));
    pixmaps.append(QPixmap(":/pic/19.png"));
    pixmaps.append(QPixmap(":/pic/20.png"));
    pixmaps.append(QPixmap(":/pic/21.png"));
    pixmaps.append(QPixmap(":/pic/22.png"));
    pixmaps.append(QPixmap(":/pic/23.png"));
    pixmaps.append(QPixmap(":/pic/24.png"));
    pixmaps.append(QPixmap(":/pic/25.png"));

    backgroundPixmap.load(":/pic/back.png");
}
