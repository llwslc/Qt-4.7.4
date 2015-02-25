#include "memberdialog.h"
#include "ui_memberdialog.h"

memberDialog::memberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::memberDialog)
{
    ui->setupUi(this);
}

memberDialog::~memberDialog()
{
    delete ui;
}

void memberDialog::showEvent(QShowEvent *)
{
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    initComboBox();
}

void memberDialog::on_pushButton_4_clicked()
{
    //查询
    QSqlQuery query;
    if(ui->lineEdit_5->text().trimmed().isEmpty())
    {
        return;
    }
    else
    {
        query.exec("select * from member where memberid = '" + ui->lineEdit_5->text().trimmed() + "'");
        while(query.next())
        {
            ui->lineEdit->setText(query.value(1).toString());
            ui->comboBox->setCurrentIndex(query.value(2).toInt());
            ui->lineEdit_2->setText(query.value(3).toString());
            ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(query.value(4).toString()));
            ui->lineEdit_3->setText(query.value(5).toString());
        }
    }
}

void memberDialog::on_pushButton_clicked()
{
    //添加会员
    QSqlQuery query;
    int idNum = 0;

    query.exec("select memberid from member");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into member values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->comboBox_2->currentText() + "', '"
               + ui->lineEdit_3->text().trimmed() + "')");

    QMessageBox::information(NULL, "add", "add success!");

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void memberDialog::on_pushButton_3_clicked()
{
    //充值
    QSqlQuery query;
    int curIntegral = 0;
    int idNum = 0;
    if(ui->lineEdit_5->text().trimmed().isEmpty())
    {
        return;
    }
    else
    {
        query.exec("select integral from member where memberid = '" + ui->lineEdit_5->text().trimmed() + "'");
        while(query.next())
        {
            curIntegral = query.value(5).toInt();
        }

        curIntegral += ui->lineEdit_4->text().toInt();

        query.exec("update member set integral = '" + QString::number(curIntegral, 10) + "' where memberid = '" + ui->lineEdit_5->text().trimmed() + "'");

        query.exec("select turnoverid from turnover");
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }

        idNum++;

        query.exec("insert into turnover values('" + QString::number(idNum, 10) + "', '"
                   + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss") + "', '"
                   + "会员 " + ui->lineEdit->text().trimmed() + " 充值" + "', '"
                   + ui->lineEdit_4->text().trimmed() + "')");
    }

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    emit addMoney();
}

void memberDialog::on_pushButton_2_clicked()
{
    //安排教练
    QSqlQuery query;
    if(ui->lineEdit_5->text().trimmed().isEmpty())
    {
        return;
    }
    else
    {
        query.exec("update member set assname = '" + ui->comboBox_2->currentText() + "' where memberid = '" + ui->lineEdit_5->text().trimmed() + "'");
    }

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void memberDialog::initComboBox()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("");

    query.exec("select name from assessor");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}

void memberDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/6.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
