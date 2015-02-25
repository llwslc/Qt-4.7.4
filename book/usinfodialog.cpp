#include "usinfodialog.h"
#include "ui_usinfodialog.h"

usInfoDialog::usInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::usInfoDialog)
{
    ui->setupUi(this);
}

usInfoDialog::~usInfoDialog()
{
    delete ui;
}

void usInfoDialog::showEvent(QShowEvent *)
{
    //显示窗口
    QSqlQuery query;
    query.exec("select * from students where stucode = '" + stuCode + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->lineEdit_4->setText(query.value(4).toString());
        ui->comboBox->setCurrentIndex(query.value(5).toInt());
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap(query.value(6).toString()));
    }
}

void usInfoDialog::setStuCode(QString tmp)
{
    stuCode = tmp;
}

void usInfoDialog::on_pushButton_clicked()
{
    //修改联系方式
    QSqlQuery query;

    query.exec("select phone from students where stucode <> '" + stuCode + "'");
    while(query.next())
    {
        if(query.value(0).toString() == ui->lineEdit_4->text().trimmed())
        {
            QMessageBox::information(NULL, "Warring", "添加失败!手机号码重复.");
            return;
        }
    }

    query.exec("update students set phone = '" + ui->lineEdit_4->text().trimmed() + "' where stucode = '" + stuCode + "'");

    QMessageBox::warning(this,tr("Success"),tr("联系方式修改成功!"), QMessageBox::Yes);
}

void usInfoDialog::on_pushButton_2_clicked()
{
    //修改登录密码
    QString tPwd1;
    QString tPwd2;
    QString sql;
    QSqlQuery query;

    tPwd1 = ui->lineEdit_2->text().trimmed();
    tPwd2 = ui->lineEdit_5->text().trimmed();

    if (tPwd1 == tPwd2)
    {
        sql = "update students set passwd = '" + tPwd1 + "' where stucode = '" + stuCode + "'";
        query.exec(sql);
        QMessageBox::warning(this,tr("Success"),tr("密码修改成功!"), QMessageBox::Yes);

        ui->lineEdit_2->clear();    //清空新密码输入框
        ui->lineEdit_5->clear();    //清空二次输入密码输入框
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("两次密码不一致!"), QMessageBox::Yes);

        ui->lineEdit_2->clear();    //清空新密码输入框
        ui->lineEdit_5->clear();    //清空二次输入密码输入框
    }
}
