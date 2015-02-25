#include "dishlist.h"
#include "ui_dishlist.h"
#include <QDebug>
#include <QMap>
#include <QSqlQuery>
#include <QPushButton>
#include <QTableWidgetItem>
#include <QMessageBox>

dishlist::dishlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dishlist)
{
    ui->setupUi(this);
    QPalette   palette;
    QPixmap pixmap("resource/3.jpg");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
    QSqlQuery query;
    query.exec("select *from dish");
    int i=1;
    while(query.next())
    {
        QString name=query.value(1).toString();
        dish d(query.value(0).toInt(),name,
               query.value(2).toInt());
        dish_map.insert(i,d);
        i++;
    }
    //connect(this,SIGNAL(rejected()))
}

dishlist::~dishlist()
{
    delete ui;
}

void dishlist::show_list()
{
    ui->desknum->display(deskno);
    ui->table->setColumnCount(4);
    QStringList headers;
    headers<<"菜的ID"<<"菜名"<<"价格"<<"删除";
    ui->table->setHorizontalHeaderLabels(headers);
    ui->table->verticalHeader()->setVisible(false);

    for(int i=0;i<list.size();i++)
    {
        ui->table->insertRow(ui->table->rowCount());
        QComboBox *bo=new QComboBox();
        QMap<int,dish>::Iterator it=dish_map.begin();
        while(it!=dish_map.end())
        {
            dish d=it.value();
            bo->addItem(d.get_name());
            it++;
        }
        bo->setCurrentIndex(list.at(i));
        connect(bo,SIGNAL(currentIndexChanged(int)),this,SLOT(dish_change(int)));
        ui->table->setCellWidget(i,1,bo);

        dish d=dish_map.value(list.at(i));
        QString price=QString::number(d.get_price(),10);
        QString id=QString::number(d.get_id(),10);
        ui->table->setItem(i,0,new QTableWidgetItem(id));
        ui->table->setItem(i,2,new QTableWidgetItem(price));
        QPushButton *but=new QPushButton();
        but->setText("删除");
        ui->table->setCellWidget(i,3,but);
        connect(but,SIGNAL(clicked()),this,SLOT(push_but()));
    }
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void dishlist::push_but()
{
    int cur_r=ui->table->currentRow();
    ui->table->removeRow(cur_r);
    ui->table->setCurrentCell(0,0);
    ui->table->setFocus(Qt::OtherFocusReason);
}

void dishlist::set_list(QVector<int> in_list,int in_deskno)
{
    this->list=in_list;
    this->deskno=in_deskno;
    show_list();
}

void dishlist::dish_change(int now)
{

    int now_row=ui->table->currentRow();
    dish d=dish_map.value(now+1);
    QString id=QString::number(d.get_id(),10);
    QString price=QString::number(d.get_price(),10);
    ui->table->setItem(now_row,0,new QTableWidgetItem(id));
    ui->table->setItem(now_row,2,new QTableWidgetItem(price));
    ui->table->setCurrentCell(0,0);
    ui->table->setFocus(Qt::OtherFocusReason);
}

//加菜
void dishlist::on_add_clicked()
{
    ui->table->insertRow(ui->table->rowCount());
    int i=ui->table->rowCount()-1;
    QComboBox *bo=new QComboBox();
    QMap<int,dish>::Iterator it=dish_map.begin();
    while(it!=dish_map.end())
    {
        dish d=it.value();
        bo->addItem(d.get_name());
        it++;
    }
    connect(bo,SIGNAL(currentIndexChanged(int)),this,SLOT(dish_change(int)));
    ui->table->setCellWidget(i,1,bo);
    dish d=dish_map.value(1);
    QString price=QString::number(d.get_price(),10);
    QString id=QString::number(d.get_id(),10);
    ui->table->setItem(i,0,new QTableWidgetItem(id));
    ui->table->setItem(i,2,new QTableWidgetItem(price));
    QPushButton *but=new QPushButton();
    but->setText("删除");
    ui->table->setCellWidget(i,3,but);
    connect(but,SIGNAL(clicked()),this,SLOT(push_but()));
    ui->table->setCurrentCell(0,0);
    ui->table->setFocus(Qt::OtherFocusReason);

}
void dishlist::save_Table()
{
    //读取表-保存表到list中
    this->list.clear();
    int rows=ui->table->rowCount();
    for(int i=0;i<rows;i++)
    {
        QString id=ui->table->item(i,0)->text();
        list.append(id.toInt());
    }
}
//结账
void dishlist::on_pushButton_2_clicked()
{
    flag=true;
    int sum=0;
    for(int i=0;i<ui->table->rowCount();i++)
    {
        QString id=ui->table->item(i,0)->text();
        dish d=dish_map.value(id.toInt());
        sum+=d.get_price();
    }
    QString msum=QString::number(sum,10);
    QMessageBox::information(this,"","应支付\t"+msum+"\t元",QMessageBox::Ok);
}
