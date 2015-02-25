#include "fishdialog.h"
#include "ui_fishdialog.h"

fishDialog::fishDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fishDialog)
{
    ui->setupUi(this);

    resize(800, 600);
    setMaximumWidth(800);
    setMinimumWidth(800);
    setMaximumHeight(600);
    setMinimumHeight(600);//固定窗口大小

    ui->pushButton->setStyleSheet(QString("QPushButton{border-image: url(:/images/start.png)0 1084 0 0;}") //上 右 下 左
                                  + QString("QPushButton:hover{border-image: url(:/images/start.png)0 813 0 271;}")
                                  + QString("QPushButton:pressed{border-image: url(:/images/start.png)0 542 0 542;}"));

    ui->pushButton_2->setStyleSheet(QString("QPushButton{border-image: url(:/images/highscore.png)0 1084 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/highscore.png)0 813 0 271;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/highscore.png)0 542 0 542;}"));

    ui->pushButton_3->setStyleSheet(QString("QPushButton{border-image: url(:/images/instruction.png)0 1084 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/instruction.png)0 813 0 271;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/instruction.png)0 542 0 542;}"));

    ui->pushButton_4->setStyleSheet(QString("QPushButton{border-image: url(:/images/exit.png)0 1084 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/exit.png)0 813 0 271;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/exit.png)0 542 0 542;}"));

    scene.setSceneRect(-(this->width()/2), -(this->height()/2), this->width()-5, this->height()-5);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setStyleSheet("background: transparent");
    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //ui->graphicsView->setBackgroundBrush(QPixmap(":/images/game.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    //ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    //ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    QObject::connect(&FishSwimTimer, SIGNAL(timeout()), &scene, SLOT(advance()));
    QObject::connect(&FishOutTimer, SIGNAL(timeout()), this, SLOT(FishOut()));
    QObject::connect(&GameTimer, SIGNAL(timeout()), this, SLOT(GameOver()));

    gameStart = MAIN;

    //发射台
    bar = new barItem;
    bar->setPos(0,
                int(scene.sceneRect().height() / 2) - int(bar->barHeight / 2));
    bar->setRotation(0);
    scene.addItem(bar);
    //炮台
    cannon = new cannonItem;
    cannon->setPos(int(cannon->cannonWidth / 2) + 10,
                   int(scene.sceneRect().height() / 2) - int(cannon->cannonHeight / 2));
    cannon->setRotation(0);
    scene.addItem(cannon);
    //暂停
    pause = new pauseItem;
    pause->setPos(0, 0);
    pause->setRotation(0);
    //关于
    about = new aboutItem;
    about->setPos(0, 0);
    about->setRotation(0);
    //进度
    ui->progressBar->setValue(100);

}

fishDialog::~fishDialog()
{
    delete ui;
}

void fishDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/images/bg.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void fishDialog::on_pushButton_clicked()
{
    //开始
    if(gameStart == MAIN)
    {
        scene.clear();
        bar = new barItem;
        bar->setPos(0,
                    int(scene.sceneRect().height() / 2) - int(bar->barHeight / 2));
        bar->setRotation(0);
        scene.addItem(bar);
        //炮台
        cannon = new cannonItem;
        cannon->setPos(int(cannon->cannonWidth / 2) + 10,
                       int(scene.sceneRect().height() / 2) - int(cannon->cannonHeight / 2));
        cannon->setRotation(0);
        scene.addItem(cannon);
        //暂停
        pause = new pauseItem;
        pause->setPos(0, 0);
        pause->setRotation(0);

        FishSwimTimer.start(1000 / 15);
        FishOutTimer.start(1000 * 5);
        GameTimer.start(1000);
        FishOut();
        score = 0;
        secondTime = 0;
        gameStart = START;
        ui->progressBar->setValue(100);
    }
}

void fishDialog::on_pushButton_2_clicked()
{
    //排行榜
    listw.show();
}

void fishDialog::on_pushButton_3_clicked()
{
    //游戏介绍
    scene.addItem(about);
}

void fishDialog::on_pushButton_4_clicked()
{
    //退出
    close();
}

void fishDialog::FishOut()
{
    int MouseCount = 10;
    for (int i = 0; i < MouseCount; ++i) {
        fishItem *fish = new fishItem;
        int randX = (int)qrand();
        int randY = (int)qrand();
        int randA = (int)qrand();

        //pow(-1, rand) 用于产生(-1, 1)
        //rand % 2 用于产生(0, 1)
        fish->setPos(int(scene.sceneRect().width()/2) * pow(-1, randX),
                     int(scene.sceneRect().height()/2) * pow(-1, randY) * (double(randY % 10) /10));
        fish->setZValue(-1.0);
        if(fish->pos().x() < 0)
        {
            fish->setRotation((randA % (90)) + (270) * (randA % 2));
        }
        else
        {
            fish->setRotation((randA % (180)) + 90);
        }
        scene.addItem(fish);
    }
}

void fishDialog::GameOver()
{
    //游戏结束
    if(score >= 1000)
    {
        FishSwimTimer.stop();
        FishOutTimer.stop();
        GameTimer.stop();
        gameStart = MAIN;
        recordw.mSecondTime = secondTime;
        recordw.show();
        score = 0;
        secondTime = 0;
    }
    else
    {
        ui->progressBar->setValue(ui->progressBar->value() - 1);
        secondTime++;
    }

    if(0 == ui->progressBar->value())
    {
        FishSwimTimer.stop();
        FishOutTimer.stop();
        GameTimer.stop();
        gameStart = MAIN;
        score = 0;
        secondTime = 0;
        QMessageBox::information(NULL, QString("Over"), QString("输啦,下次再来!"));
    }
}

void fishDialog::keyPressEvent(QKeyEvent *e)
{
    //按键
    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent* event = static_cast<QKeyEvent*>(e);
        switch (event->key())
        {
        case Qt::Key_P:       //按下p键发送暂停游戏的信号
            switch(gameStart)
            {
            case START:
                FishSwimTimer.stop();
                FishOutTimer.stop();
                GameTimer.stop();
                gameStart = PAUSE;
                scene.addItem(pause);
                break;
            case PAUSE:
                FishSwimTimer.start(1000 / 15);
                FishOutTimer.start(1000 * 5);
                GameTimer.start(1000);
                gameStart = START;
                scene.removeItem(pause);
                break;
            default:
                break;
            }
            break;
        case Qt::Key_Escape:
            close();
            break ;
        default:
            break;
        }
    }
}

void fishDialog::mousePressEvent(QMouseEvent *e)
{
    //鼠标点击
    if(gameStart == START)
    {
        int cannonX = 440;
        int cannonY = 550;
        int posX = e->pos().x();
        int posY = e->pos().y();
        double Pi = 3.14159265358979323846264338327950288419717;
        double angle = 0.0;

        angle = 180 * (atan((double)(posY-cannonY)/(posX-cannonX))) / Pi;
        if(posY <= cannonY)          //将角度转换为0-360度
        {
            if(posX >= cannonX)
            {
                angle += 90;
            }
            else
            {
                angle += 270;
            }
        }

        cannon->setRotation(angle);
        scene.removeItem(cannon);
        scene.addItem(cannon);

        bulletItem *bullet = new bulletItem;
        bullet->setPos(int(cannon->cannonWidth / 2) + 10,
                       int(scene.sceneRect().height() / 2) - int(cannon->cannonHeight / 2));
        bullet->setRotation(angle);
        bullet->setZValue(-1.0);
        scene.addItem(bullet);
    }
}
