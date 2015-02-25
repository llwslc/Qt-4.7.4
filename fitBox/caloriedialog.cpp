#include "caloriedialog.h"
#include "ui_caloriedialog.h"

calorieDialog::calorieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::calorieDialog)
{
    ui->setupUi(this);
}

calorieDialog::~calorieDialog()
{
    delete ui;
}

void calorieDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bj51.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}


void calorieDialog::on_pushButton_clicked()
{
    //¼ÆËã
    double weight = ui->lineEdit->text().trimmed().toDouble();
    double result = 0;

    if(weight == 0)
    {
        QMessageBox::information(NULL, tr("weight"), tr("weight is zero!"));
    }
    else
    {
        result = weight * 7700;
        ui->label_4->setText("¿¨Â·Àï : " + QString::number(result, 'g') + " Ç§¿¨");
    }
}
