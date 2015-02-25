#include "outroomdialog.h"
#include "ui_outroomdialog.h"

outroomDialog::outroomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::outroomDialog)
{
    ui->setupUi(this);

    initDialog();
}

outroomDialog::~outroomDialog()
{
    delete ui;
}

void outroomDialog::showEvent(QShowEvent *)
{
    initDialog();
}

void outroomDialog::on_pushButton_clicked()
{
    //退房
    QSqlQuery query;

    if(ui->comboBox->currentIndex() != 0)
    {
        query.exec("update room set status = 0 where roomid = '" + ui->comboBox->currentText() + "'");
    }
    else if(ui->comboBox_2->currentIndex() != 0)
    {
        query.exec("update room set status = 0 where roomid = '" + ui->comboBox_2->currentText() + "'");
    }
    else
    {
        QMessageBox::information(NULL, "fail", "room number is empty");
        return;
    }

    initDialog();

    emit outRoom();
}

void outroomDialog::initDialog()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox_2->clear();

    ui->comboBox->addItem("");
    ui->comboBox_2->addItem("");

    query.exec("select roomid from room where status = 2");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());

    query.exec("select roomid from room where status = 1");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}
