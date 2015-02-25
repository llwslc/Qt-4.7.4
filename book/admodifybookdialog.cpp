#include "admodifybookdialog.h"
#include "ui_admodifybookdialog.h"

adModifyBookDialog::adModifyBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adModifyBookDialog)
{
    ui->setupUi(this);    

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

adModifyBookDialog::~adModifyBookDialog()
{
    delete ui;
}

void adModifyBookDialog::showEvent(QShowEvent *)
{
    //显示窗体
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

void adModifyBookDialog::on_pushButton_clicked()
{
    //搜索
    QSqlQuery query;

    query.exec("select * from books where bookcode = '" + ui->lineEdit_6->text().trimmed() + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_2->setText(query.value(2).toString());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->lineEdit_4->setText(query.value(4).toString());
        ui->lineEdit_5->setText(query.value(5).toString());
        ui->dateEdit->setDate(QDate::fromString(query.value(6).toString(), "yyyy.MM.dd"));

        return;
    }

    QMessageBox::information(NULL, "Warring", "图书编号未找到!");
}

void adModifyBookDialog::on_pushButton_2_clicked()
{
    //修改
    QSqlQuery query;
    QString idNum, bookStatus;
    query.exec("select booksid,status from books bookcode = '" + ui->lineEdit_6->text().trimmed() + "'");
    while(query.next())
    {
        idNum = query.value(0).toString();
        bookStatus = query.value(1).toString();
    }

    query.exec("delete from books where bookcode = '" + ui->lineEdit_6->text().trimmed() + "'");

    query.exec("insert into books values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->lineEdit_4->text().trimmed() + "', '"
               + ui->lineEdit_5->text().trimmed() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "', '"
               + bookStatus + "')");

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    QMessageBox::information(NULL, "success", "修改成功!");

    emit modifyBook();
}
