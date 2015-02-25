#ifndef ROOMDIALOG_H
#define ROOMDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
class roomDialog;
}

class roomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit roomDialog(QWidget *parent = 0);
    ~roomDialog();

    QSqlRelationalTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

signals:
    void modifyRoom();

private slots:
    void updateRoom();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::roomDialog *ui;
};

#endif // ROOMDIALOG_H
