#include "messagewindow.h"
#include "ui_messagewindow.h"

messageWindow::messageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::messageWindow)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("message");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label_5->setText(username);
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->textEdit->clear();
}

messageWindow::~messageWindow()
{
    delete ui;
}

void messageWindow::on_pushButton_clicked()
{
    //我要留言
    ui->label_5->setText(username);
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->textEdit->clear();
}

void messageWindow::on_pushButton_2_clicked()
{
    //提交
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int idNum = 0;
    QSqlQuery query;
    query.exec("select messageId from message");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), idNum);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), username);
    currentTableModel->setData(currentTableModel->index(rowNum, 2), ui->lineEdit->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 3), ui->comboBox->currentIndex());
    currentTableModel->setData(currentTableModel->index(rowNum, 4), ui->textEdit->toPlainText());

    currentTableModel->submitAll();


    ui->label_5->setText(username);
    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->textEdit->clear();
}

void messageWindow::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    ui->label_5->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->lineEdit->setText(currentTableModel->index(curRow, 2).data().toString());
    ui->comboBox->setCurrentIndex(currentTableModel->index(curRow, 3).data().toInt());
    ui->textEdit->setPlainText(currentTableModel->index(curRow, 4).data().toString());
}
