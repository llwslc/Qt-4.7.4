#ifndef BUTTLETITEM_H
#define BUTTLETITEM_H

#include "common.h"
#include "webitem.h"

class bulletItem : public QGraphicsItem
{
public:
    bulletItem();

    int bulletWidth;
    int bulletHeight;
    int speed;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int type() const;

protected:
    void advance(int step);
};



#endif // BUTTLETITEM_H
