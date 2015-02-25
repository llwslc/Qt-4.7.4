#ifndef ASSESSORDIALOG_H
#define ASSESSORDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class assessorDialog;
}

class assessorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit assessorDialog(QWidget *parent = 0);
    ~assessorDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

signals:
    void addAssessor();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_5_clicked();

private:
    Ui::assessorDialog *ui;
};

#endif // ASSESSORDIALOG_H
