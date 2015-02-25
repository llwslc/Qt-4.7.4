#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    colorDlg.show();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    //打开调色板
    colorDlg.show();
}

void Dialog::on_pushButton_2_clicked()
{
    //打开原版拾色器
    QColor color = QColorDialog::getColor(Qt::white, this);
    QString msg = QString("r: %1, g: %2, b: %3").arg(QString::number(color.red()), QString::number(color.green()), QString::number(color.blue()));
    QMessageBox::information(NULL, "Selected color", msg);
}
