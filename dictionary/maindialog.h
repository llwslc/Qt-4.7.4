#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include "common.h"
#include "userdialog.h"


namespace Ui {
    class mainDialog;
}

class mainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit mainDialog(QWidget *parent = 0);
    ~mainDialog();

    QNetworkAccessManager *networkAccessManager;

    QSqlTableModel *dictionTableModel;
    QTableView *dictionView;

    QSqlTableModel *myWordTableModel;
    QTableView *myWordView;

    QString myWordString;

    userDialog userw;

    void showEvent(QShowEvent *);

private slots:
    void Finish(QNetworkReply *);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::mainDialog *ui;
};

#endif // MAINDIALOG_H
