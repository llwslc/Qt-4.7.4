#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include "function.h"

namespace Ui {
class serverWidget;
}

class serverWidget : public QWidget
{
    Q_OBJECT

public:
    explicit serverWidget(QWidget *parent = 0);
    ~serverWidget();

    QSqlRelationalTableModel *currentTableModel;
    QTableView *currentView;

    void paintEvent(QPaintEvent *);

signals:
    void returnDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

private:
    Ui::serverWidget *ui;
};

#endif // SERVERWIDGET_H
