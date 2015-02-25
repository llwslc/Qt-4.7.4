#include "rygl.h"
#include "ui_rygl.h"
#include<qsqlrecord.h>
#include<qmessagebox.h>
#include<qdebug.h>
rygl::rygl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rygl)
{
    ui->setupUi(this);
    model=new QSqlTableModel;
    model->setTable("person");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"Ô±¹¤ºÅ");
    model->setHeaderData(1,Qt::Horizontal,"ÐÕÃû");
    model->setHeaderData(2,Qt::Horizontal,"µÇÂ¼ÃÜÂë");
    model->setHeaderData(3,Qt::Horizontal,"½ÇÉ«");
    ui->tv->setModel(model);
    ui->tv->setColumnWidth(0, 80);
    ui->tv->setColumnWidth(1, 163);
    ui->tv->setColumnWidth(2, 120);
    ui->tv->setColumnWidth(3, 40);
    QPalette   palette;
    QPixmap pixmap("resource/5.jpg");
    palette.setBrush(backgroundRole(),QBrush(pixmap));
    setPalette(palette);
}

rygl::~rygl()
{
    delete ui;
}
void rygl::on_pbback_clicked()
{
    close();
}

void rygl::on_pbdelete_clicked()
{
    int currentRow=ui->tv->currentIndex().row();
    model->removeRow(currentRow);
}

void rygl::on_pbsave_clicked()
{
    model->database().transaction();
    if(model->submitAll())
        model->database().commit();
    else
        model->database().rollback();
}

void rygl::on_pbadd_clicked()
{
    int row=model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row,0),model->rowCount());
    model->submitAll();
}

void rygl::on_pbfind_clicked()
{
    QString str=ui->getvalue->text();
    str="pname like '%"+str+"%'";
    qDebug()<<str;
    model->setFilter(str);
    model->select();
}
