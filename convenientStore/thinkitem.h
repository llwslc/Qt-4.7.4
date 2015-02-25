#ifndef THINKITEM_H
#define THINKITEM_H

#include "common.h"

class thinkItem : public QGraphicsItem
{
public:
    thinkItem();

    int mWidth;
    int mHeight;

    int mCup;
    int mCol;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int step);
};

#endif // THINKITEM_H
