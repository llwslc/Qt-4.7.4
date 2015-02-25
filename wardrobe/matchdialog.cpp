#include "matchdialog.h"
#include "ui_matchdialog.h"

matchDialog::matchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matchDialog)
{
    ui->setupUi(this);

    currentTableModel_1 = new QSqlTableModel(this);
    currentTableModel_2 = new QSqlTableModel(this);
    currentView_1 = ui->tableView;
    currentView_2 = ui->tableView_2;

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->textEdit->clear();

    currentTableModel_1->setTable("clothes");
    currentTableModel_1->setSort(0, Qt::AscendingOrder);
    currentTableModel_1->select(); //选取整个表的所有行
    currentView_1->setModel(currentTableModel_1);
    currentView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    currentTableModel_2->setTable("matchclothes");
    currentTableModel_2->setSort(0, Qt::AscendingOrder);
    currentTableModel_2->setFilter("data ='" + ui->dateEdit_2->dateTime().toString("yyyy.MM.dd") + "'");
    currentTableModel_2->select(); //选取整个表的所有行
    currentView_2->setModel(currentTableModel_2);
    currentView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    //   on_pushButton_2_clicked();
}

matchDialog::~matchDialog()
{
    delete ui;
}

void matchDialog::on_pushButton_4_clicked()
{
    //查询
    if(ui->lineEdit_6->text().trimmed() == "")
    {
        currentTableModel_1->setFilter("type ='" + QString::number(ui->comboBox->currentIndex(), 10) + "' and "
                                       + "season ='" + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
                                       + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "'");
        currentTableModel_1->select();
    }
    else
    {
        currentTableModel_1->setFilter("type ='" + QString::number(ui->comboBox->currentIndex(), 10) + "' and "
                                       + "season ='" + QString::number(ui->comboBox_2->currentIndex(), 10) + "' and "
                                       + "classtype ='" + QString::number(ui->comboBox_3->currentIndex(), 10) + "' and "
                                       + "name like '%" + ui->lineEdit_6->text().trimmed() + "%'");
        currentTableModel_1->select();
    }
}

void matchDialog::on_pushButton_2_clicked()
{
    //无类别查询
    if(ui->lineEdit_6->text().trimmed() == "")
    {
        currentTableModel_1->setTable("clothes");
        currentTableModel_1->setSort(0, Qt::AscendingOrder);
        currentTableModel_1->select(); //选取整个表的所有行
    }
    else
    {
        currentTableModel_1->setTable("clothes");
        currentTableModel_1->setSort(0, Qt::AscendingOrder);
        currentTableModel_1->setFilter("name like '%" + ui->lineEdit_6->text().trimmed() + "%'");
        currentTableModel_1->select();
    }
}

void matchDialog::on_pushButton_clicked()
{
    //添加
    int rowNum = currentTableModel_2->rowCount(); //获得表的行数
    int idNum = 0;
    QSqlQuery query;
    query.exec("select matchclothesid from matchclothes");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    QString targetPath = "matchclothes/" + QString::number(idNum, 10) + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    currentTableModel_2->insertRow(rowNum); //添加一行
    currentTableModel_2->setData(currentTableModel_2->index(rowNum, 0), idNum);
    currentTableModel_2->setData(currentTableModel_2->index(rowNum, 1), ui->lineEdit->text());
    currentTableModel_2->setData(currentTableModel_2->index(rowNum, 2), ui->comboBox->currentIndex());
    currentTableModel_2->setData(currentTableModel_2->index(rowNum, 3), ui->comboBox_2->currentIndex());
    currentTableModel_2->setData(currentTableModel_2->index(rowNum, 4), ui->comboBox_3->currentIndex());
    currentTableModel_2->setData(currentTableModel_2->index(rowNum, 5), ui->dateEdit_2->date().toString("yyyy.MM.dd"));
    currentTableModel_2->setData(currentTableModel_2->index(rowNum, 6), targetPath);

    currentTableModel_2->submitAll();
}

void matchDialog::on_tableView_clicked(const QModelIndex &index)
{
    //上侧列表单击
    int curRow = currentView_1->currentIndex().row(); //获取选中的行
    ui->lineEdit->setText(currentTableModel_1->index(curRow, 1).data().toString());
    ui->comboBox->setCurrentIndex(currentTableModel_1->index(curRow, 2).data().toInt());
    ui->comboBox_2->setCurrentIndex(currentTableModel_1->index(curRow, 3).data().toInt());
    ui->comboBox_3->setCurrentIndex(currentTableModel_1->index(curRow, 4).data().toInt());
    ui->lineEdit_2->setText(currentTableModel_1->index(curRow, 5).data().toString());
    ui->lineEdit_3->setText(currentTableModel_1->index(curRow, 6).data().toString());
    ui->dateEdit->setDate(QDate::fromString(currentTableModel_1->index(curRow, 7).data().toString(), "yyyy.MM.dd"));
    ui->lineEdit_4->setText(currentTableModel_1->index(curRow, 8).data().toString());
    ui->lineEdit_5->setText(currentTableModel_1->index(curRow, 9).data().toString());
    ui->textEdit->setPlainText(currentTableModel_1->index(curRow, 10).data().toString());
    picPath = currentTableModel_1->index(curRow, 11).data().toString();

    ui->label->setScaledContents(true);
    ui->label->setPixmap(picPath);
}

void matchDialog::on_tableView_2_clicked(const QModelIndex &index)
{
    //下侧列表单击
    QSqlQuery query;
    int curRow = currentView_2->currentIndex().row(); //获取选中的行
    query.exec("select * from clothes where name = '" + currentTableModel_2->index(curRow, 1).data().toString()
               + "' and type = '" + currentTableModel_2->index(curRow, 2).data().toString()
               + "' and season = '" + currentTableModel_2->index(curRow, 3).data().toString()
               + "' and classtype = '" + currentTableModel_2->index(curRow, 4).data().toString()
               + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->comboBox->setCurrentIndex(query.value(2).toInt());
        ui->comboBox_2->setCurrentIndex(query.value(3).toInt());
        ui->comboBox_3->setCurrentIndex(query.value(4).toInt());
        ui->lineEdit_2->setText(query.value(5).toString());
        ui->lineEdit_3->setText(query.value(6).toString());
        ui->dateEdit->setDate(QDate::fromString(query.value(7).toString(), "yyyy.MM.dd"));
        ui->lineEdit_4->setText(query.value(8).toString());
        ui->lineEdit_5->setText(query.value(9).toString());
        ui->textEdit->setPlainText(query.value(10).toString());
        picPath = query.value(11).toString();
    }

    ui->label->setScaledContents(true);
    ui->label->setPixmap(picPath);
}

void matchDialog::on_dateEdit_2_dateChanged(const QDate &date)
{
    //日期改变
    currentTableModel_2->setFilter("data ='" + ui->dateEdit_2->dateTime().toString("yyyy.MM.dd") + "'");
    currentTableModel_2->select(); //选取整个表的所有行
}


void matchDialog::on_pushButton_3_clicked()
{
    //退出
    this->close();
}

void matchDialog::on_label_2_linkActivated(const QString &link)
{

}
