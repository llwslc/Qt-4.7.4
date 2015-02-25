#ifndef BOOKSEARCHDIALOG_H
#define BOOKSEARCHDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
class bookSearchDialog;
}

class bookSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit bookSearchDialog(QWidget *parent = 0);
    ~bookSearchDialog();

    void showEvent(QShowEvent *);

private slots:
    void initDialog();

private:
    Ui::bookSearchDialog *ui;
};

#endif // BOOKSEARCHDIALOG_H
