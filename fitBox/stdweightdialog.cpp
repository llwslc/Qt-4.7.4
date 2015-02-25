#include "stdweightdialog.h"
#include "ui_stdweightdialog.h"

stdweightDialog::stdweightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stdweightDialog)
{
    ui->setupUi(this);
}

stdweightDialog::~stdweightDialog()
{
    delete ui;
}
void stdweightDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bj51.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void stdweightDialog::on_pushButton_clicked()
{
    //计算
    double age = ui->lineEdit->text().trimmed().toDouble();
    double height = ui->lineEdit_2->text().trimmed().toDouble();
    int gender = ui->radioButton->isChecked();
    double result = 0;
    double ageVariable = 0; //年龄变量
    double genderVariable = 0; //性别变量

    if(gender==true)
    {
        //选择男
        qDebug() << "选择男" << endl;
        genderVariable = 1;
    }
    else
    {
        genderVariable = -1;
    }

    if(age == 0)
    {
        QMessageBox::information(NULL, tr("age"), tr("age is zero!"));
    }
    else
    {
        if((age<=19)||(age>=24))
        {
            //标准年龄
            ageVariable = 0;
        }
        else
        {
            ageVariable = -2;
        }

        if(height == 0)
        {
            QMessageBox::information(NULL, tr("height"), tr("height is zero!"));
        }
        else
        {
            result = (height-70)*0.6 + ageVariable + genderVariable;
            ui->label_14->setText("你的标准体重 : " + QString::number(result, 'g') + " KG");
        }
    }
}
