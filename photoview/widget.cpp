#include "widget.h"
#include "ui_widget.h"

#include <QImage>
#include <QBrush>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

QString imageList[101];//最大100张图片
QStringList::Iterator it;
int i=1, j=0, mm=0;
qreal w, h;//这个值很重要，它保证了你要缩放的保真。
QString image_sum , image_positon;

Widget::Widget(QWidget *parent) :
    QWidget(parent) ,
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QPixmap pixmap = QPixmap(":/image/back.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(pixmap));
    this->setPalette(palette);

    setBtnIcon(ui->Open, ":/image/open.png");
    setBtnIcon(ui->big, ":/image/big.png");
    setBtnIcon(ui->litte, ":/image/litte.png");
    setBtnIcon(ui->next, ":/image/next1.png");
    setBtnIcon(ui->previous, ":/image/previous1.png");
    setBtnIcon(ui->nromal, ":/image/normal.png");
    setBtnIcon(ui->recover, ":/image/recover.png");
    setBtnIcon(ui->start, ":/image/start.png");
    setBtnIcon(ui->stop, ":/image/stop.png");
    setBtnIcon(ui->zhuan, ":/image/zhuan.png");
    setBtnIcon(ui->start, ":/image/start.png");

    ui->big->setEnabled(false);
    ui->litte->setEnabled(false);
    ui->next->setEnabled(false);
    ui->nromal->setEnabled(false);
    ui->previous->setEnabled(false);
    ui->recover->setEnabled(false);
    ui->start->setEnabled(false);
    ui->stop->setEnabled(false);
    ui->zhuan->setEnabled(false);

    label = new QLabel(this);
    ui->scrollArea->setWidget(label);
    ui->scrollArea->setAlignment(Qt::AlignCenter);

    ui->image_number->setText(tr("0 / 0"));
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(displayImage()));

    this->setWindowTitle(tr("电子相册"));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_Open_clicked()
{
    int k = 0;
    QStringList list = QFileDialog::getOpenFileNames(this, tr("添加图片"), "/", "*.png *jpg");
    if(0 == list.size())
    {
        return;
    }
    for(it = list.begin(); it < list.end(); it++)
    {
        k++;
        imageList[k] = *it;
    }
    j=k;
    image_sum = QString::number(k);
    image_positon = QString::number(0);
    ui->image_number->setText(tr("%1 / %2").arg(image_positon).arg(image_sum));
    ui->big->setEnabled(true);
    ui->litte->setEnabled(true);
    ui->next->setEnabled(true);
    ui->nromal->setEnabled(true);
    ui->previous->setEnabled(true);
    ui->recover->setEnabled(true);
    ui->start->setEnabled(true);
    ui->stop->setEnabled(true);
    ui->zhuan->setEnabled(true);

    displayImage();
    i--;
}

void Widget::displayImage() //播放
{
    pix.load(imageList[i]);//数组从1开始
    w = label->width();
    h = label->height();
    pix = pix.scaled(w, h, Qt::IgnoreAspectRatio);//设置图片的大小和label的大小相同，注意：IgnoreAspectRatio很重要，
    label->setPixmap(pix);
    image_positon = QString::number(i);
    i++;
    if(i > j)
        i=1;
    ui->image_number->setText(tr("%1 / %2").arg(image_positon).arg(image_sum));
}

void Widget::setBtnIcon(QToolButton *Btn, const QString &path_image)
{
    Btn->setStyleSheet("QToolButton{border:0px}");
    Btn->setIconSize(QSize(Btn->width(), Btn->height()));
    QPixmap pixmap(path_image);
    Btn->setIcon(QIcon(pixmap));
}

void Widget::on_start_clicked()
{
    timer->start(1000);
}

void Widget::on_stop_clicked()
{
    timer->stop();
}

void Widget::on_previous_clicked()//上一张
{
    timer->stop();
    i--;
    if(i<1)
        i=j;
    image_positon = QString::number(i);
    pix.load(imageList[i]);
    w = label->width();
    h = label->height();
    pix = pix.scaled(w, h, Qt::IgnoreAspectRatio);//设置图片的大小和label的大小相同，注意：IgnoreAspectRatio很重要，
    label->setPixmap(pix);
    ui->image_number->setText(tr("%1 / %2").arg(image_positon).arg(image_sum));

    this->setWindowTitle(QString("电子相册 - " + imageList[i]));
}

void Widget::on_next_clicked()//下一张
{
    timer->stop();
    i++;
    if(i>j)//当播放图片大于总图片数时，跳回第一张
        i=1;
    image_positon = QString::number(i);
    pix.load(imageList[i]);
    w = label->width();
    h = label->height();
    pix = pix.scaled(w, h, Qt::IgnoreAspectRatio);//设置图片的大小和label的大小相同，注意：IgnoreAspectRatio很重要，
    label->setPixmap(pix);
    ui->image_number->setText(tr("%1 / %2").arg(image_positon).arg(image_sum));

    this->setWindowTitle(QString("电子相册 - " + imageList[i]));
}

void Widget::on_big_clicked()//放大
{
    pix.load(imageList[i]);
    w *= 1.2;
    h *= 1.2;
    pix = pix.scaled(w, h);//设置图片的大小和label的大小相同，注意：IgnoreAspectRatio很重要，
    label->setPixmap(pix);
}

void Widget::on_litte_clicked()//缩小
{
    pix.load(imageList[i]);
    w *= 0.8;
    h *= 0.8;
    pix = pix.scaled(w, h);//设置图片的大小和label的大小相同，注意：IgnoreAspectRatio很重要，
    label->setPixmap(pix);
}

void Widget::on_nromal_clicked()//原图片大小
{
    pix.load(imageList[i]);
    label->setPixmap(pix);
}

void Widget::on_recover_clicked()//从缩小或放大状态恢复
{
    pix.load(imageList[i]);//这里设置大小设置为固定值，是因为前面的label的大小已经改变

    int width = ui->scrollArea->viewport()->size().width();
    int height = ui->scrollArea->viewport()->size().height();
    pix = pix.scaled(width, height, Qt::IgnoreAspectRatio);//设置图片的大小和label的大小相同，注意：IgnoreAspectRatio很重要，
    label->setPixmap(pix);
}

void Widget::on_zhuan_clicked()//旋转
{
    timer->stop();
    matrix.rotate(90);//旋转90°
    pix = pix.transformed(matrix, Qt::FastTransformation);
    pix = pix.scaled(label->width(), label->height(), Qt::IgnoreAspectRatio);//设置图片大小为label的大小，否则就会出现滑动条
    label->setPixmap(pix);
}
