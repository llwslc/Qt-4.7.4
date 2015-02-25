#include "assessordialog.h"
#include "ui_assessordialog.h"

assessorDialog::assessorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::assessorDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_5_clicked();

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

assessorDialog::~assessorDialog()
{
    delete ui;
}

void assessorDialog::on_pushButton_4_clicked()
{
    //查询
    currentTableModel->setFilter("name like '%" + ui->lineEdit->text().trimmed() + "%'");
    currentTableModel->select();
}

void assessorDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select assessorid from assessor");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into assessor values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "')");

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");

    emit addAssessor();
}

void assessorDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    QMessageBox::information(NULL, "success", "delete success!");

    emit addAssessor();
}

void assessorDialog::on_pushButton_5_clicked()
{
    //刷新
    currentTableModel->setTable("assessor");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

void assessorDialog::on_pushButton_2_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from assessor where assessorid = '" + idNum + "'");


    query.exec("insert into assessor values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "')");

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");

    emit addAssessor();
}

void assessorDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from assessor where assessorid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->comboBox->setCurrentIndex(query.value(2).toInt());
        ui->lineEdit_2->setText(query.value(3).toString());
        ui->lineEdit_3->setText(query.value(4).toString());
    }
}

void assessorDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/10.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
