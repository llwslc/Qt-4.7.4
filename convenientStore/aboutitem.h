#ifndef ABOUTITEM_H
#define ABOUTITEM_H

#include "common.h"

class aboutItem : public QGraphicsItem
{
public:
    aboutItem();

    int aboutWidth;
    int aboutHeight;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    void advance(int step);
};


#endif // ABOUTITEM_H
