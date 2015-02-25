#ifndef SONGTOPDIALOG_H
#define SONGTOPDIALOG_H

#include <QDialog>
#include "function.h"

namespace Ui {
    class songTopDialog;
}

class songTopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit songTopDialog(QWidget *parent = 0);
    ~songTopDialog();

    void paintEvent(QPaintEvent *);

    QSqlTableModel *currentTableModel;
    QTableView *currentView;

private:
    Ui::songTopDialog *ui;
};

#endif // SONGTOPDIALOG_H
