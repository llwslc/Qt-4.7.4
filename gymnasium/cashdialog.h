#ifndef CASHDIALOG_H
#define CASHDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class cashDialog;
}

class cashDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cashDialog(QWidget *parent = 0);
    ~cashDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

private slots:
    void updateTableModel();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::cashDialog *ui;
};

#endif // CASHDIALOG_H
