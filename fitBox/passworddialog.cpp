#include "passworddialog.h"
#include "ui_passworddialog.h"

passwordDialog::passwordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::passwordDialog)
{
    ui->setupUi(this);
}

passwordDialog::~passwordDialog()
{
    delete ui;
}
void passwordDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bj51.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void passwordDialog::on_pushButton_clicked()
{
    //ÐÞ¸ÄÃÜÂë
    QString sPwd;
    QString tPwd1;
    QString tPwd2;
    QString sql;
    QSqlQuery query;

    sPwd = ui->lineEdit->text().trimmed();
    tPwd1 = ui->lineEdit_2->text().trimmed();
    tPwd2 = ui->lineEdit_3->text().trimmed();

    sql = "select * from user where passwd = '"+ sPwd + "'";
    query.exec(sql);
    if (query.next())
    {
        if (tPwd1 == tPwd2)
        {
            sql = "update user set passwd = '" + tPwd1 + "' where userid = 1";
            query.exec(sql);
            QMessageBox::warning(this,tr("Success"),tr("successfully Modify!"), QMessageBox::Yes);

            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit->setFocus();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("Second password is not suit the first!"), QMessageBox::Yes);

            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit->setFocus();
        }
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("password error!"), QMessageBox::Yes);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit->setFocus();
    }
}

void passwordDialog::on_pushButton_2_clicked()
{
    //ÍË³ö
    close();
}
