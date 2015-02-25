#ifndef CPGL_H
#define CPGL_H
#include<qsqlquerymodel.h>
#include<qsqltablemodel.h>
#include <QDialog>
namespace Ui {
class cpgl;
}

class cpgl : public QDialog
{
    Q_OBJECT
    
public:
    explicit cpgl(QWidget *parent = 0);
    ~cpgl();
    
private slots:
    void on_pbback_clicked();

    void on_pbdelete_clicked();

    void on_pbsave_clicked();

    void on_pbadd_clicked();

    void on_pbfind_clicked();
private:
    Ui::cpgl *ui;
    QSqlTableModel *model;
};

#endif // CPGL_H
