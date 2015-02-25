#ifndef BARITEM_H
#define BARITEM_H

#include "common.h"

class barItem : public QGraphicsItem
{
public:
    barItem();

    int barWidth;
    int barHeight;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int type() const;

protected:
    void advance(int step);
};



#endif // BARITEM_H
