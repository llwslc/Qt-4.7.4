#include "cpgl.h"
#include "ui_cpgl.h"
#include<qsqlrecord.h>
#include<qmessagebox.h>
#include<qdebug.h>
cpgl::cpgl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cpgl)
{
    ui->setupUi(this);
    model=new QSqlTableModel;
    model->setTable("dish");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"菜品编号");
    model->setHeaderData(1,Qt::Horizontal,"菜名");
    model->setHeaderData(2,Qt::Horizontal,"价格");
    ui->tv->setModel(model);
    ui->tv->setColumnWidth(0, 120);
    ui->tv->setColumnWidth(1, 163);
    ui->tv->setColumnWidth(2, 120);
    QPalette   palette;
    QPixmap pixmap("resource/4.jpg");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
}

cpgl::~cpgl()
{
    delete ui;
}

void cpgl::on_pbback_clicked()
{
    close();
}

void cpgl::on_pbdelete_clicked()
{
    int currentRow=ui->tv->currentIndex().row();
    model->removeRow(currentRow);
}

void cpgl::on_pbsave_clicked()
{
    model->database().transaction();
    if(model->submitAll())
        model->database().commit();
    else
        model->database().rollback();
}

void cpgl::on_pbadd_clicked()
{
    int row=model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row,0),model->rowCount());
    model->submitAll();
}

void cpgl::on_pbfind_clicked()
{
    QString str=ui->getvalue->text();
    str="dname like '%"+str+"%'";
    qDebug()<<str;
    model->setFilter(str);
    model->select();
}
