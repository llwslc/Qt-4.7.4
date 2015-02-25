#include "maindialog.h"
#include "ui_maindialog.h"

mainDialog::mainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainDialog)
{
    ui->setupUi(this);

    //连接各种信号和槽
    connect(&checkinw.inroomw, SIGNAL(inRoom()), &roomw, SLOT(updateRoom()));       //入住信号,更新room状态
    connect(&roomw, SIGNAL(modifyRoom()), &checkinw.inroomw, SLOT(initDialog()));   //更新room信号,修改相应选项框显示

    connect(&checkinw.outroomw, SIGNAL(outRoom()), &roomw, SLOT(updateRoom()));
    connect(&roomw, SIGNAL(modifyRoom()), &checkinw.outroomw, SLOT(initDialog()));

    connect(&checkinw.bookroomw, SIGNAL(bookRoom()), &roomw, SLOT(updateRoom()));
    connect(&roomw, SIGNAL(modifyRoom()), &checkinw.bookroomw, SLOT(initDialog()));

    connect(&checkinw.inroomw, SIGNAL(inRoom()), &checkinw, SLOT(initDialog()));
    connect(&checkinw.inroomw, SIGNAL(inRoom()), &checkinw.outroomw, SLOT(initDialog()));
    connect(&checkinw.inroomw, SIGNAL(inRoom()), &checkinw.bookroomw, SLOT(initDialog()));

    connect(&checkinw.outroomw, SIGNAL(outRoom()), &checkinw.inroomw, SLOT(initDialog()));
    connect(&checkinw.outroomw, SIGNAL(outRoom()), &checkinw.bookroomw, SLOT(initDialog()));

    connect(&checkinw.bookroomw, SIGNAL(bookRoom()), &checkinw.inroomw, SLOT(initDialog()));
    connect(&checkinw.bookroomw, SIGNAL(bookRoom()), &checkinw.outroomw, SLOT(initDialog()));

    connect(&checkinw.inroomw, SIGNAL(inRoom()), &incomew, SLOT(initDialog()));

    connect(&checkinw.inroomw, SIGNAL(inRoom()), &searchw.bookw, SLOT(initDialog()));
    connect(&checkinw.bookroomw, SIGNAL(bookRoom()), &searchw.bookw, SLOT(initDialog()));

    connect(&checkinw.inroomw, SIGNAL(inRoom()), &searchw.inw, SLOT(initDialog()));
    connect(&checkinw.outroomw, SIGNAL(outRoom()), &searchw.inw, SLOT(initDialog()));

    connect(&checkinw.inroomw, SIGNAL(inRoom()), &searchw.callw, SLOT(initDialog()));
    connect(&checkinw.outroomw, SIGNAL(outRoom()), &searchw.callw, SLOT(initDialog()));
}

mainDialog::~mainDialog()
{
    delete ui;
}

void mainDialog::on_pushButton_clicked()
{
    //住宿管理
    checkinw.show();
}

void mainDialog::on_pushButton_2_clicked()
{
    //客房管理
    roomw.show();
}

void mainDialog::on_pushButton_3_clicked()
{
    //挂账管理
    incomew.show();
}

void mainDialog::on_pushButton_4_clicked()
{
    //查询统计
    searchw.show();
}
