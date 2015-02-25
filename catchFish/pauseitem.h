#ifndef PAUSEITEM_H
#define PAUSEITEM_H

#include "common.h"

class pauseItem : public QGraphicsItem
{
public:
    pauseItem();

    int pauseWidth;
    int pauseHeight;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int type() const;

protected:
    void advance(int step);
};



#endif // PAUSEITEM_H
