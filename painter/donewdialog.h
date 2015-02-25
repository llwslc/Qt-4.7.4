#ifndef DONEWDIALOG_H
#define DONEWDIALOG_H
#include <QColorDialog>
#include <QDialog>
#include "ui_donewdialog.h"
class DoNewDialog : public QDialog {
    Q_OBJECT
public:
    DoNewDialog(QWidget *parent = 0,Qt::WFlags flags = 0);
    ~DoNewDialog();
    int getWidth();
    int getHeight();
    QColor getBackColor();
protected:
    void changeEvent(QEvent *e);
private:
    Ui::DoNewDialogClass *ui;
    QColor backColor;
private slots:
    void on_toolButton_clicked();
    bool on_buttonBox_clicked();
};


#endif // DONEWDIALOG_H
