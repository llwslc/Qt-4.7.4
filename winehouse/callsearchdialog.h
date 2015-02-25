#ifndef CALLSEARCHDIALOG_H
#define CALLSEARCHDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class callSearchDialog;
}

class callSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit callSearchDialog(QWidget *parent = 0);
    ~callSearchDialog();

    void showEvent(QShowEvent *);

private slots:
    void initDialog();

private:
    Ui::callSearchDialog *ui;
};

#endif // CALLSEARCHDIALOG_H
