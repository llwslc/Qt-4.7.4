#include "thinkitem.h"

thinkItem::thinkItem()
{
    mWidth = 172;
    mHeight = 152;

    mCup = qrand()%6 + 1;
    mCol = qrand()%6 + 1;
}

QRectF thinkItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 0;
    return QRectF(-(mWidth-adjust)/2, -(mHeight-adjust)/2, (mWidth+adjust), (mHeight+adjust));
}

void thinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/think.png"));
    painter->drawPixmap(0, -60, QPixmap(":/images/cup" + QString::number(mCup) + "_1.png"));
    painter->drawPixmap(-60, -20, QPixmap(":/images/color" + QString::number(mCol) + "_1.png"));
}

void thinkItem::advance(int step)
{
    if (!step)
        return;
}
