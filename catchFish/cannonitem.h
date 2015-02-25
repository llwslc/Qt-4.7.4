#ifndef CONNONITEM_H
#define CONNONITEM_H

#include "common.h"

class cannonItem : public QGraphicsItem
{
public:
    cannonItem();

    int cannonWidth;
    int cannonHeight;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int type() const;

protected:
    void advance(int step);
};



#endif // CONNONITEM_H
