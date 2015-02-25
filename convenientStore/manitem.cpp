#include "manitem.h"

manItem::manItem()
{
    mWidth = 120;
    mHeight = 181;

    mType = qrand()%6 + 1;
}

QRectF manItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 0;
    return QRectF(-(mWidth-adjust)/2, -(mHeight-adjust)/2, (mWidth+adjust), (mHeight+adjust));
}

void manItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    switch(mType)
    {
    case 1:
        mWidth = 120;
        mHeight = 181;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/man1.png"));
        break;
    case 2:
        mWidth = 120;
        mHeight = 165;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/man2.png"));
        break;
    case 3:
        mWidth = 120;
        mHeight = 190;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/man3.png"));
        break;
    case 4:
        mWidth = 120;
        mHeight = 169;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/man4.png"));
        break;
    case 5:
        mWidth = 120;
        mHeight = 190;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/man5.png"));
        break;
    case 6:
        mWidth = 120;
        mHeight = 160;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/man6.png"));
        break;
    default:
        mWidth = 120;
        mHeight = 181;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/man1.png"));
        break;
    }
}

void manItem::advance(int step)
{
    if (!step)
        return;
}
