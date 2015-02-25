#include "cashdialog.h"
#include "ui_cashdialog.h"

cashDialog::cashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cashDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_3_clicked();

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

cashDialog::~cashDialog()
{
    delete ui;
}

void cashDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select turnoverid from turnover");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into turnover values('" + QString::number(idNum, 10) + "', '"
               + ui->dateTimeEdit->dateTime().toString("yyyy.MM.dd hh:mm:ss") + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "')");

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void cashDialog::on_pushButton_2_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();

    QMessageBox::information(NULL, "success", "delete success!");
}

void cashDialog::on_pushButton_3_clicked()
{
    //刷新
    currentTableModel->setTable("turnover");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void cashDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from turnover where turnoverid = '" + idNum + "'");
    while(query.next())
    {
        ui->dateTimeEdit->setDateTime(QDateTime::fromString(query.value(1).toString(), "yyyy.MM.dd hh:mm:ss"));
        ui->lineEdit->setText(query.value(2).toString());
        ui->lineEdit_2->setText(query.value(3).toString());
    }
}

void cashDialog::updateTableModel()
{
    currentTableModel->select();
}

void cashDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/9.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
