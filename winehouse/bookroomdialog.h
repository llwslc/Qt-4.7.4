#ifndef BOOKROOMDIALOG_H
#define BOOKROOMDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class bookroomDialog;
}

class bookroomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bookroomDialog(QWidget *parent = 0);
    ~bookroomDialog();

    void showEvent(QShowEvent *);

signals:
    void bookRoom();

private slots:
    void initDialog();

    void on_pushButton_clicked();

private:
    Ui::bookroomDialog *ui;
};

#endif // BOOKROOMDIALOG_H
