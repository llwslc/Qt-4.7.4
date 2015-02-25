#include "callsearchdialog.h"
#include "ui_callsearchdialog.h"

callSearchDialog::callSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::callSearchDialog)
{
    ui->setupUi(this);
}

callSearchDialog::~callSearchDialog()
{
    delete ui;
}

void callSearchDialog::showEvent(QShowEvent *)
{
    initDialog();
}

void callSearchDialog::initDialog()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox->clear();

    ui->comboBox->addItem("");

    query.exec("select roomnum from checkin where date = '" + QDate::currentDate().toString("yyyy.MM.dd") + "'");
    while(query.next())
    {
        if(ui->comboBox->findText(query.value(0).toString()) == -1)
            ui->comboBox->addItem(query.value(0).toString());
    }
}
