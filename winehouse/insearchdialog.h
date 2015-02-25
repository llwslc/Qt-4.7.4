#ifndef INSEARCHDIALOG_H
#define INSEARCHDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QtDebug>
#include <QtSql>
#include <QList>
#include <QDateTime>
#include <QTextCodec>
#include <QAbstractItemModel>

namespace Ui {
    class inSearchDialog;
}

class inSearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit inSearchDialog(QWidget *parent = 0);
    ~inSearchDialog();

    void showEvent(QShowEvent *);

private slots:
    void initDialog();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::inSearchDialog *ui;
};

#endif // INSEARCHDIALOG_H
