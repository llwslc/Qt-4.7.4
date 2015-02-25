#ifndef CLOTHESWINDOW_H
#define CLOTHESWINDOW_H

#include <QDialog>
#include "common.h"
#include "createbutton.h"
#include "otherobject.h"

namespace Ui {
    class clothesWindow;
}

class clothesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit clothesWindow(QWidget *parent = 0);
    ~clothesWindow();

    QPoint windowPos;

    QPoint mousePos;

    QPoint dPos;

    void showEvent(QShowEvent *);

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void closeEvent(QCloseEvent *);

signals:
    void modifyClothes();

private slots:
    void picButton_clicked();

    void modifyButton_clicked();

    void cancelButton_clicked();

private:
    Ui::clothesWindow *ui;
};

#endif // CLOTHWINDOW_H
