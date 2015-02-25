#include "lightthritem.h"

lightThrItem::lightThrItem()
{
    lightWidth = 422 * 0.8;
    lightHeight = 153 * 0.8;

    lightStep = 0;
}

QRectF lightThrItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 2;
    return QRectF(-(lightWidth-adjust)/2, -(lightHeight-adjust)/2, (lightWidth+adjust), (lightHeight+adjust));
}

void lightThrItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    switch(lightStep % 2)
    {
    case 0:
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/transparent.png").scaled(lightWidth, lightHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    case 1:
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/light3.png").scaled(lightWidth, lightHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    default:
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/light3.png").scaled(lightWidth, lightHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    }
}

void lightThrItem::advance(int step)
{
    if (!step)
        return;
}

void lightThrItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //点击
    lightStep++;

    update();
}

void lightThrItem::lightOn()
{
    lightStep = 1;

    update();
}

void lightThrItem::lightOff()
{
    lightStep = 0;

    update();
}

void lightThrItem::lightStepChange()
{
    //灯泡亮灭改变
    lightStep++;

    update();
}


