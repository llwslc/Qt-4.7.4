#ifndef LIGHTTWOITEM_H
#define LIGHTTWOITEM_H

#include "common.h"

class lightTwoItem : public QGraphicsItem
{
public:
    lightTwoItem();

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


#endif // LIGHTTWOITEM_H
