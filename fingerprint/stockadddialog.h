#ifndef STOCKADDDIALOG_H
#define STOCKADDDIALOG_H

#include "common.h"
#include "qfingerprint.h"

namespace Ui {
    class stockAddDialog;
}

class stockAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stockAddDialog(QWidget *parent = 0);
    ~stockAddDialog();

    int buyerid;
    int keeperid;
    int leaderid;

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void init();
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
    void findFingerUser(int mUserid);

    void roleCheckboxStatus();

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
    Ui::stockAddDialog *ui;
    qFingerprint *qFinger;
};

#endif // STOCKADDDIALOG_H
