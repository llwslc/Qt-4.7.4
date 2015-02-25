#ifndef INCOMEDIALOG_H
#define INCOMEDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class incomeDialog;
}

class incomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit incomeDialog(QWidget *parent = 0);
    ~incomeDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

signals:
    void modifyCheckIn();

private slots:
    void initDialog();

    void on_pushButton_clicked();

private:
    Ui::incomeDialog *ui;
};

#endif // INCOMEDIALOG_H
