#include "logdialog.h"
#include "ui_logdialog.h"
#include"servedialog.h"
#include"admindialog.h"
#include<QDebug>
#include<QMessageBox.h>
#include<QSqlQuery>

logDialog::logDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logDialog)
{
    ui->setupUi(this);
    ui->rbadmin->setChecked(true);
    QPalette   palette;
    QPixmap pixmap("resource/2.jpg");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
}

logDialog::~logDialog()
{
    delete ui;
}

void logDialog::on_pbcancel_clicked()
{
    close();
}

void logDialog::on_pblogin_clicked()
{
    //根据用户名、密码、身份，与数据库中信息比较

    this->close();

        serveDialog  sd;
        sd.exec();


    //关闭登录窗口
}
