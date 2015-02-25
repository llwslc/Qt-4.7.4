#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    ui->setupUi(this);
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_clicked()
{
    //µÇÂ¼
    QSqlQuery query;
    QString sql;

    sql = "select * from user where passwd = '"+ ui->lineEdit_2->text() + "'";
    query.exec(sql);

    if (query.next())
    {
        this->close();
        mainw.show();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("password error!"),QMessageBox::Yes);
        ui->lineEdit_2->clear();    //Çå¿ÕÃÜÂëÊäÈë¿ò
    }
}

void loginDialog::on_pushButton_3_clicked()
{
    //ÍË³ö
    close();
}
