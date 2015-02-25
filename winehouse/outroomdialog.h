#ifndef OUTROOMDIALOG_H
#define OUTROOMDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class outroomDialog;
}

class outroomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit outroomDialog(QWidget *parent = 0);
    ~outroomDialog();

    void showEvent(QShowEvent *);

signals:
    void outRoom();

private slots:
    void initDialog();

    void on_pushButton_clicked();

private:
    Ui::outroomDialog *ui;
};

#endif // OUTROOMDIALOG_H
