#ifndef stockSelDialog_H
#define stockSelDialog_H

#include "common.h"
#include "qfingerprint.h"

namespace Ui {
    class stockSelDialog;
}

class stockSelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stockSelDialog(QWidget *parent = 0);
    ~stockSelDialog();

    QSqlTableModel *currentTableModel_1;
    QTableView *currentView_1;
    QSqlTableModel *currentTableModel_2;
    QTableView *currentView_2;
    QSqlTableModel *currentTableModel_3;
    QTableView *currentView_3;

    void init();
    void initPage1();
    void initPage2();
    void initPage3();
    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *);
    QString hideIdcard(QString idcard);
    QString showIdcard(QString idcard);

signals:
    void OnClose();

private slots:
    void on_checkBox_1_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_3_clicked();

    void on_lineEdit_1_textChanged(const QString &arg1);

    void on_tableWidget_1_clicked(const QModelIndex &index);

    void on_tableWidget_2_clicked(const QModelIndex &index);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_tableView_1_clicked(const QModelIndex &index);

    void on_tableView_2_clicked(const QModelIndex &index);

    void on_comboBox_1_currentIndexChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_tableWidget_3_clicked(const QModelIndex &index);

    void on_lineEdit_7_textChanged(const QString &arg1);

    void on_lineEdit_8_textChanged(const QString &arg1);

    void on_lineEdit_9_textChanged(const QString &arg1);

    void on_lineEdit_10_textChanged(const QString &arg1);

    void on_tableView_3_clicked(const QModelIndex &index);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_tableWidget_4_clicked(const QModelIndex &index);

private:
    Ui::stockSelDialog *ui;
    qFingerprint *qFinger;
};

#endif // stockSelDialog_H
