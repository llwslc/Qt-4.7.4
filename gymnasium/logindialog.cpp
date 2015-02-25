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

void loginDialog::on_commandLinkButton_clicked()
{
    QSqlQuery query;
    QString sql;
    int punchid = 0;

    if (ui->checkBox->isChecked() == true)
    {
        sql = "select * from person where name = '" + ui->lineEdit->text().trimmed()
                + "' and passwd = '"+ ui->lineEdit_2->text() + "' and role = 0";
        query.exec(sql);

        if (query.next())
        {
            this->close();
            adminw.show();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

            ui->lineEdit->clear();      //清空用户名输入框
            ui->lineEdit_2->clear();       //清空密码输入框
            ui->lineEdit->setFocus();   //将光标转到用户名输入框

        }
    }
    if (ui->checkBox_2->isChecked() == true)
    {
        sql = "select * from person where name = '" + ui->lineEdit->text().trimmed()
                + "' and passwd = '"+ ui->lineEdit_2->text() + "' and role = 1";
        query.exec(sql);

        if (query.next())
        {
            sql = "select punchid from punch";
            query.exec(sql);
            while(query.next())
            {
                punchid = query.value(0).toInt() + 1;
            }
            waiterw.name = ui->lineEdit->text().trimmed();
            waiterw.logtime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss");
            sql = "insert into punch (punchid, name, logtime, outtime) values ('" + QString::number(punchid, 10) + "', '" + waiterw.name + "', '" + waiterw.logtime + "', 'null')";
            query.exec(sql);

            this->close();
            waiterw.show();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

            ui->lineEdit->clear();      //清空用户名输入框
            ui->lineEdit_2->clear();       //清空密码输入框
            ui->lineEdit->setFocus();   //将光标转到用户名输入框
        }
    }
}

void loginDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/8.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
