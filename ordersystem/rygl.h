#ifndef RYGL_H
#define RYGL_H
#include<qsqlquerymodel.h>
#include<qsqltablemodel.h>
#include <QDialog>

namespace Ui {
class rygl;
}

class rygl : public QDialog
{
    Q_OBJECT
    
public:
    explicit rygl(QWidget *parent = 0);
    ~rygl();
private slots:
    void on_pbback_clicked();

    void on_pbdelete_clicked();

    void on_pbsave_clicked();

    void on_pbadd_clicked();

    void on_pbfind_clicked();
private:
    Ui::rygl *ui;
    QSqlTableModel *model;
};

#endif // RYGL_H
