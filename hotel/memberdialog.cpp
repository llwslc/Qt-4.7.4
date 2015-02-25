#include "memberdialog.h"
#include "ui_memberdialog.h"

memberDialog::memberDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::memberDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("member");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_4->clear();
}

memberDialog::~memberDialog()
{
    delete ui;
}

void memberDialog::on_pushButton_clicked()
{
    //姓名查询
    currentTableModel->setFilter("name like '%" + ui->lineEdit->text().trimmed() + "%'");
    currentTableModel->select();
}

void memberDialog::on_pushButton_2_clicked()
{
    //身份证号查询
    currentTableModel->setFilter("idnum = '" + ui->lineEdit_2->text().trimmed() + "'");
    currentTableModel->select();
}

void memberDialog::on_pushButton_3_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select memberid from member");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    if(ui->lineEdit->text().isEmpty()
            || ui->lineEdit_2->text().isEmpty()
            || ui->lineEdit_3->text().isEmpty()
            || ui->lineEdit_4->text().isEmpty()
            )
    {
        QMessageBox::information(NULL, "fail", "something is empty!");
        return;
    }

    query.exec("insert into member values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text() + "', '"
               + ui->lineEdit_2->text() + "', '"
               + ui->lineEdit_3->text() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "', '"
               + ui->lineEdit_4->text() + "')");

    currentTableModel->setTable("member");
    currentTableModel->select();
    QMessageBox::information(NULL, "success", "member add success!");

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_4->clear();
}

void memberDialog::on_pushButton_4_clicked()
{
    //刷新
    currentTableModel->setTable("member");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_4->clear();
}

void memberDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    ui->lineEdit->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->lineEdit_2->setText(currentTableModel->index(curRow, 2).data().toString());
    ui->lineEdit_3->setText(currentTableModel->index(curRow, 3).data().toString());
    ui->dateEdit->setDate(QDate::fromString(currentTableModel->index(curRow, 4).data().toString(), "yyyy.MM.dd"));
    ui->lineEdit_4->setText(currentTableModel->index(curRow, 5).data().toString());
}
