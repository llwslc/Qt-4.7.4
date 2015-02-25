#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include "common.h"
#include "qfingerprint.h"

namespace Ui {
    class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = 0);
    ~registerDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);

    void init();

signals:
    void OnClose();

private slots:

    void finishImageReceived();

    void finishFeatureInfo(int AQuality);

    void finishEnroll(QString ATemplate);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::registerDialog *ui;
    qFingerprint *qFinger;
    bool isLineToFinger;
};

#endif // REGISTERDIALOG_H
