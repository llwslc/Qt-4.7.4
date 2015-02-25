#ifndef PUNCHDIALOG_H
#define PUNCHDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class punchDialog;
}

class punchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit punchDialog(QWidget *parent = 0);
    ~punchDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

private slots:
    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::punchDialog *ui;
};

#endif // PUNCHDIALOG_H
