#ifndef MEMBERADDIALOG_H
#define MEMBERADDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class memberadDialog;
}

class memberadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit memberadDialog(QWidget *parent = 0);
    ~memberadDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

    void showEvent(QShowEvent *);

private slots:
    void initComboBox();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::memberadDialog *ui;
};

#endif // MEMBERADDIALOG_H
