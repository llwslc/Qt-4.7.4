#include "paintarea.h"
#include <QPainter>
#include <QPrintDialog>
#include <QPrinter>
#include <QMessageBox>
#include<qvector.h>
int presscount=0;
PaintArea::PaintArea()
{
    //初始化数据
    image = QImage(520,390,QImage::Format_RGB32); //画布的初始化大小设为520,390，使用32位颜色
    backColor = qRgb(255,255,255); //画布初始化背景色使用白色
    image.fill(backColor);
    modified = false;
    angle = 0;

    penColor = Qt::black;
    brushColor = Qt::white;
    penWidth = 1;
    penStyle = Qt::SolidLine;
    curShape = None;
    isDrawing = false;
}
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this); 
    if(isDrawing)   //如果正在绘制特殊图形，则显示临时绘图区上的内容
    { 
        painter.drawImage(0,0,tempImage);
    } 
    else 
    { 
        if(angle) 
        { 
            QImage copyImage = image;  //新建临时的 copyImage，利用它进行旋转操作 
            QPainter pp(&copyImage); 
            QPointF center(copyImage.width()/2.0,copyImage.height()/2.0); 
            pp.translate(center); 
            pp.rotate(angle); 
            pp.translate(-center); 
            pp.drawImage(0,0,image); 
            image = copyImage;   //只会复制图片上的内容，不会复制坐标系统 
            angle = 0;   //完成旋转后将角度值重新设为 0 
        }
        painter.drawImage(0,0,image); 
    }
}
void PaintArea::mousePressEvent(QMouseEvent *event)
{
    //鼠标压下
    if(event->button() == Qt::LeftButton)
    {
        lastPoint = event->pos();

        isDrawing = true;
    }
}
void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    //鼠标移动
    if(event->buttons()&Qt::LeftButton)
    {
        endPoint = event->pos();
        if(curShape == None)
        {
            isDrawing = false;
            paint(image);
        }
        else
        {
            tempImage = image;
            paint(tempImage);
        }
    }
}
void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    //鼠标释放
    if(event->button() == Qt::LeftButton)
    {
        endPoint = event->pos();
        isDrawing = false;
        paint(image);
    }
}
void PaintArea::paint(QImage &theImage)
{
    //绘图
    QPainter pp(&theImage);
    QPen pen = QPen();
    pen.setColor(penColor);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);
    QBrush brush = QBrush(brushColor);
    pp.setPen(pen);
    pp.setBrush(brush);
    int x,y,w,h,f,g;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x() - x;
    h = endPoint.y() - y;
    jiao[2]=endPoint;
    f=(lastPoint.x()+endPoint.x())/2;

    switch(curShape)
    {
    case None:
    {
        pp.drawLine(lastPoint,endPoint);
        lastPoint = endPoint;
        presscount=0;
        break;
    }
    case Line:
    {
        pp.drawLine(lastPoint,endPoint);
        presscount=0;
        break;
    }
    case Rectangle:
    {
        pp.drawRect(x,y,w,h);
        presscount=0;
        break;
    }
    case Ellipse:
    {
        pp.drawEllipse(x,y,w,h);
        presscount=0;
        break;
    }
    case Triangle:
    {
	QPolygonF polygon;
	
        polygon << QPointF( lastPoint.x(), endPoint.y())<<endPoint << QPointF(f, lastPoint.y());
        presscount=0;
        pp.drawPolygon(polygon, Qt::WindingFill);
        break;
    }
    default:
    {
        break;
    }
    }
    update(); //进行更新界面显示，可引起窗口重绘事件，重绘窗口
    modified = true;
}
void PaintArea::setImageSize(int width, int height)
{
    //设置图像大小
    QImage newImage(width,height,QImage::Format_RGB32);
    image = newImage;
    update();
}
void PaintArea::setImageColor(QColor color)
{
    //设置图像颜色
    backColor = color.rgb(); //因为image的背景色要用QRgb类型的颜色，所以这里进行了一下转换
    image.fill(backColor);
    update();
}
bool PaintArea::saveImage(const QString &fileName, const char *fileFormat)
{
    //保存图片
    QImage visibleImage = image;
    if (visibleImage.save(fileName, fileFormat))
    {
        modified = false;
        return true;
    }
    else
    {
        return false;
    }
}
bool PaintArea::openImage(const QString &fileName)
{
    //打开图片
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
    QSize newSize = loadedImage.size();
    setImageSize(newSize.width(),newSize.height());
    image = loadedImage;
    modified = false;
    update();
    return true;
}
QSize PaintArea::getImageSize()
{
    //获取图像大小
    return image.size();
}
void PaintArea::aboutus()
{
    //关于
    QMessageBox::StandardButton boxus;
    boxus = QMessageBox::information(this,tr("关于画图！"),tr("东软信息学院"),
                                     QMessageBox::Yes);
}
void PaintArea::doRotate()
{
    //旋转
    angle +=90;
    update();
}
void PaintArea::doClear()
{
    //清空
    image.fill(backColor); //用现在的画布背景色进行填充
    update();
}
void PaintArea::setPenStyle(Qt::PenStyle style)
{
    //设置笔
    penStyle = style;
}
void PaintArea::setPenWidth(int width)
{
    //设置宽度
    penWidth = width;
}
void PaintArea::setPenColor(QColor color)
{
    //设置颜色
    penColor = color;
}
void PaintArea::setBrushColor(QColor color)
{
    //设置刷子
    brushColor = color;
}
void PaintArea::setShape(ShapeType shape)
{
    //设置笔画的型
    curShape = shape;
}
