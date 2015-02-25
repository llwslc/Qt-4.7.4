#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
namespace Ui {
class logDialog;
}

class logDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit logDialog(QWidget *parent = 0);
    ~logDialog();
    
private slots:
    void on_pbcancel_clicked();
    void on_pblogin_clicked();

private:
    Ui::logDialog *ui;

};

#endif // LOGDIALOG_H
