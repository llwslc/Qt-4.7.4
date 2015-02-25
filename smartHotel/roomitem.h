#ifndef ROOMITEM_H
#define ROOMITEM_H

#include "common.h"

class roomItem : public QGraphicsItem
{
public:
    roomItem();

    int roomWidth;
    int roomHeight;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    void advance(int step);
};


#endif // ROOMITEM_H
