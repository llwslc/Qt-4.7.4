#ifndef STUDIALOG_H
#define STUDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
class stuDialog;
}

class stuDialog : public QDialog
{
    Q_OBJECT

public:
    explicit stuDialog(QWidget *parent = 0);
    ~stuDialog();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

    void showEvent(QShowEvent *);

    bool copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist);

    QString picPath;

signals:
    void modifyStu();

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::stuDialog *ui;
};

#endif // STUDIALOG_H
