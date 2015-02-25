#include "checkindialog.h"
#include "ui_checkindialog.h"

checkinDialog::checkinDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::checkinDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_3_clicked();

    initComboBox();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
}

checkinDialog::~checkinDialog()
{
    delete ui;
}


void checkinDialog::showEvent(QShowEvent *)
{
    on_pushButton_3_clicked();

    initComboBox();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
}

void checkinDialog::on_pushButton_clicked()
{
    //入住
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int idNum = 0;
    QSqlQuery query;
    query.exec("select checkinid from checkin");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), idNum);
    if(ui->comboBox->currentIndex() != 0)
    {
        currentTableModel->setData(currentTableModel->index(rowNum, 1), ui->comboBox->currentText());
        query.exec("update room set status = 1 where roomid = '" + ui->comboBox->currentText() + "'");
    }
    else if(ui->comboBox_2->currentIndex() != 0)
    {
        currentTableModel->setData(currentTableModel->index(rowNum, 1), ui->comboBox_2->currentText());
        query.exec("update room set status = 1 where roomid = '" + ui->comboBox_2->currentText() + "'");
    }
    else
    {
        QMessageBox::information(NULL, "fail", "room number is empty");
        return;
    }
    currentTableModel->setData(currentTableModel->index(rowNum, 2), ui->lineEdit->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 3), ui->lineEdit_2->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 4), ui->dateEdit->date().toString("yyyy.MM.dd"));
    currentTableModel->setData(currentTableModel->index(rowNum, 5), ui->lineEdit_3->text());

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    currentTableModel->submitAll();
    initComboBox();
}

void checkinDialog::on_pushButton_2_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
}

void checkinDialog::on_pushButton_3_clicked()
{
    //刷新
    currentTableModel->setTable("checkin");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox->setEnabled(true);
    ui->comboBox_2->setEnabled(true);
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
}

void checkinDialog::on_pushButton_4_clicked()
{
    //营业额查询
    QDate preDate = ui->dateEdit_2->date();
    QDate nextDate = ui->dateEdit_3->date();
    QSqlQuery query;
    int price = 0;

    if(preDate > nextDate)
    {
        QMessageBox::warning(this,tr("Warning"),tr("preDate > nextDate!"),QMessageBox::Yes);
        ui->dateEdit_2->setDate(nextDate); //设置为后一个时间
    }

    currentTableModel->setFilter("date >= '" + preDate.toString("yyyy.MM.dd")
                                 + "' and date <= '" + nextDate.toString("yyyy.MM.dd") + "'");
    currentTableModel->select();

    query.exec("select price from checkin where date >= '" + preDate.toString("yyyy.MM.dd")
               + "' and date <= '" + nextDate.toString("yyyy.MM.dd") + "'");
    while(query.next())
        price += query.value(0).toInt();
    ui->label_11->setText("营业额统计 : " + QString::number(price, 10)+ "元");
}

void checkinDialog::initComboBox()
{
    //初始化列表
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();

    ui->comboBox->addItem("");
    ui->comboBox_2->addItem("");
    ui->comboBox_3->addItem("");

    query.exec("select roomid from room where status = 0");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());

    query.exec("select roomid from room where status = 1");
    while(query.next())
        ui->comboBox_3->addItem(query.value(0).toString());

    query.exec("select roomid from room where status = 2");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());
}

void checkinDialog::on_comboBox_currentIndexChanged(int index)
{
    //预订组合框
    if(ui->comboBox->currentIndex())
    {
        ui->comboBox_2->setEnabled(false);
    }
    else
    {
        ui->comboBox_2->setEnabled(true);
    }
}

void checkinDialog::on_comboBox_2_currentIndexChanged(int index)
{
    //未使用组合框
    if(ui->comboBox_2->currentIndex())
    {
        ui->comboBox->setEnabled(false);
    }
    else
    {
        ui->comboBox->setEnabled(true);
    }
}

void checkinDialog::on_pushButton_5_clicked()
{
    //退房
    QSqlQuery query;
    if(ui->comboBox_3->currentIndex() != 0)
        query.exec("update room set status = 0 where roomid = '" + ui->comboBox_3->currentText() + "'");

    initComboBox();
}
