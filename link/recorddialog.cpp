#include "recorddialog.h"
#include "ui_recorddialog.h"

recordDialog::recordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recordDialog)
{
    ui->setupUi(this);
}

recordDialog::~recordDialog()
{
    delete ui;
}

void recordDialog::showEvent(QShowEvent *event)
{
    ui->label_2->setText(QString::number(gameTime.elapsed()/1000, 10));
    ui->lineEdit->clear();
}

void recordDialog::on_pushButton_clicked()
{
    //确定
    QString nameStr = ui->lineEdit->text().trimmed();
    if(nameStr == "")
    {
        nameStr = "无名";
    }
    QSqlQuery query;
    int idNum = 0;
    query.exec("select historyListid from historyList");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;
    query.exec("insert into historyList values ('" + QString::number(idNum, 10) + "', '"
               + nameStr + "', '"
               + ui->label_2->text() + "', '"
               + QString::number(gameRole, 10) + "')");

    this->close();
}
