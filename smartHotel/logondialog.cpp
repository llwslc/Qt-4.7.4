#include "logondialog.h"
#include "ui_logondialog.h"

logonDialog::logonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logonDialog)
{
    ui->setupUi(this);

    //定义一个结构体，用来存放串口各个参数
    struct PortSettings myComSetting = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 500};
    //定义串口对象，并传递参数，在构造函数里对其进行初始化
    myCom = new Win_QextSerialPort("com1", myComSetting, QextSerialBase::EventDriven);
    //以可读写方式打开串口
    myCom->open(QIODevice::ReadWrite);
    //信号和槽函数关联，当串口缓冲区有数据时，进行读串口操作
    connect(myCom, SIGNAL(readyRead()), this, SLOT(readMyCom()));
    //写串口操作
    //myCom->write("99999");
}

logonDialog::~logonDialog()
{
    delete ui;
}


void logonDialog::on_loginBut_clicked()
{
    QSqlQuery query;
    QString sql;

    if (ui->adminRadio->isChecked() == true)
    {
        sql = "select * from users where name = '" + ui->nameEdit->text().trimmed()
                + "' and passwd = '"+ ui->pwdEdit->text() + "' and role = 0";
        query.exec(sql);

        if (query.next())
        {
            loginName = ui->nameEdit->text().trimmed();
            this->close();
            adminw.show();

            ui->nameEdit->clear();     //清空用户名输入框
            ui->pwdEdit->clear();      //清空密码输入框
            ui->nameEdit->setFocus();  //将光标转到用户名输入框
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

            ui->nameEdit->clear();     //清空用户名输入框
            ui->pwdEdit->clear();      //清空密码输入框
            ui->nameEdit->setFocus();  //将光标转到用户名输入框

        }
    }
    if (ui->userRadio->isChecked() == true)
    {
        sql = "select * from users where name = '" + ui->nameEdit->text().trimmed()
                + "' and passwd = '"+ ui->pwdEdit->text() + "' and role = 1";
        query.exec(sql);

        if (query.next())
        {
            loginName = ui->nameEdit->text().trimmed();
            this->close();
            userw = new userRoomDialog;
            userw->show();

            ui->nameEdit->clear();     //清空用户名输入框
            ui->pwdEdit->clear();      //清空密码输入框
            ui->nameEdit->setFocus();  //将光标转到用户名输入框
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);

            ui->nameEdit->clear();     //清空用户名输入框
            ui->pwdEdit->clear();      //清空密码输入框
            ui->nameEdit->setFocus();  //将光标转到用户名输入框
        }
    }
}

void logonDialog::on_cancelBut_clicked()
{
    close();
}

void logonDialog::readMyCom()
{
    //读取串口数据
    //读取串口缓冲区的所有数据给临时变量temp
    QByteArray temp = myCom->readAll();
    QString logonString(temp);

    //logon:用户名,密码,权限
    //logon:us::1
    if(logonString == "")
    {
        return;
    }

    QStringList logonStringList = logonString.split(":");
    if(logonStringList.at(0) != "logon")
    {
        return;
    }

    QSqlQuery query;
    QString sql;

    sql = "select * from users where name = '" + logonStringList.at(1)
            + "' and passwd = '"+ logonStringList.at(2) + "' and role = '" + logonStringList.at(3) + "'";
    query.exec(sql);

    if (query.next())
    {
        loginName = logonStringList.at(1);
        this->close();
        myCom->close();
        userw = new userRoomDialog;
        userw->show();

        ui->nameEdit->clear();     //清空用户名输入框
        ui->pwdEdit->clear();      //清空密码输入框
        ui->nameEdit->setFocus();  //将光标转到用户名输入框
    }
}
