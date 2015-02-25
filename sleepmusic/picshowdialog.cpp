#include "picshowdialog.h"
#include "ui_picshowdialog.h"

picShowDialog::picShowDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::picShowDialog)
{
    ui->setupUi(this);
    this->resize(QApplication::desktop()->screen()->width(), QApplication::desktop()->screen()->height());

    totalInt = 0;
    curInt = 0;

    QSqlQuery query;

    query.exec("select path from pic");
    while(query.next())
        totalInt++;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTimeOut()));
}

picShowDialog::~picShowDialog()
{
    delete ui;
}

void picShowDialog::showEvent(QShowEvent *)
{
    curInt = 1;
    update();

    timer->start(15*1000);
}

void picShowDialog::paintEvent(QPaintEvent *)
{
    QString picPath;
    QSqlQuery query;

    query.exec("select path from pic where picid = '" + QString::number(curInt, 10) + "'");
    while(query.next())
        picPath = query.value(0).toString();

    qDebug() << picPath << endl;

    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(picPath).scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

}

void picShowDialog::checkTimeOut()
{
    if(curInt == totalInt)
        curInt = 1;
    else
        curInt++;

    update();
}
