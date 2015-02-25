#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H
#include "cpgl.h"
#include "rygl.h"
#include <QDialog>

namespace Ui {
class adminDialog;
}

class adminDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit adminDialog(QWidget *parent = 0);
    ~adminDialog();
    
private slots:
    void on_pbcp_released();

    void on_pbry_released();

private:
    Ui::adminDialog *ui;
};

#endif // ADMINDIALOG_H
