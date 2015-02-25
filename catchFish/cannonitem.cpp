#include "cannonitem.h"

cannonItem::cannonItem()
{
    cannonWidth = 74;
    cannonHeight = 74;
}

QRectF cannonItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 2;
    return QRectF(-(cannonWidth-adjust)/2, -(cannonHeight-adjust)/2, (cannonWidth+adjust), (cannonHeight+adjust));
}

void cannonItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/cannon.png").copy(0, 0, cannonWidth, cannonHeight));
}

void cannonItem::advance(int step)
{
    if (!step)
        return;
}

int cannonItem::type() const
{
    //返回类型
    return CANNONITEM;
}

