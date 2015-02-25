#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtGui>
#include <qmath.h>

//KSD颜色模型子类
class ParamColor
{
public:
    ParamColor()
    {
        this->dR = 0;
        this->dG = 0;
        this->dB = 0;
    }

    ParamColor(double dR, double dG, double dB)
    {
        this->dR = dR;
        this->dG = dG;
        this->dB = dB;
    }

    ParamColor(const ParamColor& ParamC)
    {
        this->dR = ParamC.dR;
        this->dG = ParamC.dG;
        this->dB = ParamC.dB;
    }

    ParamColor &operator =(const ParamColor& ParamC)
    {
        this->dR = ParamC.dR;
        this->dG = ParamC.dG;
        this->dB = ParamC.dB;
        return *this;
    }
public:
    double dR;
    double dG;
    double dB;
};

//KSD颜色模型类
class KSDColor
{
public:
    KSDColor()
    {
        this->dK = ParamColor();
        this->dS = ParamColor();
        this->dD = 0;
    }

    KSDColor(ParamColor dK, ParamColor dS, double dD)
    {
        this->dK = dK;
        this->dS = dS;
        this->dD = dD;
    }

    KSDColor &operator =(const KSDColor& KSDCol)
    {
        this->dK = KSDCol.dK;
        this->dS = KSDCol.dS;
        this->dD = KSDCol.dD;
        return *this;
    }
public:
    ParamColor dK;
    ParamColor dS;
    double dD;
};

//KSD转为RGB
QColor KSDToRGB(const KSDColor KSDCol);
//KSD混合
KSDColor KSDMix(const KSDColor KSDColF, const KSDColor KSDColS);

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    QColor drawColorStandardRGB[7];     //RGB标准色
    KSDColor drawColorStandardKSD[7];   //KSD标准色

    KSDColor drawColorMixKSD;           //KSD混合色
    KSDColor drawColorSelectKSD;        //KSD选择色

    int drawColorX;                      //色块起始X
    int drawColorY;                      //色块起始Y
    int drawColorW;                      //色块起始W
    int drawColorH;                      //色块起始H
    int drawColorS;                      //色块起始S

    int drawColorStandardX[7];           //标准色起始X
    int drawColorStandardY[7];           //标准色起始Y
    int drawColorStandardW[7];           //标准色起始W
    int drawColorStandardH[7];           //标准色起始H

    int drawColorMixX;                   //混合色起始X
    int drawColorMixY;                   //混合色起始Y
    int drawColorMixW;                   //混合色起始W
    int drawColorMixH;                   //混合色起始H


    QPushButton *clearBtn;               //清空按钮
    QPushButton *selectBtn;              //选择按钮

    int buttonX[2];                      //按钮起始X
    int buttonY[2];                      //按钮起始Y
    int buttonW[2];                      //按钮起始W
    int buttonH[2];                      //按钮起始H
    int buttonS;                         //按钮起始s

    void paintEvent(QPaintEvent *e);
    void drawColorStandard();           //绘制标准颜色矩形
    void drawColorMix();                //绘制混合颜色矩形

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void myMouseEvent(QMouseEvent *e);

signals:
    void sendColor(const QColor col);

private slots:
    void clearBtnClicked();
    void selectBtnClicked();

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
