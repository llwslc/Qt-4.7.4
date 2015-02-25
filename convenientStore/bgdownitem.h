#ifndef BGDOWNITEM_H
#define BGDOWNITEM_H

#include "common.h"

class bgDownItem : public QGraphicsItem
{
public:
    bgDownItem();

    int mWidth;
    int mHeight;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int step);
};

#endif // BGDOWNITEM_H
