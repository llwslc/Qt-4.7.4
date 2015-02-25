#include "roomItem.h"

roomItem::roomItem()
{
    roomWidth = 800;
    roomHeight = 600;
}

QRectF roomItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 2;
    return QRectF(-(roomWidth-adjust)/2, -(roomHeight-adjust)/2, (roomWidth+adjust), (roomHeight+adjust));
}

void roomItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/room.png").scaled(roomWidth, roomHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void roomItem::advance(int step)
{
    if (!step)
        return;
}

void roomItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //点击
}


