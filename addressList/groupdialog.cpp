#include "groupdialog.h"
#include "ui_groupdialog.h"

groupDialog::groupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::groupDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("mygroup");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("名称"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
}

groupDialog::~groupDialog()
{
    delete ui;
}

void groupDialog::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    //painter.drawPixmap(0, 0, QPixmap(":/jpg/5.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void groupDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select mygroupid from mygroup");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into mygroup values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "')");

    ui->lineEdit->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");

    emit addGroup();
}

void groupDialog::on_pushButton_2_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();

    QMessageBox::information(NULL, "success", "delete success!");

    emit addGroup();
}

void groupDialog::on_pushButton_3_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from mygroup where mygroupid = '" + idNum + "'");

    query.exec("insert into mygroup values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "')");

    ui->lineEdit->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");

    emit addGroup();
}

void groupDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from mygroup where mygroupid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
    }
}
