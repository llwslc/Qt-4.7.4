#ifndef INROOMDIALOG_H
#define INROOMDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
class inroomDialog;
}

class inroomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit inroomDialog(QWidget *parent = 0);
    ~inroomDialog();

    void showEvent(QShowEvent *);

signals:
    void inRoom();

private slots:
    void initDialog();

    void on_pushButton_clicked();

private:
    Ui::inroomDialog *ui;
};

#endif // INROOMDIALOG_H
