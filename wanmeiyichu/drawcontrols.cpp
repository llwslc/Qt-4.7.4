#include "drawcontrols.h"

imageButton::imageButton(QWidget *parent) :
    QPushButton(parent)
{
    //保存图片成员初始化
    buttonPicture = new QPixmap();
    pressPicture = new QPixmap();
    releasePicture = new QPixmap();

    //关闭按钮的默认显示
    this->setFlat(true);
    this->setFocusPolicy(Qt::NoFocus);
}

void imageButton::setButtonPicture(QPixmap pic)
{
    *buttonPicture = pic;
    this->setIcon(QIcon(*buttonPicture));
}

void imageButton::setPressPicture(QPixmap pic)
{
    *pressPicture = pic;
}

void imageButton::setReleasePicture(QPixmap pic)
{
    *releasePicture = pic;
}

void imageButton::set_X_Y_width_height(int x, int y, int width, int height)
{
    this->setIconSize(QSize(width, height));
    this->setGeometry(x, y, width, height);
}

void imageButton::mousePressEvent(QMouseEvent *event)
{
    this->setIcon(QIcon(*pressPicture));
}

void imageButton::mouseMoveEvent(QMouseEvent *event)
{
}

void imageButton::mouseReleaseEvent(QMouseEvent *event)
{
    this->setIcon(QIcon(*releasePicture));
    emit clicked();
}

void imageButton::enterEvent(QEvent *)
{
    this->setIcon (QIcon(*pressPicture));
}

void imageButton::leaveEvent(QEvent *)
{
    this->setIcon(QIcon(*buttonPicture));
}

void imageButton::resizeit(int w , int h)
{
    this->raise();
    this->resize(w,h);
    this ->setIconSize(QSize(w, h));
}
