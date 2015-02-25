#ifndef LIGHTONEITEM_H
#define LIGHTONEITEM_H

#include "common.h"

class lightOneItem : public QGraphicsItem
{
public:
    lightOneItem();

    int lightWidth;
    int lightHeight;

    int lightStep;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void lightOn();

    void lightOff();

    void lightStepChange();

protected:
    void advance(int step);
};


#endif // LIGHTONEITEM_H
