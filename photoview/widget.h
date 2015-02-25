#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QStringList>
#include <QString>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QMatrix>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    void setBtnIcon(QToolButton *Btn,const QString &path_image);
    QTimer *timer;
    QLabel *label;
    QPixmap pix;
    QMatrix matrix;

private slots:
    void on_Open_clicked();
    void displayImage();

    void on_start_clicked();

    void on_stop_clicked();

    void on_previous_clicked();

    void on_next_clicked();

    void on_big_clicked();

    void on_litte_clicked();

    void on_nromal_clicked();

    void on_recover_clicked();

    void on_zhuan_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
