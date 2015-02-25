#ifndef QFINGERPRINT_H
#define QFINGERPRINT_H

#include "common.h"

class qFingerprint : public QObject
{
    Q_OBJECT
public:
    explicit qFingerprint(QObject *parent = 0);
    ~qFingerprint();

    int InitEngine();
    void EndEngine();
    void BeginEnroll();
    int EnrollIndex();
    bool IsRegister();
    void CancelEnroll();
    void SaveBitmap();
    QString EncodeTemplate(QVariant ATemplate);
    QVariant DecodeTemplate(QString UserZW);
    bool VerFinger(QVariant& FRegTemplate, QVariant ATemplate);


    QString SensorSN();
    int SensorIndex();
    int SensorCount();

signals:
    void OnImageReceived();
    void OnCapture(QVariant ATemplate);
    void OnEnroll(QString ATemplate);
    void OnFeatureInfo(int AQuality);


public slots:
    void finishImageReceived(bool& AImageValid);
    void finishCapture(bool ActionResult, QVariant ATemplate);
    void finishEnrool(bool ActionResult, QVariant ATemplate);
    void finishFeatureInfo(int AQuality);

private:
    QAxWidget* qFinger;

};

#endif // QFINGERPRINT_H
