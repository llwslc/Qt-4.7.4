#ifndef GOODSDIALOG_H
#define GOODSDIALOG_H

#include "common.h"
#include "qfingerprint.h"

namespace Ui {
    class goodsDialog;
}

class goodsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit goodsDialog(QWidget *parent = 0);
    ~goodsDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void init();
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
    void findFingerUser(int mUserid);

signals:
    void OnClose();
    void modGoods();

private slots:
    void finishImageReceived();

    void finishFeatureInfo(int AQuality);

    void finishCapture(QVariant ATemplate);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::goodsDialog *ui;
    qFingerprint *qFinger;
};

#endif // GOODSDIALOG_H
