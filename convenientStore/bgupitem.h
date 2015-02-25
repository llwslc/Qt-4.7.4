#ifndef BGUPITEM_H
#define BGUPITEM_H

#include "common.h"

class bgUpItem : public QGraphicsItem
{
public:
    bgUpItem();

    int mWidth;
    int mHeight;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int step);
};

#endif // BGUPITEM_H
