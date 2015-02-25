#include "bookroomdialog.h"
#include "ui_bookroomdialog.h"

bookroomDialog::bookroomDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookroomDialog)
{
    ui->setupUi(this);

    initDialog();
}

bookroomDialog::~bookroomDialog()
{
    delete ui;
}

void bookroomDialog::showEvent(QShowEvent *)
{
    initDialog();
}

void bookroomDialog::on_pushButton_clicked()
{
    //预订
    QSqlQuery query;

    if(ui->comboBox->currentIndex() != 0)
    {
        query.exec("update room set status = 2 where roomid = '" + ui->comboBox->currentText() + "'");
    }
    else
    {
        QMessageBox::information(NULL, "fail", "room number is empty");
        return;
    }

    initDialog();

    emit bookRoom();
}

void bookroomDialog::initDialog()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox->clear();

    ui->comboBox->addItem("");

    query.exec("select roomid from room where status = 0");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());
}
