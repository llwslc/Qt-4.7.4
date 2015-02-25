#include "randomdialog.h"
#include "ui_randomdialog.h"

randomDialog::randomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::randomDialog)
{
    ui->setupUi(this);

    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
    ui->label_12->clear();
}

randomDialog::~randomDialog()
{
    delete ui;
}

void randomDialog::on_pushButton_clicked()
{
    //每日推荐
    int clothesNum = 0;
    int bagNum = 0;
    int cosNum = 0;
    int shoeNum = 0;
    int breakFlag = 0;

    //获取该类衣服总数
    QSqlQuery query;
    query.exec("select * from clothes where type = 0 and season ='"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
               + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
    while(query.next())
        clothesNum++;

    //获取一个随机数,范围是0-衣服总数
    qsrand(QTime::currentTime().toString("hms").toInt());
    breakFlag = qrand() % clothesNum;
    clothesNum = 0;

    query.exec("select * from clothes where type = 0 and season ='"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
               + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
    while(query.next())
    {
        if(clothesNum++ == breakFlag)
        {
            ui->label_9->setText(query.value(1).toString());
            ui->label->setScaledContents(true);
            ui->label->setPixmap(query.value(11).toString());
            break;
        }
    }
    //包包
    query.exec("select * from clothes where type = 1 and season ='"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
               + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
    while(query.next())
        bagNum++;

    qsrand(QTime::currentTime().toString("shm").toInt());
    breakFlag = qrand() % bagNum;
    bagNum = 0;

    query.exec("select * from clothes where type = 1 and season ='"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
               + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
    while(query.next())
    {
        if(bagNum++ == breakFlag)
        {
            ui->label_10->setText(query.value(1).toString());
            ui->label_2->setScaledContents(true);
            ui->label_2->setPixmap(query.value(11).toString());
            break;
        }
    }
    //装饰
    query.exec("select * from clothes where type = 2 and season ='"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
               + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
    while(query.next())
        cosNum++;

    qDebug() << cosNum << endl;

    qsrand(QTime::currentTime().toString("msh").toInt());
    breakFlag = qrand() % cosNum;
    cosNum = 0;

    qDebug() << breakFlag << endl;

    query.exec("select * from clothes where type = 2 and season ='"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
               + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
    while(query.next())
    {
        if(cosNum++ == breakFlag)
        {
            qDebug() << query.value(1).toString();
            ui->label_11->setText(query.value(1).toString());
            ui->label_3->setScaledContents(true);
            ui->label_3->setPixmap(query.value(11).toString());
            break;
        }
    }
    //鞋袜
    query.exec("select * from clothes where type = 4 and season ='"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
               + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
    while(query.next())
        shoeNum++;
    qsrand(QTime::currentTime().toString("mhs").toInt());
    breakFlag = qrand() % shoeNum;
    shoeNum = 0;

    query.exec("select * from clothes where type = 4 and season ='"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
               + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
    while(query.next())
    {
        if(shoeNum++ == breakFlag)
        {
            ui->label_12->setText(query.value(1).toString());
            ui->label_4->setScaledContents(true);
            ui->label_4->setPixmap(query.value(11).toString());
            break;
        }
    }
}

void randomDialog::on_pushButton_2_clicked()
{
    //退出
    this->close();
}
