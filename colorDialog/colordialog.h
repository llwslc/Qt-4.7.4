#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QtGui>
#include <qmath.h>

#define PI 3.1415926

class colorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit colorDialog(QWidget *parent = 0);
    ~colorDialog();

    bool initFlag;          //是否第一次初始化
    bool colorFlag;         //是否选择了颜色
    bool selectSCFlag;      //是否选择了单色盘中小圈
    bool selectHCFlag;      //是否选择了拾色盘中小圈
    QColor pickRoundColor;  //选择的基础颜色
    QColor pickRadialColor; //选择的特定颜色

    int drawRoundX;			//彩色盘
    int drawRoundY;
    int drawRoundRadius;
    int drawRoundHeight;
    int drawRoundCentreX;
    int drawRoundCentreY;

    int drawRadialX;		//单色盘
    int drawRadialY;
    int drawRadialRadius;
    int drawRadialCentreX;
    int drawRadialCentreY;

    int drawHollowCircleX[2];//空心盘
    int drawHollowCircleY[2];
    int drawHollowCircleRadius[2];
    int drawHollowCircleCentreX[2];
    int drawHollowCircleCentreY[2];

    int drawColorStandardDrawX;//标准色起始位置
    int drawColorStandardDrawY;
    int drawColorStandardDrawW;
    int drawColorStandardDrawH;
    int drawColorStandardSpaceW;
    int drawColorStandardSpaceH;

    int drawColorStandardX[14];//标准色
    int drawColorStandardY[14];
    int drawColorStandardW[14];
    int drawColorStandardH[14];
    QColor drawColorStandardC[14];

    int drawColorSelectX;		//选中颜色框
    int drawColorSelectY;
    int drawColorSelectW;
    int drawColorSelectH;

    QPushButton *selectBtn; //选择按钮
    QPushButton *cancelBtn; //退出按钮

    void paintEvent(QPaintEvent *e);

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void myMouseEvent(QMouseEvent *e);

    void drawColorRound();
    void drawColorRadial();
    void drawColorLinear();
    void drawHollowCircle();
    void drawColorStandard();
    void drawColorSelect();

    void setColor(QColor col);
    QColor getColor();

signals:
    void sendColor(const QColor col);

private slots:
    void selectBtnClicked();
    void cancelBtnClicked();

};

#endif // COLORDIALOG_H
