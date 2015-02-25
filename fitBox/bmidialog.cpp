#include "bmidialog.h"
#include "ui_bmidialog.h"

bmiDialog::bmiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bmiDialog)
{
    ui->setupUi(this);
}

bmiDialog::~bmiDialog()
{
    delete ui;
}

void bmiDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bj51.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void bmiDialog::on_pushButton_clicked()
{
    //¼ÆËã
    double height = ui->lineEdit->text().trimmed().toDouble();
    double weight = ui->lineEdit_2->text().trimmed().toDouble();
    double result = 0;

    if(height == 0)
    {
        QMessageBox::information(NULL, tr("height"), tr("height is zero!"));
    }
    else
    {
        if(weight == 0)
        {
            QMessageBox::information(NULL, tr("weight"), tr("weight is zero!"));
        }
        else
        {
            result = weight/((height/100)*(height/100));
            ui->label_14->setText("ÄãµÄBMI : " + QString::number(result, 'g'));
        }
    }
}
