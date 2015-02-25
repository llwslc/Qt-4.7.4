#include "libroomdialog.h"
#include "ui_libroomdialog.h"

libroomDialog::libroomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::libroomDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_4_clicked();

    ui->lineEdit->clear();
}

libroomDialog::~libroomDialog()
{
    delete ui;
}

void libroomDialog::showEvent(QShowEvent *)
{
    on_pushButton_4_clicked();

    ui->lineEdit->clear();
}

void libroomDialog::on_pushButton_3_clicked()
{
    //查询实验室
    currentTableModel->setFilter("name like '%" + ui->lineEdit->text().trimmed() + "%'");
    currentTableModel->select();
}

void libroomDialog::on_pushButton_clicked()
{
    //添加实验室
    QSqlQuery query;
    int idNum = 0;

    query.exec("select libroomid from libroom");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into libroom values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "')");

    ui->lineEdit->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");

    emit modifyLib();
}

void libroomDialog::on_pushButton_2_clicked()
{
    //删除实验室
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();

    QMessageBox::information(NULL, "success", "delete success!");

    emit modifyLib();
}

void libroomDialog::on_pushButton_4_clicked()
{
    //全部实验室
    currentTableModel->setTable("libroom");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
}

void libroomDialog::on_tableView_clicked(const QModelIndex &index)
{
    //单击列表
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from libroom where libroomid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
    }
}
