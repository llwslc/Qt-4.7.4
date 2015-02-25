#ifndef FISHITEM_H
#define FISHITEM_H

#include "common.h"

class fishItem : public QGraphicsItem
{
public:
    fishItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int type() const;

protected:
    void advance(int step);

private:
    qreal speed;
    int fishType;
    int fishWidth;
    int fishHeight;
    int fishStep;
};

#endif // FISHITEM_H
