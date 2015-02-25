#include "aboutitem.h"

aboutItem::aboutItem()
{
    aboutWidth = 800;
    aboutHeight = 600;
}

QRectF aboutItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 2;
    return QRectF(-(aboutWidth-adjust)/2, -(aboutHeight-adjust)/2, (aboutWidth+adjust), (aboutHeight+adjust));
}

void aboutItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/about.png"));
}

void aboutItem::advance(int step)
{
    if (!step)
        return;
}

void aboutItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    scene()->removeItem(this);
}


