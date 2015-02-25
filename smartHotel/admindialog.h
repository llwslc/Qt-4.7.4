#ifndef ADMINDIALOG_H
#define ADMINDIALOG_H

#include <QDialog>
#include "common.h"
#include "adminusersdialog.h"
#include "adminguestsdialog.h"
#include "adminroomsdialog.h"
#include "adminorderdialog.h"

namespace Ui {
    class adminDialog;
}

class adminDialog : public QDialog
{
    Q_OBJECT

public:
    explicit adminDialog(QWidget *parent = 0);
    ~adminDialog();

    adminUsersDialog userw;
    adminGuestsDialog guestw;
    adminRoomsDialog roomw;
    adminOrderDialog orderw;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::adminDialog *ui;
};

#endif // ADMINDIALOG_H
