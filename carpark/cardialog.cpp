#include "cardialog.h"
#include "ui_cardialog.h"

carDialog::carDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::carDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("comego");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    on_checkBox_clicked();

    ui->lineEdit->clear();
    ui->checkBox->setChecked(false);
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

carDialog::~carDialog()
{
    delete ui;
}

void carDialog::showEvent(QShowEvent *)
{
    on_checkBox_clicked();

    ui->lineEdit->clear();
    ui->checkBox->setChecked(false);
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

void carDialog::on_pushButton_clicked()
{
    //入库
    QSqlQuery query;
    int idNum = 0;
    int rowNum = currentTableModel->rowCount(); //获得表的行数

    query.exec("select comegoid from comego");
    while(query.next())
    {
        idNum = query.value(0).toInt() + 1;
    }

    if(ui->comboBox->currentIndex() != 0)
    {
        currentTableModel->setData(currentTableModel->index(rowNum, 1), ui->comboBox->currentText());
        query.exec("update park set status = 1 where parkid = '" + ui->comboBox->currentText() + "'");
    }
    else
    {
        return;
    }

    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), idNum);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), ui->lineEdit->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 2), ui->comboBox->currentText());
    currentTableModel->setData(currentTableModel->index(rowNum, 3), QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));

    ui->lineEdit->clear();
    ui->checkBox->setChecked(false);
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();

    currentTableModel->submitAll();
    on_checkBox_clicked();
}

void carDialog::on_pushButton_3_clicked()
{
    //出库
    QSqlQuery query;
    QString parkid;

    query.exec("update comego set go = '" + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss") + "', price = '"
               + ui->lineEdit_4->text().trimmed() + "'"
               + "where comegoid = '" + selectCarId + "'");

    query.exec("select park from comego where comegoid = '" + selectCarId + "'");
    while(query.next())
        parkid = query.value(0).toString();

    query.exec("update park set status = 0 where parkid = '" + parkid + "'");

    ui->lineEdit->clear();
    ui->checkBox->setChecked(false);
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();

    currentTableModel->select();
}

void carDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    if(currentTableModel->index(curRow, 4).data().toString().isEmpty())
    {
        selectCarId = currentTableModel->index(curRow, 0).data().toString();
        ui->lineEdit_3->setText(currentTableModel->index(curRow, 1).data().toString());
    }
    else
    {
        ui->lineEdit->clear();
        ui->checkBox->setChecked(false);
        ui->comboBox->setCurrentIndex(0);
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
    }
}

void carDialog::on_checkBox_clicked()
{
    //复选框点击
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox->addItem("");

    if(ui->checkBox->isChecked())
    {
        //预订
        query.exec("select parkid from park where status = 2");
        while(query.next())
            ui->comboBox->addItem(query.value(0).toString());
    }
    else
    {
        query.exec("select parkid from park where status = 0");
        while(query.next())
            ui->comboBox->addItem(query.value(0).toString());
    }
}
