#include "goodsdialog.h"
#include "ui_goodsdialog.h"

goodsDialog::goodsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goodsDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_4_clicked();

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
}

goodsDialog::~goodsDialog()
{
    delete ui;
}

void goodsDialog::showEvent(QShowEvent *)
{
    on_pushButton_4_clicked();

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
}

void goodsDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/2.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void goodsDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select goodsid from goods");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into goods values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "')");

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void goodsDialog::on_pushButton_2_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from goods where goodsid = '" + idNum + "'");

    query.exec("insert into goods values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "')");

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");
}

void goodsDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());

    QMessageBox::information(NULL, "success", "delete success!");
}

void goodsDialog::on_pushButton_4_clicked()
{
    //刷新
    currentTableModel->setTable("goods");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
}

void goodsDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from goods where goodsid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->comboBox->setCurrentIndex(query.value(2).toInt());
        ui->dateEdit->setDate(QDate::fromString(query.value(3).toString(), "yyyy.MM.dd"));
    }
}
