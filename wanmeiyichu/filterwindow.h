#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include <QDialog>
#include "common.h"
#include "createbutton.h"
#include "otherobject.h"

namespace Ui {
class filterWindow;
}

class filterWindow : public QDialog
{
    Q_OBJECT

public:
    explicit filterWindow(QWidget *parent = 0);
    ~filterWindow();

    QPoint windowPos;

    QPoint mousePos;

    QPoint dPos;

    void showEvent(QShowEvent *);

    void paintEvent(QPaintEvent *);

    void mousePressEvent(QMouseEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void closeEvent(QCloseEvent *);

signals:
    void modifyDaydress();

private slots:
    void exitButton_clicked();

    void filterListWidget_DoubleClicked(const QModelIndex &index);

private:
    Ui::filterWindow *ui;
};

#endif // FILTERWINDOW_H
