#ifndef LOGONDIALOG_H
#define LOGONDIALOG_H

#include "common.h"
#include "crackerdialog.h"
#include "maindialog.h"
#include "registerdialog.h"
#include "qfingerprint.h"

namespace Ui {
    class logonDialog;
}

class logonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit logonDialog(QWidget *parent = 0);
    ~logonDialog();

    void init();
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
    void initFingerTempMap();
    void findFingerUser(int mUserid);
    void keyPressEvent(QKeyEvent *);


private slots:
    void selfShow();

    void exitApp();

    void finishImageReceived();

    void finishFeatureInfo(int AQuality);

    void finishCapture(QVariant ATemplate);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    int crackerFlag;
    Ui::logonDialog *ui;
    qFingerprint *qFinger;
    crackerDialog crackerw;
    mainDialog mainw;
    registerDialog regw;
};

#endif // LOGONDIALOG_H
