#include "inroomdialog.h"
#include "ui_inroomdialog.h"

inroomDialog::inroomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inroomDialog)
{
    ui->setupUi(this);

    initDialog();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

inroomDialog::~inroomDialog()
{
    delete ui;
}

void inroomDialog::showEvent(QShowEvent *)
{
    initDialog();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

void inroomDialog::on_pushButton_clicked()
{
    //入住
    int idNum = 0;
    QString roomNum;
    QSqlQuery query;
    query.exec("select checkinid from checkin");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    if(ui->comboBox->currentIndex() != 0)
    {
        roomNum = ui->comboBox->currentText();
        query.exec("update room set status = 1 where roomid = '" + ui->comboBox->currentText() + "'");
    }
    else if(ui->comboBox_2->currentIndex() != 0)
    {
        roomNum = ui->comboBox_2->currentText();
        query.exec("update room set status = 1 where roomid = '" + ui->comboBox_2->currentText() + "'");
    }
    else
    {
        QMessageBox::information(NULL, "fail", "room number is empty");
        return;
    }

    query.exec("insert into checkin values('" + QString::number(idNum, 10) + "', '"
               + roomNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "', '"
               + ui->lineEdit_3->text().trimmed() + "')");

    initDialog();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    emit inRoom();
}

void inroomDialog::initDialog()
{
    //初始化列表
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox_2->clear();

    ui->comboBox->addItem("");
    ui->comboBox_2->addItem("");

    query.exec("select roomid from room where status = 2");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());

    query.exec("select roomid from room where status = 0");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}
