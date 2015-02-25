#ifndef ORDERSDIALOG_H
#define ORDERSDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QtNetwork>
#include <QAbstractItemModel>

namespace Ui {
    class ordersDialog;
}

class ordersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ordersDialog(QWidget *parent = 0);
    ~ordersDialog();

    QNetworkAccessManager *networkAccessManager;

    QStandardItemModel *model;

    void showEvent(QShowEvent *);
    void paintEvent(QPaintEvent *);

    void initComboBox();

private slots:
    void Finish(QNetworkReply *);

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_4_clicked();

private:
    Ui::ordersDialog *ui;
};

#endif // ORDERSDIALOG_H
