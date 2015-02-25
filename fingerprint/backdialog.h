#ifndef BACKDIALOG_H
#define BACKDIALOG_H

#include "common.h"
#include "qfingerprint.h"

namespace Ui {
    class backDialog;
}

class backDialog : public QDialog
{
    Q_OBJECT

public:
    explicit backDialog(QWidget *parent = 0);
    ~backDialog();

    int keeperid;
    int userid;

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void init();
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
    void findFingerUser(int mUserid);

    void roleCheckboxStatus();

    void getBorrowGoods();

    void delBorrowGoods();

signals:
    void OnClose();

private slots:
    void initGoods();

    void finishImageReceived();

    void finishFeatureInfo(int AQuality);

    void finishCapture(QVariant ATemplate);

    void on_pushButton_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::backDialog *ui;
    qFingerprint *qFinger;
};

#endif // BACKDIALOG_H
