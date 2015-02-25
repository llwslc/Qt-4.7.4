#ifndef STOCKMODDIALOG_H
#define STOCKMODDIALOG_H

#include "common.h"
#include "qfingerprint.h"

namespace Ui {
    class stockModDialog;
}

class stockModDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stockModDialog(QWidget *parent = 0);
    ~stockModDialog();

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

    void on_pushButton_2_clicked();

private:
    Ui::stockModDialog *ui;
    qFingerprint *qFinger;
};

#endif // STOCKMODDIALOG_H
