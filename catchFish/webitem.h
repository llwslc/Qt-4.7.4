#ifndef WEBITEM_H
#define WEBITEM_H

#include "common.h"

class webItem : public QGraphicsItem
{
public:
    webItem();

    int webWidth;
    int webHeight;
    int webTime;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int type() const;

protected:
    void advance(int step);
};



#endif // WEBITEM_H
