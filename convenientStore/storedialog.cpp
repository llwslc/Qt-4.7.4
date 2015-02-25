#include "storedialog.h"
#include "ui_storedialog.h"

storeDialog::storeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::storeDialog)
{
    ui->setupUi(this);

    resize(644, 484);
    setMaximumWidth(644);
    setMinimumWidth(644);
    setMaximumHeight(484);
    setMinimumHeight(484);//固定窗口大小

    //初始化开始面板
    ui->label_4->clear();
    ui->label_4->setStyleSheet(QString("QLabel{border-image: url(:/images/start.png)0 0 0 0;}"));
    ui->pushButton->setStyleSheet(QString("QPushButton{border-image: url(:/images/button1.png)4 4 4 4; border-width: 4;}") //上 右 下 左
                                  + QString("QPushButton:hover{border-image: url(:/images/button2.png)4 4 4 4; border-width: 4;}")
                                  + QString("QPushButton:pressed{border-image: url(:/images/button3.png)4 4 4 4; border-width: 4;}"));
    ui->pushButton_19->setStyleSheet(QString("QPushButton{border-image: url(:/images/button1.png)4 4 4 4; border-width: 4;}") //上 右 下 左
                                  + QString("QPushButton:hover{border-image: url(:/images/button2.png)4 4 4 4; border-width: 4;}")
                                  + QString("QPushButton:pressed{border-image: url(:/images/button3.png)4 4 4 4; border-width: 4;}"));

    //初始化杯子与颜色
    setCup = 1;
    setCol = 1;
    score = 0;

    //初始化血槽
    heartCount = 5;

    ui->pushButton_1->setStyleSheet(QString("QPushButton{border-image: url(:/images/cup1_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/cup1_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/cup1_2.png)0 0 0 0;}"));
    ui->pushButton_2->setStyleSheet(QString("QPushButton{border-image: url(:/images/cup2_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/cup2_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/cup2_2.png)0 0 0 0;}"));
    ui->pushButton_3->setStyleSheet(QString("QPushButton{border-image: url(:/images/cup3_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/cup3_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/cup3_2.png)0 0 0 0;}"));
    ui->pushButton_4->setStyleSheet(QString("QPushButton{border-image: url(:/images/cup4_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/cup4_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/cup4_2.png)0 0 0 0;}"));
    ui->pushButton_5->setStyleSheet(QString("QPushButton{border-image: url(:/images/cup5_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/cup5_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/cup5_2.png)0 0 0 0;}"));
    ui->pushButton_6->setStyleSheet(QString("QPushButton{border-image: url(:/images/cup6_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/cup6_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/cup6_2.png)0 0 0 0;}"));
    ui->pushButton_7->setStyleSheet(QString("QPushButton{border-image: url(:/images/color1_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/color1_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/color1_2.png)0 0 0 0;}"));
    ui->pushButton_8->setStyleSheet(QString("QPushButton{border-image: url(:/images/color2_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/color2_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/color2_2.png)0 0 0 0;}"));
    ui->pushButton_9->setStyleSheet(QString("QPushButton{border-image: url(:/images/color3_1.png)0 0 0 0;}") //上 右 下 左
                                    + QString("QPushButton:hover{border-image: url(:/images/color3_2.png)0 0 0 0;}")
                                    + QString("QPushButton:pressed{border-image: url(:/images/color3_2.png)0 0 0 0;}"));
    ui->pushButton_10->setStyleSheet(QString("QPushButton{border-image: url(:/images/color4_1.png)0 0 0 0;}") //上 右 下 左
                                     + QString("QPushButton:hover{border-image: url(:/images/color4_2.png)0 0 0 0;}")
                                     + QString("QPushButton:pressed{border-image: url(:/images/color4_2.png)0 0 0 0;}"));
    ui->pushButton_11->setStyleSheet(QString("QPushButton{border-image: url(:/images/color5_1.png)0 0 0 0;}") //上 右 下 左
                                     + QString("QPushButton:hover{border-image: url(:/images/color5_2.png)0 0 0 0;}")
                                     + QString("QPushButton:pressed{border-image: url(:/images/color5_2.png)0 0 0 0;}"));
    ui->pushButton_12->setStyleSheet(QString("QPushButton{border-image: url(:/images/color6_1.png)0 0 0 0;}") //上 右 下 左
                                     + QString("QPushButton:hover{border-image: url(:/images/color6_2.png)0 0 0 0;}")
                                     + QString("QPushButton:pressed{border-image: url(:/images/color6_2.png)0 0 0 0;}"));
    ui->pushButton_13->setStyleSheet(QString("QPushButton{border-image: url(:/images/button1.png)4 4 4 4; border-width: 4;}") //上 右 下 左
                                     + QString("QPushButton:hover{border-image: url(:/images/button2.png)4 4 4 4; border-width: 4;}")
                                     + QString("QPushButton:pressed{border-image: url(:/images/button3.png)4 4 4 4; border-width: 4;}"));
    ui->pushButton_14->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
    ui->pushButton_15->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
    ui->pushButton_16->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
    ui->pushButton_17->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
    ui->pushButton_18->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左

    ui->label->setText("分数 : " + QString::number(score));
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label->setStyleSheet("QLabel{border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #f0bcd7;}");
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/null.png)0 0 0 0;}");
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/null.png)0 0 0 0;}");

    //场景
    sceneWidth = 640;
    sceneHeight = 480;
    scene.setSceneRect(-(sceneWidth/2), -(sceneHeight/2), sceneWidth, sceneHeight);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setStyleSheet("background: transparent");

    //背景上半部分
    bgUp = new bgUpItem;
    bgUp->setPos(0,
                 int(-(sceneHeight - bgUp->mHeight) / 2));
    bgUp->setRotation(0);
    bgUp->setZValue(-2);
    scene.addItem(bgUp);

    //背景下半部分
    bgDown = new bgDownItem;
    bgDown->setPos(0,
                   int((sceneHeight - bgDown->mHeight) / 2));
    bgDown->setRotation(0);
    bgDown->setZValue(0);
    scene.addItem(bgDown);

    //人物
    man = new manItem;
    man->setPos(0,
                int((40 - ((man->mHeight) / 2))));
    man->setRotation(0);
    man->setZValue(-1);
    scene.addItem(man);

    //想法
    think = new thinkItem;
    think->setPos(int(0 + ((man->mWidth + think->mWidth) / 2)),
                  int(-(10 + ((think->mHeight) / 2))));
    think->setRotation(0);
    think->setZValue(-1);
    scene.addItem(think);
}

storeDialog::~storeDialog()
{
    delete ui;
}

void storeDialog::on_pushButton_1_clicked()
{
    //杯1
    setCup = 1;
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/cup" + QString::number(setCup) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_2_clicked()
{
    //杯2
    setCup = 2;
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/cup" + QString::number(setCup) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_3_clicked()
{
    //杯3
    setCup = 3;
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/cup" + QString::number(setCup) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_4_clicked()
{
    //杯4
    setCup = 4;
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/cup" + QString::number(setCup) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_5_clicked()
{
    //杯5
    setCup = 5;
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/cup" + QString::number(setCup) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_6_clicked()
{
    //杯6
    setCup = 6;
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/cup" + QString::number(setCup) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_7_clicked()
{
    //颜色1
    setCol = 1;
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/color" + QString::number(setCol) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_8_clicked()
{
    //颜色2
    setCol = 2;
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/color" + QString::number(setCol) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_9_clicked()
{
    //颜色3
    setCol = 3;
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/color" + QString::number(setCol) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_10_clicked()
{
    //颜色4
    setCol = 4;
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/color" + QString::number(setCol) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_11_clicked()
{
    //颜色5
    setCol = 5;
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/color" + QString::number(setCol) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_12_clicked()
{
    //颜色6
    setCol = 6;
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/color" + QString::number(setCol) + "_1.png)0 0 0 0;}");
}

void storeDialog::on_pushButton_13_clicked()
{
    //卖出
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/null.png)0 0 0 0;}");
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/null.png)0 0 0 0;}");

    if(setCup == think->mCup)
    {
        if(setCol == think->mCol)
        {
            setCup = 0;
            setCol = 0;

            score += 20;
            ui->label->setText("分数 : " + QString::number(score));

            scene.removeItem(man);
            scene.removeItem(think);

            //人物
            man = new manItem;
            man->setPos(0,
                        int((40 - ((man->mHeight) / 2))));
            man->setRotation(0);
            man->setZValue(-1);
            scene.addItem(man);

            //想法
            think = new thinkItem;
            think->setPos(int(0 + ((man->mWidth + think->mWidth) / 2)),
                          int(-(10 + ((think->mHeight) / 2))));
            think->setRotation(0);
            think->setZValue(-1);
            scene.addItem(think);

            return;
        }
    }
    else
    {
        setCup = 0;
        setCol = 0;

        heartCount -= 1;

        scene.removeItem(man);
        scene.removeItem(think);

        //人物
        man = new manItem;
        man->setPos(0,
                    int((40 - ((man->mHeight) / 2))));
        man->setRotation(0);
        man->setZValue(-1);
        scene.addItem(man);

        //想法
        think = new thinkItem;
        think->setPos(int(0 + ((man->mWidth + think->mWidth) / 2)),
                      int(-(10 + ((think->mHeight) / 2))));
        think->setRotation(0);
        think->setZValue(-1);
        scene.addItem(think);
    }

    QPropertyAnimation *ani;

    switch(heartCount)
    {
    case 0:
        ui->pushButton_14->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_15->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_16->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_17->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_18->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左

        recordw.mScore = score;
        recordw.exec();

        ani = new QPropertyAnimation(ui->graphicsView, "pos");
        ani->setDuration(1500);
        ani->setStartValue(QPoint(ui->graphicsView->pos().x(), ui->graphicsView->pos().y()));
        ani->setEndValue(QPoint(this->width(), 0));
        ani->setEasingCurve(QEasingCurve::OutBounce);
        ani->start();

        ani = new QPropertyAnimation(ui->frame, "pos");
        ani->setDuration(1500);
        ani->setStartValue(QPoint(-this->width(), 0));
        ani->setEndValue(QPoint(0, 0));
        ani->setEasingCurve(QEasingCurve::OutBounce);
        ani->start();

        break;
    case 1:
        ui->pushButton_14->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_15->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_16->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_17->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_18->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        break;
    case 2:
        ui->pushButton_14->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_15->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_16->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_17->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_18->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        break;
    case 3:
        ui->pushButton_14->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_15->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_16->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_17->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_18->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        break;
    case 4:
        ui->pushButton_14->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart_.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_15->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_16->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_17->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_18->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        break;
    case 5:
        ui->pushButton_14->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_15->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_16->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_17->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        ui->pushButton_18->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
        break;
    default:
        break;
    }
}

void storeDialog::on_pushButton_clicked()
{
    //开始游戏
    QPropertyAnimation *ani = new QPropertyAnimation(ui->frame, "pos");
    ani->setDuration(1500);
    ani->setStartValue(QPoint(ui->frame->pos().x(), ui->frame->pos().y()));
    ani->setEndValue(QPoint(-this->width(), 0));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

    ani = new QPropertyAnimation(ui->graphicsView, "pos");
    ani->setDuration(1500);
    ani->setStartValue(QPoint(this->width(), 0));
    ani->setEndValue(QPoint(0, 0));
    ani->setEasingCurve(QEasingCurve::OutBounce);
    ani->start();

    //初始化杯子与颜色
    setCup = 1;
    setCol = 1;
    score = 0;

    //初始化血槽
    heartCount = 5;

    ui->pushButton_14->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
    ui->pushButton_15->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
    ui->pushButton_16->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
    ui->pushButton_17->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左
    ui->pushButton_18->setStyleSheet(QString("QPushButton{border-image: url(:/images/heart.png)0 0 0 0;}")); //上 右 下 左

    ui->label->setText("分数 : " + QString::number(score));
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label->setStyleSheet("QLabel{border: 2px solid gray; border-radius: 10px; padding: 0 8px; background: #f0bcd7;}");
    ui->label_2->setStyleSheet("QLabel{border-image: url(:/images/null.png)0 0 0 0;}");
    ui->label_3->setStyleSheet("QLabel{border-image: url(:/images/null.png)0 0 0 0;}");

    scene.removeItem(man);
    scene.removeItem(think);

    //人物
    man = new manItem;
    man->setPos(0,
                int((40 - ((man->mHeight) / 2))));
    man->setRotation(0);
    man->setZValue(-1);
    scene.addItem(man);

    //想法
    think = new thinkItem;
    think->setPos(int(0 + ((man->mWidth + think->mWidth) / 2)),
                  int(-(10 + ((think->mHeight) / 2))));
    think->setRotation(0);
    think->setZValue(-1);
    scene.addItem(think);
}

void storeDialog::on_pushButton_19_clicked()
{
    //排行榜
    listw.show();
}
