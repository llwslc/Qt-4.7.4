#include "webitem.h"

webItem::webItem()
{
    webWidth = 116;
    webHeight = 118;
    webTime = 0;
}

QRectF webItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 2;
    return QRectF(-(webWidth-adjust)/2, -(webHeight-adjust)/2, (webWidth+adjust), (webHeight+adjust));
}

void webItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/web.png"));
}

void webItem::advance(int step)
{
    if (!step)
        return;

    webTime++;
    if(webTime == 15)
    {
        scene()->removeItem(this);
    }
}

int webItem::type() const
{
    //返回类型
    return WEBITEM;
}



