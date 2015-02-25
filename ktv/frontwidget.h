#ifndef FRONTWIDGET_H
#define FRONTWIDGET_H

#include <QWidget>
#include "function.h"
#include "logindialog.h"
#include "songtopdialog.h"

namespace Ui {
    class frontWidget;
}

class frontWidget : public QWidget
{
    Q_OBJECT

public:
    explicit frontWidget(QWidget *parent = 0);
    ~frontWidget();

    QSqlTableModel *currentTableModel_1;
    QTableView *currentView_1;
    QSqlTableModel *currentTableModel_2;
    QTableView *currentView_2;

    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;
    Phonon::VolumeSlider *volumeSlider;

    QTimer *timer;

    void paintEvent(QPaintEvent *);

    bool pauseFlag;

private slots:
    void returnShow();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void stateChanged(Phonon::State newState, Phonon::State oldState);

    void sourceChanged(const Phonon::MediaSource &source);

    void aboutToFinish();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::frontWidget *ui;
    loginDialog loginw;
    songTopDialog songTopw;
};

#endif // FRONTWIDGET_H
