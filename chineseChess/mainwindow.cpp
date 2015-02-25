#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    //定义棋盘数组.用于显示棋盘
    //初始化棋盘
    chessGameOver = 0;

    memcpy(m_ChessBoard, InitChessBoard, 4*90);

    m_MoveChess.nChessID = NOCHESS;
    m_BoardBmp.load(":/pic/board.png");
    m_Chessman.load(":/pic/chessmanBLACK.png");
    chessmanRed = false;

    CMoveGenerator *pMG;
    CEveluation *pEvel;
    //创建负极大值搜索引擎
    m_pSE = new CNegaMaxEngine;
    //创建走法产生器
    pMG = new CMoveGenerator;
    //创建估值核心
    pEvel = new CEveluation;

    //设定搜索层数为3
    m_pSE->SetSearchDepth(3);
    //给搜索引擎设定走法产生器
    m_pSE->SetMoveGenerator(pMG);
    //给搜索引擎设定估值核心
    m_pSE->SetEveluator(pEvel);
    ui->pushButton_3->setEnabled(false);
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::paintEvent(QPaintEvent *)
{
    //绘图
    int i = 0;
    int j = 0;
    QPixmap temp;
    QPainter painter(this);

    temp = m_BoardBmp.scaled(BOARDWIDTH, BOARDHEIGHT, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(BOARDSTARTX, BOARDSTARTY, temp);

    for(i=0; i<10; i++)
        for(j=0; j<9; j++)
        {
            if(m_ChessBoard[i][j] == NOCHESS)
                continue;
            temp = m_Chessman.copy((m_ChessBoard[i][j]-1)*GRILLEWIDTH, 0, GRILLEWIDTH, GRILLEHEIGHT);
            painter.drawPixmap(BOARDSTARTY+BOARDMANY+j*(GRILLEHEIGHT+10), BOARDSTARTX+BOARDMANX+i*(GRILLEWIDTH+10), temp);
        }
    //绘制用户正在拖动的棋子
    if (m_MoveChess.nChessID != NOCHESS)
    {
        temp = m_Chessman.copy((m_MoveChess.nChessID - 1)*GRILLEWIDTH, 0, GRILLEWIDTH, GRILLEHEIGHT);
        painter.drawPixmap(m_MoveChess.ptMovePoint, temp);
    }
}

void mainWindow::mousePressEvent(QMouseEvent *event)
{
    //鼠标压下
    int x,y;
    //将坐标换算成棋盘上的格子
    y = (event->y() - (BOARDSTARTX + BOARDMANX)) / (GRILLEHEIGHT + 10);
    x = (event->x() - (BOARDSTARTY + BOARDMANY)) / (GRILLEWIDTH + 10);

    //备份当前棋盘
    memcpy(m_BackupChessBoard, m_ChessBoard, 4*90);
    //判断鼠标是否在棋盘内,并且点钟了红方(用户)棋子
    if(x>=0 && x<9 && y>=0 && y<10  && IsRed(m_ChessBoard[y][x]))
    {
        //备份棋盘
        memcpy(m_BackupChessBoard, m_ChessBoard, 4*90);
        m_ptMoveChess.setX(x);
        m_ptMoveChess.setY(y);
        m_MoveChess.nChessID = m_ChessBoard[y][x];
        //将该棋子原位置棋子去掉
        m_ChessBoard[m_ptMoveChess.y()][m_ptMoveChess.x()] = NOCHESS;
        //让棋子中点坐标位于鼠标所在点
        m_MoveChess.ptMovePoint.setX(event->x()-20);
        m_MoveChess.ptMovePoint.setY(event->y()-20);
        //重绘屏幕
        update(BOARDSTARTX, BOARDSTARTY, BOARDWIDTH, BOARDHEIGHT);
    }
}
void mainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移动
    int x = 0;
    int y = 0;
    if(m_MoveChess.nChessID)
    {
        //防止将棋子拖出棋盘
        if(event->x() < BOARDSTARTX+10) //左面
            x = BOARDSTARTX+10;
        if(event->y() < BOARDSTARTY+10) //上面
            y = BOARDSTARTY+10;
        if(event->x() > BOARDWIDTH) //右边
            x = BOARDWIDTH;
        if(event->y() > BOARDHEIGHT) //下面
            y = BOARDHEIGHT;

        //让棋子的中心位于鼠标所在处
        if (x == 0) //x没出界
            m_MoveChess.ptMovePoint.setX(event->x()-20);
        else
            m_MoveChess.ptMovePoint.setX(x-20);
        if (y == 0) //y没出界
            m_MoveChess.ptMovePoint.setY(event->y()-20);
        else
            m_MoveChess.ptMovePoint.setY(y-20);

        //刷新窗口
        update(BOARDSTARTX, BOARDSTARTY, BOARDWIDTH, BOARDHEIGHT);
    }
}

//全局变量申明,用于统计叶子节点数目
extern int count;
void mainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标松开
    bool bTurnSide = FALSE;
    QTime timeCount;
    int x, y;
    //将坐标换算成棋盘上的格子
    y = (event->y() - (BOARDSTARTX + BOARDMANX)) / (GRILLEHEIGHT + 10);
    x = (event->x() - (BOARDSTARTY + BOARDMANY)) / (GRILLEWIDTH + 10);

    //判断是否有移动棋子,并且该棋子的移动是一个合法走法
    if(m_MoveChess.nChessID && CMoveGenerator::IsValidMove(m_BackupChessBoard,
                                                           m_ptMoveChess.x(), m_ptMoveChess.y(), x, y))
    {
        m_ChessBoard[y][x] = m_MoveChess.nChessID;
        bTurnSide = true;
        ui->pushButton_3->setEnabled(true);
    }
    else
    {
        //恢复移动前的棋盘状态
        memcpy(m_ChessBoard, m_BackupChessBoard, 4*90);
    }
    //将移动的棋子清空
    m_MoveChess.nChessID = NOCHESS;
    //重绘屏幕
    update(BOARDSTARTX, BOARDSTARTY, BOARDWIDTH, BOARDHEIGHT);
    //释放鼠标焦点
    //    ReleaseCapture();

    if(bTurnSide == true)
    {
        //取初始化时间
        timeCount.start();
        //让电脑走下一步
        m_pSE->SearchAGoodMove(m_ChessBoard);
        gameIsOver(m_ChessBoard);

        if(chessGameOver == 1)
        {
            QMessageBox::information(NULL, tr("Game Over"), tr("电脑赢了,同志仍需努力!"));
        }
        if(chessGameOver == 2)
        {
            QMessageBox::information(NULL, tr("Game Over"), tr("英雄战胜电脑!"));
        }

        QString sNodeCount = QString("电脑共花费:\n%1毫秒\n\n评估:\n%2个走法!")
                .arg(timeCount.elapsed()).arg(count);
        //输出上述信息
        ui->label->setText(sNodeCount);
    }
    //计数器清零
    count = 0;
    //重绘屏幕
    update(BOARDSTARTX, BOARDSTARTY, BOARDWIDTH, BOARDHEIGHT);
}

void mainWindow::on_pushButton_clicked()
{
    //新游戏
    CMoveGenerator  *pMG;
    CEveluation	    *pEvel;

    if(m_pSE)
        //释放旧的搜索引擎
        delete m_pSE;

    m_pSE = new CNegaMaxEngine;
    pEvel = new CEveluation;

    //初始化棋盘
    memcpy(m_ChessBoard, InitChessBoard, 4*90);
    //清楚移动棋子
    m_MoveChess.nChessID = NOCHESS;
    //创建走法产生器
    pMG = new CMoveGenerator;
    //将走法传声器传给搜索引擎
    m_pSE->SetMoveGenerator(pMG);
    //将估值核心传给搜索引擎
    m_pSE->SetEveluator(pEvel);
    //刷新窗口
    chessGameOver = 0;
    ui->pushButton_3->setEnabled(false);
    ui->comboBox->setCurrentIndex(0);

    update();
}

void mainWindow::on_pushButton_2_clicked()
{
    //认输
    QMessageBox::information(NULL, tr("Game Over"), tr("电脑赢了,同志仍需努力!"));
    on_pushButton_clicked();
}

void mainWindow::on_pushButton_3_clicked()
{
    //悔棋
    memcpy(m_ChessBoard, m_BackupChessBoard, 4*90);
    ui->pushButton_3->setEnabled(false);
    update();
}

void mainWindow::on_pushButton_4_clicked()
{
    //电脑让子
    int i, j;
    switch(ui->comboBox->currentIndex())
    {
    case 0:
        for(i=0; i<10; i++)
            for(j=0; j<9; j++)
                if(m_ChessBoard[i][j] == B_CAR)
                    m_ChessBoard[i][j] = NOCHESS;
        break;
    case 1:
        for(i=0; i<10; i++)
            for(j=0; j<9; j++)
                if(m_ChessBoard[i][j] == B_HORSE)
                    m_ChessBoard[i][j] = NOCHESS;
        break;
    case 2:
        for(i=0; i<10; i++)
            for(j=0; j<9; j++)
                if(m_ChessBoard[i][j] == B_CANON)
                    m_ChessBoard[i][j] = NOCHESS;
        break;
    default:
        break;
    }

    update();
}

void mainWindow::on_pushButton_5_clicked()
{
    //保存棋局
    QString targetPath = QFileDialog::getSaveFileName(this, tr("save"), "./chessboard/Chessboard" + QDateTime::currentDateTime().toString("dd-MM-yyyy") + ".cb", tr("Chessboard Files(*.cb)"));
    if(targetPath.length() == 0)
    {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else
    {
        QMessageBox::information(NULL, tr("save"), tr("success!"));

        QFile f(targetPath);
        f.open(QIODevice::WriteOnly);
        QTextStream t(&f);
        t << chessmanDataToFile(m_ChessBoard);
        f.close();
    }
}

void mainWindow::on_pushButton_6_clicked()
{
    //加载棋局
    QString sourcePath = QFileDialog::getOpenFileName(this, tr("open"), "./chessboard", tr("Chessboard Files(*.cb)"));
    if(sourcePath.length() == 0)
    {
        QMessageBox::information(NULL, tr("open"), tr("You didn't select any files."));
    }
    else
    {
        QMessageBox::information(NULL, tr("open"), tr("success!"));

        QFile f(sourcePath);
        f.open(QIODevice::ReadOnly);
        QTextStream t(&f);
        chessmanDataFromFile(t.read(90), m_ChessBoard);
        f.close();

        update();
    }
}

void mainWindow::on_pushButton_7_clicked()
{
    //互换颜色
    if(chessmanRed == false)
    {
        m_Chessman.load(":/pic/chessmanRED.png");
        chessmanRed = true;
    }
    else
    {
        m_Chessman.load(":/pic/chessmanBLACK.png");
        chessmanRed = false;
    }

    update();
}
