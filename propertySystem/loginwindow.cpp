#include "loginwindow.h"
#include "ui_loginwindow.h"

loginWindow::loginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_pushButton_clicked()
{
    //用户登录
    QString sql;
    QSqlQuery query;
    sql = "select * from ownerinfo where name = '" + ui->lineEdit->text().trimmed()
            + "' and pwd = '"+ ui->lineEdit_2->text() + "'";
    query.exec(sql);

    if (query.next())
    {
        username = ui->lineEdit->text().trimmed();
        this->close();
        userw.show();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

        ui->lineEdit->clear();      //清空用户名输入框
        ui->lineEdit_2->clear();       //清空密码输入框
        ui->lineEdit->setFocus();   //将光标转到用户名输入框
    }
}

void loginWindow::on_pushButton_2_clicked()
{
    //用户取消
    close();
}

void loginWindow::on_pushButton_3_clicked()
{
    //管理员登录
    QString sql;
    QSqlQuery query;
    sql = "select * from person where name = '" + ui->lineEdit_3->text().trimmed()
            + "' and passwd = '"+ ui->lineEdit_4->text() + "' and role = 0";
    query.exec(sql);

    if (query.next())
    {
        this->close();
        adminw.show();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

        ui->lineEdit_3->clear();      //清空用户名输入框
        ui->lineEdit_4->clear();       //清空密码输入框
        ui->lineEdit_3->setFocus();   //将光标转到用户名输入框
    }
}

void loginWindow::on_pushButton_4_clicked()
{
    //管理员取消
    close();
}

void loginWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/1.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
