#include "bgupitem.h"

bgUpItem::bgUpItem()
{
    mWidth = 640;
    mHeight = 233;
}

QRectF bgUpItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 0;
    return QRectF(-(mWidth-adjust)/2, -(mHeight-adjust)/2, (mWidth+adjust), (mHeight+adjust));
}

void bgUpItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/bgup.png"));
}

void bgUpItem::advance(int step)
{
    if (!step)
        return;
}
