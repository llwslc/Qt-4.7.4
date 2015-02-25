#include "weightdialog.h"
#include "ui_weightdialog.h"

weightDialog::weightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::weightDialog)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
}

weightDialog::~weightDialog()
{
    delete ui;
}

void weightDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bj51.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void weightDialog::on_pushButton_clicked()
{
    //Ìí¼Ó
    int idNum = 0;
    QString sql;
    QSqlQuery query;

    sql = "select weightrecordid from weightrecord";
    query.exec(sql);
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    if(ui->lineEdit_2->text().trimmed().toInt() > 0)
    {
            sql = "insert into weightrecord values ('"
                    + QString::number(idNum, 10) + "', '"
                    + ui->lineEdit_2->text().trimmed() + "', '"
                    + ui->dateEdit->date().toString("dd.MM.yyyy") + "')";
            query.exec(sql);

            QMessageBox::information(NULL, tr("Success"), tr("weight add success!"));
    }
    else
    {
        QMessageBox::information(NULL, tr("Warring"), tr("lineEdit is zero!"));
    }
}
