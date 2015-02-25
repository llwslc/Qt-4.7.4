#include "fishitem.h"

static const double Pi = 3.14159265358979323846264338327950288419717;

fishItem::fishItem()
{
    fishStep = 0;
    speed = 0.0;
    fishType = qrand() % 11 + 1;
}

QRectF fishItem::boundingRect() const
{
    //绘制item大概的区域
    qreal adjust = 2;
    return QRectF(-(fishWidth-adjust)/2, -(fishHeight-adjust)/2, (fishWidth+adjust), (fishHeight+adjust));
}

void fishItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    switch(fishType)
    {
    case 1:
        if(fishStep == 3)
        {
            fishStep = 0;
        }
        fishWidth = 55;
        fishHeight = 37;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish1.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 2:
        if(fishStep == 3)
        {
            fishStep = 0;
        }
        fishWidth = 78;
        fishHeight = 64;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish2.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 3:
        if(fishStep == 3)
        {
            fishStep = 0;
        }
        fishWidth = 72;
        fishHeight = 56;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish3.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 4:
        if(fishStep == 3)
        {
            fishStep = 0;
        }
        fishWidth = 77;
        fishHeight = 59;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish4.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 5:
        if(fishStep == 3)
        {
            fishStep = 0;
        }
        fishWidth = 107;
        fishHeight = 122;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish5.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 6:
        if(fishStep == 7)
        {
            fishStep = 0;
        }
        fishWidth = 105;
        fishHeight = 79;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish6.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 7:
        if(fishStep == 5)
        {
            fishStep = 0;
        }
        fishWidth = 92;
        fishHeight = 151;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish7.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 8:
        if(fishStep == 7)
        {
            fishStep = 0;
        }
        fishWidth = 174;
        fishHeight = 126;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish8.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 9:
        if(fishStep == 7)
        {
            fishStep = 0;
        }
        fishWidth = 166;
        fishHeight = 183;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish9.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 10:
        if(fishStep == 5)
        {
            fishStep = 0;
        }
        fishWidth = 178;
        fishHeight = 187;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish10.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    case 11:
        if(fishStep == 3)
        {
            fishStep = 0;
        }
        fishWidth = 133;
        fishHeight = 52;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish11.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    default:
        if(fishStep == 3)
        {
            fishStep = 0;
        }
        fishWidth = 55;
        fishHeight = 37;
        painter->drawPixmap(boundingRect().topLeft(), QPixmap(":/images/fish1.png").copy(0, fishHeight*fishStep, fishWidth, fishHeight));
        break;
    }
    fishStep++;
}

void fishItem::advance(int step)
{
    if (!step)
        return;

    speed = abs(100-fishWidth) / 10 + 5; //qreal(qrand() % 100) / 10.0;
    setPos(mapToParent(speed, 0));

    update();
}

int fishItem::type() const
{
    //返回类型
    return FISHITEM;
}
