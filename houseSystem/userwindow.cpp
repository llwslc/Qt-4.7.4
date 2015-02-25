#include "userwindow.h"
#include "ui_userwindow.h"

userWindow::userWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userWindow)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    //刷新楼盘
    on_pushButton_4_clicked();
}

userWindow::~userWindow()
{
    delete ui;
}

void userWindow::on_pushButton_clicked()
{
    //上一张
    if (picCol <= 3)
    {
        picCol = 7;
    }
    else
    {
        picCol--;
    }
    QModelIndex indexData = currentTableModel->index(picRow, picCol);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));
}

void userWindow::on_pushButton_4_clicked()
{
    //刷新
    currentView = ui->tableView;

    currentTableModel->setTable("houses");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label->clear();
}

void userWindow::on_pushButton_2_clicked()
{
    //下一张
    if (picCol < 3)
    {
        picCol = 4;
    }
    else if (picCol >= 7)
    {
        picCol = 3;
    }
    else
    {
        picCol++;
    }
    QModelIndex indexData = currentTableModel->index(picRow, picCol);   //获得一条记录的一个属性的值
    qDebug() << indexData.data() << endl;

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));
}

void userWindow::on_pushButton_3_clicked()
{
    //密码修改
    QString name;
    QString sPwd;
    QString tPwd;
    QString sql;
    QSqlQuery query;

    name = ui->lineEdit->text().trimmed();
    sPwd = ui->lineEdit_2->text().trimmed();
    tPwd = ui->lineEdit_3->text().trimmed();

    sql = "select * from person where pname = '" + name
            + "' and passwd = '"+ sPwd + "' and role = 1";

    query.exec(sql);
    if (query.next())
    {
        sql = "update person set passwd = '" + tPwd + "' where pname = '" + name + "' and role = 1";
        query.exec(sql);
        QMessageBox::warning(this,tr("Success"),tr("successfully Modify!"), QMessageBox::Yes);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"), QMessageBox::Yes);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
    }
}

void userWindow::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    picCol = currentView->currentIndex().column(); //获取选中的列
    picRow = currentView->currentIndex().row(); //获取选中的行

    QModelIndex indexData = currentTableModel->index(picRow, 3);   //获得一条记录的一个属性的值

    if (picCol < 3)
    {
        indexData = currentTableModel->index(picRow, 3);   //获得一条记录的一个属性的值
    }
    else
    {
        indexData = currentTableModel->index(picRow, picCol);   //获得一条记录的一个属性的值
    }
    qDebug() << indexData.data() << endl;

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));
}

void userWindow::on_pushButton_5_clicked()
{
    //留言板
    messagew.show();
}

void userWindow::on_pushButton_6_clicked()
{
    //退出登录
    this->hide();
    emit closeWindows();
}
