#include "messagedialog.h"
#include "ui_messagedialog.h"

messageDialog::messageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::messageDialog)
{
    ui->setupUi(this);
}

messageDialog::~messageDialog()
{
    delete ui;
}

void messageDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/frame.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
