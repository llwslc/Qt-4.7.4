#include "wardrobedialog.h"
#include "ui_wardrobedialog.h"

wardrobeDialog::wardrobeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wardrobeDialog)
{
    ui->setupUi(this);

    ui->comboBox_4->setCurrentIndex(0);
    ui->label_14->setText("共计 : 0 件");

    ui->label->clear();
    ui->comboBox_5->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();

    initDialog();
}

wardrobeDialog::~wardrobeDialog()
{
    delete ui;
}

void wardrobeDialog::showEvent(QShowEvent *)
{
    //显示窗口
    ui->comboBox_4->setCurrentIndex(0);
    ui->label_14->setText("共计 : 0 件");

    ui->label->clear();
    ui->comboBox_5->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();

    initDialog();
}

void wardrobeDialog::on_comboBox_4_currentIndexChanged(int index)
{
    //存放地选择
    QSqlQuery query;

    ui->comboBox_5->clear();

    query.exec("select distinct name from clothes where storeplace = '" + ui->comboBox_4->currentText() + "'");
    while(query.next())
        ui->comboBox_5->addItem(query.value(0).toString());

    ui->label->clear();
    ui->comboBox_5->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->textEdit->clear();
}

void wardrobeDialog::on_comboBox_5_currentIndexChanged(int index)
{
    //衣物选择
    QSqlQuery query;

    query.exec("select * from clothes where name = '" + ui->comboBox_5->currentText() + "'");
    while(query.next())
    {
        ui->comboBox->setCurrentIndex(query.value(2).toInt());
        ui->comboBox_2->setCurrentIndex(query.value(3).toInt());
        ui->comboBox_3->setCurrentIndex(query.value(4).toInt());
        ui->lineEdit_2->setText(query.value(5).toString());
        ui->lineEdit_3->setText(query.value(6).toString());
        ui->dateEdit->setDate(QDate::fromString(query.value(7).toString(), "yyyy.MM.dd"));
        ui->lineEdit_4->setText(query.value(8).toString());
        ui->lineEdit_5->setText(query.value(9).toString());
        ui->textEdit->setPlainText(query.value(10).toString());
        ui->label->setScaledContents(true);
        ui->label->setPixmap(query.value(11).toString());
    }
}

void wardrobeDialog::initDialog()
{
    //初始化
    QSqlQuery query;
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();

    query.exec("select distinct storeplace from clothes");
    while(query.next())
        ui->comboBox_4->addItem(query.value(0).toString());

    query.exec("select count(distinct name) from clothes where storeplace = '" + ui->comboBox_4->currentText() + "'");
    while(query.next())
        ui->label_14->setText("共计 : " + query.value(0).toString() + " 件");
}
