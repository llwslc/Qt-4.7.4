#include "memberaddialog.h"
#include "ui_memberaddialog.h"

memberadDialog::memberadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::memberadDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_clicked();

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();
}

memberadDialog::~memberadDialog()
{
    delete ui;
}

void memberadDialog::showEvent(QShowEvent *)
{
    on_pushButton_clicked();

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();

    initComboBox();
}

void memberadDialog::on_pushButton_4_clicked()
{
    //查询
    currentTableModel->setFilter("name like '%" + ui->lineEdit->text().trimmed() + "%'");
    currentTableModel->select();
}

void memberadDialog::on_pushButton_3_clicked()
{
    //添加
    QSqlQuery query;
     int idNum = 0;

     query.exec("select memberid from member");
     while(query.next())
     {
         if(idNum < query.value(0).toInt())
             idNum = query.value(0).toInt();
     }

     idNum++;

     query.exec("insert into member values('" + QString::number(idNum, 10) + "', '"
                + ui->lineEdit->text().trimmed() + "', '"
                + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
                + ui->lineEdit_2->text().trimmed() + "', '"
                + ui->comboBox_2->currentText() + "', '"
                + ui->lineEdit_3->text().trimmed() + "')");

     currentTableModel->select();
     QMessageBox::information(NULL, "add", "add success!");

     ui->lineEdit->clear();
     ui->comboBox->setCurrentIndex(0);
     ui->lineEdit_2->clear();
     ui->comboBox_2->setCurrentIndex(0);
     ui->lineEdit_3->clear();
}

void memberadDialog::on_pushButton_2_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();

    QMessageBox::information(NULL, "success", "delete success!");
}

void memberadDialog::on_pushButton_clicked()
{
    //刷新
    currentTableModel->setTable("member");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_3->clear();
}

void memberadDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from member where memberid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->comboBox->setCurrentIndex(query.value(2).toInt());
        ui->lineEdit_2->setText(query.value(3).toString());
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(query.value(4).toString()));
        ui->lineEdit_3->setText(query.value(5).toString());
    }
}

void memberadDialog::initComboBox()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("");

    query.exec("select name from assessor");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}

void memberadDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/7.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
