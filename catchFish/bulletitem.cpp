#include "bulletitem.h"

bulletItem::bulletItem()
{
    bulletWidth = 24;
    bulletHeight = 26;
    speed = 5;
}

QRectF bulletItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 2;
    return QRectF(-(bulletWidth-adjust)/2, -(bulletHeight-adjust)/2, (bulletWidth+adjust), (bulletHeight+adjust));
}

void bulletItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/bullet.png"));
}

void bulletItem::advance(int step)
{
    if (!step)
        return;

    //检测所有碰撞
    QList<QGraphicsItem *> list = scene()->collidingItems(this);
    if (list.size() != 0)
    {
        foreach(QGraphicsItem *item, list)
        {
            if (item == this)
            {
                continue;
            }

            if (item->type() == FISHITEM)
            {
                webItem *web = new webItem;
                web->setPos(item->pos().x(),
                            item->pos().y());
                web->setRotation(0);
                scene()->addItem(web);

                //打中鱼给分数
                score += 100;

                scene()->removeItem(item);
                scene()->removeItem(this);
                return;
            }
        }
    }
    setPos(mapToParent(0, -speed));

}

int bulletItem::type() const
{
    //返回类型
    return BULLETITEM;
}


