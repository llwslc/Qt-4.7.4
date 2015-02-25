#include "libroomtimedialog.h"
#include "ui_libroomtimedialog.h"

libroomTimeDialog::libroomTimeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::libroomTimeDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("libroomtime");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    initComboBox();

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
}

libroomTimeDialog::~libroomTimeDialog()
{
    delete ui;
}

void libroomTimeDialog::on_pushButton_clicked()
{
    //预约
    QSqlQuery query;
    int idNum = 0;

    query.exec("select libroomtimeid from libroomtime");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into libroomtime values('" + QString::number(idNum, 10) + "', '"
               + ui->comboBox->currentText() + "', '"
               + ui->dateTimeEdit->dateTime().toString("yyyy.MM.dd hh:mm:ss") + "', '"
               + ui->dateTimeEdit_2->dateTime().toString("yyyy.MM.dd hh:mm:ss") + "')");

    initComboBox();

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void libroomTimeDialog::on_pushButton_2_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    initComboBox();

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    QMessageBox::information(NULL, "success", "delete success!");
}

void libroomTimeDialog::showEvent(QShowEvent *)
{
    initComboBox();

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
}

void libroomTimeDialog::initComboBox()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox->addItem("");

    query.exec("select name from libroom");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());
}


void libroomTimeDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表点击
    int curRow = currentView->currentIndex().row();
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from libroomtime where libroomtimeid = '" + idNum + "'");
    while(query.next())
    {
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(query.value(1).toString()));
        ui->dateTimeEdit->setDateTime(QDateTime::fromString(query.value(2).toString(), "yyyy.MM.dd hh:mm:ss"));
        ui->dateTimeEdit_2->setDateTime(QDateTime::fromString(query.value(3).toString(), "yyyy.MM.dd hh:mm:ss"));
    }
}

void libroomTimeDialog::on_comboBox_currentIndexChanged(int index)
{
    //下拉框改变
    currentTableModel->setFilter("name like '%" + ui->comboBox->currentText() + "%'");
    currentTableModel->select();
}
