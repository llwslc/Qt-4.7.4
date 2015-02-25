#include "booksearchdialog.h"
#include "ui_booksearchdialog.h"

bookSearchDialog::bookSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookSearchDialog)
{
    ui->setupUi(this);
    initDialog();
}

bookSearchDialog::~bookSearchDialog()
{
    delete ui;
}

void bookSearchDialog::showEvent(QShowEvent *)
{
    initDialog();
}

void bookSearchDialog::initDialog()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox->clear();

    ui->comboBox->addItem("");

    query.exec("select roomid from room where status = 2");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());
}
