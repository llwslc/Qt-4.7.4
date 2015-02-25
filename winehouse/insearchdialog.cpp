#include "insearchdialog.h"
#include "ui_insearchdialog.h"

inSearchDialog::inSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inSearchDialog)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
}

inSearchDialog::~inSearchDialog()
{
    delete ui;
}

void inSearchDialog::showEvent(QShowEvent *)
{
    initDialog();
}

void inSearchDialog::initDialog()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox->clear();

    ui->comboBox->addItem("");

    query.exec("select roomid from room where status = 1");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());
}

void inSearchDialog::on_comboBox_currentIndexChanged(int index)
{
    //下拉框变化
    QSqlQuery query;
    query.exec("select date from checkin where roomnum = '" + ui->comboBox->currentText() + "' and date >= '" + QDate::currentDate().toString("yyyy.MM.dd") + "'");
    while(query.next())
        ui->dateEdit->setDate(QDate::fromString(query.value(0).toString(), "yyyy.MM.dd"));
}
