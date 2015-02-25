#include "lighttwoitem.h"

lightTwoItem::lightTwoItem()
{
    lightWidth = 148 * 0.8;
    lightHeight = 482 * 0.8;

    lightStep = 0;
}

QRectF lightTwoItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 2;
    return QRectF(-(lightWidth-adjust)/2, -(lightHeight-adjust)/2, (lightWidth+adjust), (lightHeight+adjust));
}

void lightTwoItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    switch(lightStep % 2)
    {
    case 0:
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/transparent.png").scaled(lightWidth, lightHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    case 1:
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/light2.png").scaled(lightWidth, lightHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    default:
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/light2.png").scaled(lightWidth, lightHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    }
}

void lightTwoItem::advance(int step)
{
    if (!step)
        return;
}

void lightTwoItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //点击
    lightStep++;

    update();
}

void lightTwoItem::lightOn()
{
    lightStep = 1;

    update();
}

void lightTwoItem::lightOff()
{
    lightStep = 0;

    update();
}

void lightTwoItem::lightStepChange()
{
    //灯泡亮灭改变
    lightStep++;

    update();
}


