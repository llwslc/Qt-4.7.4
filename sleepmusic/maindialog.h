#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "myfunc.h"
#include "musicDialog.h"
#include "picDialog.h"
#include "messagedialog.h"
#include "picshowdialog.h"

namespace Ui {
class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    Phonon::SeekSlider *seekSlider;
    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
    Phonon::VolumeSlider *volumeSlider;
    QToolBar *bar;
    QLCDNumber *timeLcd;

    QAction *playAction;
    QAction *pauseAction;
    QAction *stopAction;

    QTimer *timer;

    void musicPlay();
    void picShow();

    bool musicFlag;

    int musicTick;

    bool tryListen;
    int tryMusicTick;

    void paintEvent(QPaintEvent *);

private slots:
    void stateChanged(Phonon::State newState, Phonon::State oldState);

    void tick(qint64 time);

    void sourceChanged(const Phonon::MediaSource &source);

    void aboutToFinish();

    void checkTimeOut();

    void initComboBox();

    void on_pushButton_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_timeEdit_2_timeChanged(const QTime &date);

    void on_pushButton_10_clicked();

private:
    Ui::mainDialog *ui;
    musicDialog musicw;
    picDialog picw;
    messageDialog msgw;
    picShowDialog picDia;
};

#endif // MAINDIALOG_H
