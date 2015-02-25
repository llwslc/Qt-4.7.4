#include "qfingerprint.h"

qFingerprint::qFingerprint(QObject *parent) :
    QObject(parent)
{
    /*
     QT中使用ActiveX控件、QAxBase、QAxWidget
     http://blog.163.com/lijiji_1515/blog/static/1268774462009921961893/

     http://blog.csdn.net/tszhangjunqiao/article/details/16946953

     http://blog.csdn.net/goodowxy/article/details/4294568

     */

    qFinger = new QAxWidget;

    qFinger->setControl(QString::fromUtf8("{CA69969C-2F27-41D3-954D-A48B941C3BA7}"));
    qFinger->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    qFinger->setObjectName(QString::fromUtf8("ZKFPEngXControl"));

    connect(qFinger, SIGNAL(OnImageReceived(bool&)), this, SLOT(finishImageReceived(bool&)));
    connect(qFinger, SIGNAL(OnCapture(bool, QVariant)), this, SLOT(finishCapture(bool, QVariant)));
    connect(qFinger, SIGNAL(OnEnroll(bool, QVariant)), this, SLOT(finishEnrool(bool, QVariant)));
    connect(qFinger, SIGNAL(OnFeatureInfo(int)), this, SLOT(finishFeatureInfo(int)));
}

qFingerprint::~qFingerprint()
{
    delete qFinger;
}

//初始化设备
int qFingerprint::InitEngine()
{
    // 0 初始化成功
    // 1 指纹识别驱动程序加载失败
    // 2 没有连接指纹识别仪
    // 3 属性SensorIndex指定的指纹仪不存在（注意：在调用之前设置属性SensorIndex）
    // 调试的时候 qFinger->dynamicCall("InitEngine()"); 会报错 原因未知
    int result = -1;
    QList<QVariant> params;

    params << qFinger->dynamicCall("InitEngine()");
    result = params[0].value<int>();

    return result;
}

//关闭设备
void qFingerprint::EndEngine()
{
    qFinger->dynamicCall("EndEngine()");
}

//开始登记指纹
void qFingerprint::BeginEnroll()
{
    qFinger->dynamicCall("BeginEnroll()");
}

//还需登记次数
int qFingerprint::EnrollIndex()
{
    int result = -1;
    QList<QVariant> params;

    params << qFinger->dynamicCall("EnrollIndex");
    result = params[0].value<int>();

    return result;
}

//是否正在登记
bool qFingerprint::IsRegister()
{
    bool result = false;
    QList<QVariant> params;

    params << qFinger->dynamicCall("IsRegister");
    result = params[0].value<bool>();

    return result;
}

//关闭登记指纹
void qFingerprint::CancelEnroll()
{
    qFinger->dynamicCall("CancelEnroll()");
}

//保存指纹图像
void qFingerprint::SaveBitmap()
{
    QList<QVariant> params;
    params << fingerBmpPath;

   qFinger->dynamicCall("SaveBitmap(QString)", params);
}

//计算指纹特征码
QString qFingerprint::EncodeTemplate(QVariant ATemplate)
{
    QString result = "false";
    QList<QVariant> params;

    params << qFinger->dynamicCall("EncodeTemplate1(QVariant)", ATemplate);
    result = params[0].value<QString>();

    return result;
}

//指纹特征码转换
QVariant qFingerprint::DecodeTemplate(QString UserZW)
{
    QVariant result = "false";
    QList<QVariant> params;

    params << qFinger->dynamicCall("DecodeTemplate1(QString)", UserZW);
    result = params[0];

    return result;
}

//计算是否匹配
bool qFingerprint::VerFinger(QVariant& FRegTemplate, QVariant ATemplate)
{
    bool result = false;
    bool ADoLearning = true;
    bool RegChanged = true;

    QList<QVariant> params;

    params << qFinger->dynamicCall("VerFinger(QVariant&, QVariant, bool, bool&) ", FRegTemplate, ATemplate, ADoLearning, RegChanged);
    result = params[0].value<bool>();

    return result;
}

//获取指纹仪器序列号
QString qFingerprint::SensorSN()
{
    QString result = "";
    QList<QVariant> params;

    params << qFinger->dynamicCall("SensorSN()");
    result = params[0].value<QString>();

    return result;
}

//当前指纹仪器索引
int qFingerprint::SensorIndex()
{
    int result = -1;
    QList<QVariant> params;

    params << qFinger->dynamicCall("SensorIndex()");
    result = params[0].value<int>();

    return result;
}

//获取指纹仪器个数
int qFingerprint::SensorCount()
{
    int result = -1;
    QList<QVariant> params;

    params << qFinger->dynamicCall("SensorCount()");
    result = params[0].value<int>();

    return result;
}

//图片接收完成
void qFingerprint::finishImageReceived(bool& AImageValid)
{
    /*
        设备取到指纹图像或者通过AddImageFile和AddBitmap加入指纹图像时调用该事件
        AImageValid表示是否进行模板提取
        设置为False后,系统在取到指纹图像后返回,不进行模板提取。
    */
    emit OnImageReceived();
}

void qFingerprint::finishCapture(bool ActionResult, QVariant ATemplate)
{
    /*
        ActionResult = True 表示成功取到指纹模版, False 表示失败.
    */
    if(ActionResult)
    {
        emit OnCapture(ATemplate);
    }
}

//登记完成
void qFingerprint::finishEnrool(bool ActionResult, QVariant ATemplate)
{
    /*
        BeginEnroll() 开始登记
        CancelEnroll() 结束登记

        一般三次之后完成登记,得到特征模板
        用户登记指纹结束时调用该事件, ActionResult =true 表示成功登记,
        QByteArray 用ATemplate属性可取得指纹特征模版, False 表示失败。
    */
    QString result = "false";
    if(ActionResult == true)
    {
        result = this->EncodeTemplate(ATemplate);
    }
    emit OnEnroll(result);
}

//指纹信息完成
void qFingerprint::finishFeatureInfo(int AQuality)
{
    /*
        取得指纹初始特征，Quality表示该指纹特征的质量，有如下可能值：OnFeatureInfo(AQuality As Long)
        0: 好的指纹特征
        1: 特征点不够
        2: 其它原因导致不能取到指纹特征
    */
    emit OnFeatureInfo(AQuality);
}

