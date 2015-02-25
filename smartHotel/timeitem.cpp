#include "timeitem.h"

timeItem::timeItem()
{
    timeSting = QDateTime::currentDateTime().toString("yyyy/MM/dd dddd hh:mm:ss");

    timeWidth = 300;
    timeHeight = 100;
}

void timeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QFont font;
    font.setPixelSize(18);
    font.setBold(true);
    painter->setPen(Qt::yellow);
    painter->setFont(font);

    timeSting = QDateTime::currentDateTime().toString("yyyy/MM/dd\ndddd\nhh:mm:ss");

    painter->drawText(boundingRect(), Qt::AlignRight | Qt::AlignVCenter, timeSting);
}

QRectF timeItem::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-(timeWidth-adjust)/2, -(timeHeight-adjust)/2, (timeWidth+adjust), (timeHeight+adjust));
}

void timeItem::advance(int step)
{
    if (!step)
        return;

    update();
}


