#ifndef CUSTOMDRAWCONTROLS_H
#define CUSTOMDRAWCONTROLS_H

#include "common.h"

//Í¼Æ¬°´Å¥
class imageButton : public QPushButton
{
    Q_OBJECT
public:
    explicit imageButton(QWidget *parent = 0);

private:
    QPixmap *buttonPicture;
    QPixmap *pressPicture;
    QPixmap *releasePicture;

public:
    void setButtonPicture(QPixmap pic);

    void setPressPicture(QPixmap pic);

    void setReleasePicture(QPixmap pic);

    void set_X_Y_width_height(int x, int y, int width, int height);

    void mousePressEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void enterEvent(QEvent *);

    void leaveEvent(QEvent *);

    void resizeit(int w, int h);

signals:

public slots:

};

//×éºÏ¿ò
class noMoveComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit noMoveComboBox(QWidget *parent = 0) : QComboBox(parent){}

    void mouseMoveEvent(QMouseEvent *){}

signals:

public slots:

};

class buttonsClicked : public QPushButton
{
    Q_OBJECT
public:
    explicit buttonsClicked(QWidget *parent = 0){}

public slots:
    void Clicked(){ emit clicked(); }
};

#endif // CUSTOMDRAWCONTROLS_H
