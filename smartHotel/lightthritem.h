#ifndef LIGHTTHRITEM_H
#define LIGHTTHRITEM_H

#include "common.h"

class lightThrItem : public QGraphicsItem
{
public:
    lightThrItem();

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


#endif // LIGHTTHRITEM_H
