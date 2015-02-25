#include "userdialog.h"
#include "ui_userdialog.h"

userDialog::userDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userDialog)
{
    ui->setupUi(this);

    msgTimer = new QTimer(this);
    connect(msgTimer, SIGNAL(timeout()), this, SLOT(msgTimeOut()));
}

userDialog::~userDialog()
{
    delete ui;
}

void userDialog::showEvent(QShowEvent *)
{
    //显示窗体
    msgTimer->start(1*1000);

    chatw.setNickName();

    chatw.sendMessage("student:" + loginName);

    //chatw.show();
}

void userDialog::closeEvent(QCloseEvent *)
{
    //退出
    qDebug("leave!");
    int i = 100;
    while(i--)
        chatw.sendMessage("leave:" + loginName);
}

void userDialog::setStuCode(QString tmp)
{
    stuCode = tmp;
    usInfow.setStuCode(tmp);
    usBorroww.setStuCode(tmp);
}

void userDialog::on_pushButton_9_clicked()
{
    //个人信息
    usInfow.show();
}

void userDialog::on_pushButton_11_clicked()
{
    //借阅信息
    usBorroww.show();
}

void userDialog::on_pushButton_10_clicked()
{
    //图书信息查阅
    bookSearchw.show();
}

void userDialog::msgTimeOut()
{
    //获取系统消息
    QSqlQuery msgQuery, delQuery;
    msgQuery.exec("select * from message where stucode = '" + stuCode + "'");
    while(msgQuery.next())
    {
        QMessageBox::information(NULL, "管理员来信", "尊敬的<font color='red'> " + stuCode + " </font>用户:<br><br>您借阅的图书<font color='red'> " + msgQuery.value(1).toString() + " </font>已到期!<br><br>管理员提示您尽快还书!");
        delQuery.exec("delete from message where messageid = '" + msgQuery.value(0).toString() + "'");
    }

    chatw.sendMessage("student:" + loginName);
}

void userDialog::on_pushButton_12_clicked()
{
    //退出登录
    this->close();

    msgTimer->stop();

    emit loginOut();
}
