#ifndef MEMBERDIALOG_H
#define MEMBERDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
class memberDialog;
}

class memberDialog : public QDialog
{
    Q_OBJECT

public:
    explicit memberDialog(QWidget *parent = 0);
    ~memberDialog();

    void paintEvent(QPaintEvent *);

    void showEvent(QShowEvent *);

signals:
    void addMoney();

private slots:
    void initComboBox();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::memberDialog *ui;
};

#endif // MEMBERDIALOG_H
