#ifndef TIMEITEM_H
#define TIMEITEM_H

#include "common.h"

class timeItem : public QGraphicsItem
{
public:
    timeItem();

    QString timeSting;

    int timeWidth;
    int timeHeight;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int step);
};

#endif // TIMEITEM_H
