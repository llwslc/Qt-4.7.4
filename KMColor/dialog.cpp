#include "dialog.h"
#include "ui_dialog.h"


//KSD转为RGB
QColor KSDToRGB(const KSDColor KSDCol)
{
    QColor targetCol = QColor(0, 0, 0);
    double iA[3] = {0.0, 0.0, 0.0};      //a
    double iB[3] = {0.0, 0.0, 0.0};      //b
    double Rg = 1.0;                     //Rg

    iA[0] = 1 + KSDCol.dK.dR / KSDCol.dS.dR;
    iA[1] = 1 + KSDCol.dK.dG / KSDCol.dS.dG;
    iA[2] = 1 + KSDCol.dK.dB / KSDCol.dS.dB;

    iB[0] = sqrt(pow(iA[0], 2) - 1);
    iB[1] = sqrt(pow(iA[1], 2) - 1);
    iB[2] = sqrt(pow(iA[2], 2) - 1);

    int R = (255 * ((1 - (Rg * (iA[0] - (iB[0] * 1 / tanh(iB[0]*KSDCol.dS.dR*KSDCol.dD))))) / (iA[0] + (iB[0] * 1 / tanh(iB[0]*KSDCol.dS.dR*KSDCol.dD)) - Rg)));
    int G = (255 * ((1 - (Rg * (iA[1] - (iB[1] * 1 / tanh(iB[1]*KSDCol.dS.dR*KSDCol.dD))))) / (iA[1] + (iB[1] * 1 / tanh(iB[1]*KSDCol.dS.dR*KSDCol.dD)) - Rg)));
    int B = (255 * ((1 - (Rg * (iA[2] - (iB[2] * 1 / tanh(iB[2]*KSDCol.dS.dR*KSDCol.dD))))) / (iA[2] + (iB[2] * 1 / tanh(iB[2]*KSDCol.dS.dR*KSDCol.dD)) - Rg)));
    targetCol.setRed((R<0) ? 0 : R);
    targetCol.setGreen((G<0) ? 0 : G);
    targetCol.setBlue((B<0) ? 0 : B);

    return targetCol;
}

//KSD混合
KSDColor KSDMix(const KSDColor KSDColF, const KSDColor KSDColS)
{
    KSDColor targetCol = KSDColor(ParamColor(), ParamColor(), 0);
    double iC[2] = {0.5, 0.5};            //c
    double iK[3] = {0.0, 0.0, 0.0};       //k
    double iS[3] = {0.0, 0.0, 0.0};       //s

    iK[0] = KSDColF.dK.dR * iC[0] + KSDColS.dK.dR * iC[1];
    iK[1] = KSDColF.dK.dG * iC[0] + KSDColS.dK.dG * iC[1];
    iK[2] = KSDColF.dK.dB * iC[0] + KSDColS.dK.dB * iC[1];

    iS[0] = KSDColF.dS.dR * iC[0] + KSDColS.dS.dR * iC[1];
    iS[1] = KSDColF.dS.dG * iC[0] + KSDColS.dS.dG * iC[1];
    iS[2] = KSDColF.dS.dB * iC[0] + KSDColS.dS.dB * iC[1];

    targetCol = KSDColor(ParamColor(iK[0], iK[1], iK[2]), ParamColor(iS[0], iS[1], iS[2]), 3.5);

    return targetCol;
}


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    //初始化颜色
    drawColorStandardRGB[0] = QColor(230, 26, 26);       //某红色颜料
    drawColorStandardRGB[1] = QColor(232, 231, 25);      //某黄色颜料
    drawColorStandardRGB[2] = QColor(22, 169, 81);       //石绿颜料
    drawColorStandardRGB[3] = QColor(22, 133, 169);      //石青颜料
    drawColorStandardRGB[4] = QColor(75, 92, 196);       //宝蓝颜料
    drawColorStandardRGB[5] = QColor(141, 75, 187);      //紫色颜料
    drawColorStandardRGB[6] = QColor(57, 47, 65);        //乌黑颜料

    drawColorStandardKSD[0] = KSDColor(ParamColor(0.047, 0.81, 0.81), ParamColor(8.46, 0.2, 0.2), 3.6);          //某红色颜料
    drawColorStandardKSD[1] = KSDColor(ParamColor(0.047, 0.047, 0.81), ParamColor(8.46, 8.46, 0.2), 3.6);        //某黄色颜料
    drawColorStandardKSD[2] = KSDColor(ParamColor(0.7312, 1.9785, 0.5156), ParamColor(0.15, 2.31, 0.705), 3.6);  //石绿颜料
    drawColorStandardKSD[3] = KSDColor(ParamColor(0.7739, 0.3072, 0.2016), ParamColor(0.16, 1.4, 2.35), 3.7);    //石青颜料
    drawColorStandardKSD[4] = KSDColor(ParamColor(0.5422, 0.4586, 0.1295), ParamColor(0.64, 0.81, 3.72), 3.5);   //宝蓝颜料
    drawColorStandardKSD[5] = KSDColor(ParamColor(0.2748, 0.5337, 0.1533), ParamColor(1.52, 0.63, 3.16), 3.7);   //紫色颜料
    drawColorStandardKSD[6] = KSDColor(ParamColor(0.607, 0.6679, 0.5881), ParamColor(0.45, 0.37, 0.54), 4.5);    //乌黑颜料

    drawColorX = 10;                      //色块起始X
    drawColorY = 10;                      //色块起始Y
    drawColorW = 50;                      //色块起始W
    drawColorH = 50;                      //色块起始H
    drawColorS = 10;                      //色块起始S

    for (int i=0; i<7; i++)
    {
        drawColorStandardX[i] = drawColorX + i * (drawColorS + drawColorW);
        drawColorStandardY[i] = drawColorY;
        drawColorStandardW[i] = drawColorW;
        drawColorStandardH[i] = drawColorH;
    }

    drawColorMixX = drawColorX;                                         //混合色起始X
    drawColorMixY = drawColorY + drawColorH + drawColorS;               //混合色起始Y
    drawColorMixW = drawColorW * 7 + drawColorS * 6;                    //混合色起始W
    drawColorMixH = drawColorH * 2;                                     //混合色起始H

    for(int j=0; j<2; j++)
    {
        buttonS = drawColorS * 2 + drawColorW;
        buttonW[j] = drawColorS * 2 + drawColorW * 3;
        buttonH[j] = drawColorH;

        buttonX[j] = drawColorX + j * (buttonS + buttonW[j]);
        buttonY[j] = drawColorMixY + drawColorMixH + drawColorS;
    }

    clearBtn = new QPushButton(this);
    selectBtn = new QPushButton(this);
    clearBtn->setText(QString("Clear"));
    selectBtn->setText(QString("Select"));
    clearBtn->setGeometry(buttonX[0], buttonY[0], buttonW[0], buttonH[0]);
    selectBtn->setGeometry(buttonX[1], buttonY[1], buttonW[1], buttonH[1]);

    QObject::connect(clearBtn, SIGNAL(clicked()), this, SLOT(clearBtnClicked()));
    QObject::connect(selectBtn, SIGNAL(clicked()), this, SLOT(selectBtnClicked()));

    drawColorMixKSD = KSDColor(ParamColor(), ParamColor(), 0);          //KSD混合色
    drawColorSelectKSD = KSDColor(ParamColor(), ParamColor(), 0);       //KSD选择色

    this->resize((drawColorStandardX[6] + drawColorS + drawColorW), (buttonY[0] + buttonH[0] + drawColorS));

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::paintEvent(QPaintEvent *e)
{
    drawColorStandard();
    drawColorMix();
}

//绘制标准颜色矩形
void Dialog::drawColorStandard()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for (int i=0; i<7; i++)
    {
        painter.setPen(drawColorStandardRGB[i]);
        painter.setBrush(QBrush(drawColorStandardRGB[i], Qt::SolidPattern));
        painter.drawRect(drawColorStandardX[i], drawColorStandardY[i], drawColorStandardW[i], drawColorStandardH[i]);
    }
}

//绘制混合颜色矩形
void Dialog::drawColorMix()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor col = KSDToRGB(drawColorMixKSD);

    painter.setPen(col);
    painter.setBrush(QBrush(col, Qt::SolidPattern));
    painter.drawRect(drawColorMixX, drawColorMixY, drawColorMixW, drawColorMixH);
}
//鼠标压下移动
void Dialog::mouseMoveEvent(QMouseEvent *e)
{
    // NULL
}

//鼠标压下
void Dialog::mousePressEvent(QMouseEvent *e)
{
    myMouseEvent(e);
}

//鼠标释放
void Dialog::mouseReleaseEvent(QMouseEvent *e)
{
    // NULL
}

//鼠标事件
void Dialog::myMouseEvent(QMouseEvent *e)
{
    for (int i=0; i<7; i++)
    {
        if ((e->x() >= drawColorStandardX[i]) && (e->x() <= (drawColorStandardX[i] + drawColorStandardW[i])))
        {
            if ((e->y() >= drawColorStandardY[i]) && (e->y() <= (drawColorStandardY[i] + drawColorStandardH[i])))
            {
                drawColorSelectKSD = drawColorStandardKSD[i];                  //KSD选择色
                drawColorMixKSD = KSDMix(drawColorMixKSD, drawColorSelectKSD); //KSD混合色
                update();
                return;
            }
        }
    }
}

//选择按钮
void Dialog::selectBtnClicked()
{
    emit sendColor(KSDToRGB(drawColorMixKSD));
}

//清除按钮
void Dialog::clearBtnClicked()
{
    drawColorMixKSD = KSDColor(ParamColor(), ParamColor(), 0);          //KSD混合色
    update();
}
