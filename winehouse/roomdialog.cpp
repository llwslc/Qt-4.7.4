#include "roomdialog.h"
#include "ui_roomdialog.h"

roomDialog::roomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::roomDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlRelationalTableModel(this);
    currentView = ui->tableView;

    on_pushButton_4_clicked();
}

roomDialog::~roomDialog()
{
    delete ui;
}

void roomDialog::showEvent(QShowEvent *)
{
    on_pushButton_4_clicked();
}

void roomDialog::on_pushButton_clicked()
{
    //添加房间
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), 0);

    currentTableModel->submitAll();

    emit modifyRoom();
}

void roomDialog::on_pushButton_2_clicked()
{
    //删除房间
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    emit modifyRoom();
}

void roomDialog::on_pushButton_3_clicked()
{
    //提交修改
    currentTableModel->submitAll();

    emit modifyRoom();
}

void roomDialog::on_pushButton_4_clicked()
{
    //刷新房间
    currentTableModel->setTable("room");
    currentTableModel->setRelation(1, QSqlRelation("roomstatus", "roomstatusid", "status"));
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setItemDelegate(new QSqlRelationalDelegate(currentView));
}

void roomDialog::updateRoom()
{
    //刷新房间信号
    on_pushButton_4_clicked();
}
