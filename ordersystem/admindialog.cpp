#include "admindialog.h"
#include "ui_admindialog.h"
#include<QDebug>

adminDialog::adminDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminDialog)
{
    ui->setupUi(this);
    QPalette   palette;
    QPixmap pixmap("resource/1.jpg");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
}

adminDialog::~adminDialog()
{
    delete ui;
}

void adminDialog::on_pbcp_released()
{
    cpgl cp;
    cp.exec();
}

void adminDialog::on_pbry_released()
{
    rygl ry;
    ry.exec();
}
