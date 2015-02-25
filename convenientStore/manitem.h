#ifndef MANITEM_H
#define MANITEM_H

#include "common.h"

class manItem : public QGraphicsItem
{
public:
    manItem();

    int mWidth;
    int mHeight;

    int mType;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void advance(int step);
};
#endif // MANITEM_H
