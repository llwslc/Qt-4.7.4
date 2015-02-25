#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "common.h"
#include "createbutton.h"
#include "otherobject.h"
#include "clotheswindow.h"
#include "filterwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    clothesWindow clothesw;
    filterWindow filterw;

    QTimer *updateTimeTimer;
    QTimer *isOnlineTimer;

    QPoint windowPos;
    QPoint mousePos;
    QPoint dPos;

    QNetworkAccessManager *ipNetworkAccessManager;
    QNetworkAccessManager *placeNetworkAccessManager;
    QNetworkAccessManager *weatherNetworkAccessManager;

    void showEvent(QShowEvent *);

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void insertDayDressList();

    void closeEvent(QCloseEvent *);

private slots:

    void updateTime();

    void isOnlineTest();

    void ipNetworkReplyFinish(QNetworkReply *);

    void placeNetworkReplyFinish(QNetworkReply *);

    void weatherNetworkReplyFinish(QNetworkReply *);

    void myclothesButton_clicked();

    void fashionButton_clicked();

    void daydressButton_clicked();

    void settingButton_clicked();

    void clothesButton_clicked();

    void bagButton_clicked();

    void shoeButton_clicked();

    void decoButton_clicked();

    void cosButton_clicked();

    void labelButton_clicked();

    void springButton_clicked();

    void summerButton_clicked();

    void autumnButton_clicked();

    void winterButton_clicked();

    void workplaceButton_clicked();

    void banquetButton_clicked();

    void leisureButton_clicked();

    void sportButton_clicked();

    void otherButton_clicked();

    void addButton_clicked();

    void delButton_clicked();

    void secondLayerButton_clicked();

    void clothesListWidget_DoubleClicked(const QModelIndex &index);

    void daydressListWidget_update();

    void daydressListWidget_Clicked(const QModelIndex &index);

    void daydressListWidget_DoubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
