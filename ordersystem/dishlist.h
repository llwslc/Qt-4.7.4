#ifndef DISHLIST_H
#define DISHLIST_H

#include <QDialog>
#include <QVector>
#include <QComboBox>
#include "dish.h"

namespace Ui {
class dishlist;
}

class dishlist : public QDialog
{
    Q_OBJECT

public:
    explicit dishlist(QWidget *parent = 0);
    dishlist(QVector<int> in_list,int deskno);
    ~dishlist();
    void set_list(QVector<int> in_list,int deskno);
    void show_list();
    QVector<int> get_list(){return list;}
    void save_Table();

private slots:
    void on_add_clicked();
    void push_but();
    void dish_change(int now);


    void on_pushButton_2_clicked();

private:
    Ui::dishlist *ui;
    QVector<int> list;
    QMap<int,dish> dish_map;
    int deskno;
    bool flag;

};

#endif // DISHLIST_H
