#include "bgDownItem.h"

bgDownItem::bgDownItem()
{
    mWidth = 640;
    mHeight = 247;
}

QRectF bgDownItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 0;
    return QRectF(-(mWidth-adjust)/2, -(mHeight-adjust)/2, (mWidth+adjust), (mHeight+adjust));
}

void bgDownItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/bgdown.png"));
}

void bgDownItem::advance(int step)
{
    if (!step)
        return;
}
