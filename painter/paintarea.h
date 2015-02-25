#ifndef PAINTAREA_H
#define PAINTAREA_H
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
class PaintArea : public QWidget
{
public:
    PaintArea();
    void setImageSize(int width,int height);
    void setImageColor(QColor color);
    bool isModified() const { return modified; }
    bool saveImage(const QString &fileName, const char *fileFormat);
    bool openImage(const QString &fileName);
    QSize getImageSize();
    void aboutus();
    void doRotate();
    void doClear();
    void setPenStyle(Qt::PenStyle style);
    void setPenWidth(int width);
    void setPenColor(QColor color);
    void setBrushColor(QColor color);
    enum ShapeType
    {     None,
	  Line, 
	  Rectangle, 
	  Triangle,
	  Fourline,
	  Ellipse
    };
    void setShape(ShapeType shape);
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paint(QImage& theImage);
private:
    QImage image;
    QRgb backColor;
    QPoint lastPoint,endPoint,jiao[3];
    QPoint p1,p2,p3,p4;
    bool modified;
    int angle;
    QColor penColor;
    QColor brushColor;
    int penWidth;
    Qt::PenStyle penStyle;
    ShapeType curShape;
    QImage tempImage;
    bool isDrawing;
};
#endif // PAINTAREA_H
