#include "logondialog.h"
#include "ui_logondialog.h"

logonDialog::logonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logonDialog)
{
    ui->setupUi(this);

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    this->setWindowTitle("指纹库存管理");

    qFinger = new qFingerprint(this);
    connect(qFinger, SIGNAL(OnImageReceived()), this, SLOT(finishImageReceived()));
    connect(qFinger, SIGNAL(OnFeatureInfo(int)), this, SLOT(finishFeatureInfo(int)));
    connect(qFinger, SIGNAL(OnCapture(QVariant)), this, SLOT(finishCapture(QVariant)));

    connect(&regw, SIGNAL(OnClose()), this, SLOT(selfShow()));
    connect(&mainw, SIGNAL(OnClose()), this, SLOT(selfShow()));
    connect(&mainw, SIGNAL(OnExit()), this, SLOT(exitApp()));

    //初始化指纹特征码数据
    initFingerTempMap();

    init();

    on_pushButton_clicked();
}

logonDialog::~logonDialog()
{
    qFinger->EndEngine();
    delete ui;
}

void logonDialog::init()
{
    //初始化
    crackerFlag = 0;
    ui->lineEdit->setEnabled(false);
    ui->label_2->clear();
    ui->label_2->setScaledContents(true);
    ui->label_3->clear();
    ui->label_3->setText("指纹质量 : ");
    ui->label_6->setText("正在查找 ...");

    ui->lineEdit_2->clear();
    ui->lineEdit_2->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->comboBox->clear();
    ui->comboBox->addItem("员工");
    ui->comboBox->addItem("采购员");
    ui->comboBox->addItem("保管员");
    ui->comboBox->addItem("主管");
    ui->comboBox->setCurrentIndex(0);

    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);

    ui->lineEdit_3->clear();
}

void logonDialog::paintEvent(QPaintEvent *)
{}

void logonDialog::closeEvent(QCloseEvent *)
{}

void logonDialog::initFingerTempMap()
{
    //初始化当前的指纹模板
    QSqlQuery query;
    QString sql;
    int userid;
    QString fingerTempStr;
    QVariant fingerTempVar;

    sql = "select * from users";
    query.exec(sql);

    while(query.next())
    {
        userid = query.value(0).toInt();
        fingerTempStr = query.value(4).toString();
        fingerTempVar = qFinger->DecodeTemplate(fingerTempStr);
        insertFingerTempMap(userid, fingerTempVar);
    }
}

void logonDialog::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_Control:
        crackerFlag = 1;
        break;
    case Qt::Key_Alt:
        if(crackerFlag == 1)
        {
            crackerFlag = 2;
        }
        else
        {
            crackerFlag = 0;
        }
        break;
    case Qt::Key_F1:
        if(crackerFlag == 2)
        {
            crackerw.show();
        }
        else
        {
        }
        crackerFlag = 0;
        break;
    default:
        crackerFlag = 0;
        break;
    }
}

void logonDialog::findFingerUser(int mUserid)
{
    //查找人员信息
    QSqlQuery query;
    QString sql;
    int role = 0;

    sql = "select * from users where usersid = '" + QString::number(mUserid, 10) + "'";
    query.exec(sql);

    while(query.next())
    {
        ui->lineEdit_2->setText(query.value(1).toString());
        role = query.value(3).toInt();
        ui->comboBox->setCurrentIndex(role);
    }

    switch(role)
    {
    case 0:
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        break;
    case 1:
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        break;
    case 2:
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
        break;
    case 3:
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        break;
    default:
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        break;
    }
}

void logonDialog::on_pushButton_clicked()
{
    //连接指纹器
    int result = -1;
    QString strSN = "指纹仪器未连接!";
    result = qFinger->InitEngine();

    if(result == 0)
    {
        strSN = qFinger->SensorSN();
    }
    else
    {
        qFinger->EndEngine();
        QMessageBox::information(NULL, "error.", "初始化指纹仪失败!");
    }
    ui->lineEdit->setText(QString(strSN));
}

void logonDialog::selfShow()
{
    //显示自己
    init();
    on_pushButton_clicked();
    this->show();
}

void logonDialog::exitApp()
{
    //关闭程序
    this->close();
}

void logonDialog::finishImageReceived()
{
    //指纹图像完成
    qFinger->SaveBitmap();
    ui->label_2->setPixmap(QPixmap(fingerBmpPath));
}

void logonDialog::finishFeatureInfo(int Aquality)
{
    //指纹质量报告
    switch(Aquality)
    {
    case 0:
        ui->label_3->setText("指纹质量 : 合格");
        break;
    case 1:
        ui->label_3->setText("指纹质量 : 特征点不够");
        break;
    case 2:
        ui->label_3->setText("指纹质量 : 无法取到指纹特征");
        break;
    default:
        ui->label_3->setText("指纹质量 : ");
        break;
    }
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->label_6->setText("正在对比 ...");
}

void logonDialog::finishCapture(QVariant ATemplate)
{
    //指纹对比
    QMapIterator<int, QVariant> i(fingerTemplateMap);
    while (i.hasNext())
    {
        i.next();
        if(qFinger->VerFinger(ATemplate, i.value()))
        {
            ui->label_6->setText("查找成功 ...");
            findFingerUser(i.key());
        }
    }
}

void logonDialog::on_pushButton_2_clicked()
{
    //指纹管理
    QString strSN = "指纹仪器未连接!";
    ui->lineEdit->setText(QString(strSN));

    qFinger->EndEngine();
    regw.show();
    this->close();
}

void logonDialog::on_pushButton_3_clicked()
{
    //库存管理
    QString strSN = "指纹仪器未连接!";
    ui->lineEdit->setText(QString(strSN));

    qFinger->EndEngine();
    mainw.show();
    this->close();
}

void logonDialog::on_pushButton_4_clicked()
{
    //密码登陆
    QSqlQuery query;
    QString sql;

    sql = "select * from person where pwd = '" + ui->lineEdit_3->text().trimmed() + "'";
    query.exec(sql);

    if (query.next())
    {
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->lineEdit_3->clear();
    }
    else
    {
        QMessageBox::information(NULL, "error.", "密码错误!");

        ui->lineEdit_3->clear();
    }
}
