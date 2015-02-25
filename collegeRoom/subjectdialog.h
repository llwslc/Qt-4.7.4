#ifndef SUBJECTDIALOG_H
#define SUBJECTDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class subjectDialog;
}

class subjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit subjectDialog(QWidget *parent = 0);
    ~subjectDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);
signals:
    void modifySub();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::subjectDialog *ui;
};

#endif // SUBJECTDIALOG_H
