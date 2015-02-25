#ifndef ADMINWIDGET_H
#define ADMINWIDGET_H

#include <QWidget>
#include "function.h"

namespace Ui {
class adminWidget;
}

class adminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit adminWidget(QWidget *parent = 0);
    ~adminWidget();

    QSqlTableModel *currentTableModel;
    QTableView *currentView;
    bool songOrMember;
    QString sourcePath;
    Phonon::MediaObject *metaInformationResolver;

    void paintEvent(QPaintEvent *);

signals:
    void returnDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void mataDataChanged();
    void on_pushButton_7_clicked();

private:
    Ui::adminWidget *ui;
};

#endif // ADMINWIDGET_H
