#include "staffdialog.h"
#include "ui_staffdialog.h"

staffDialog::staffDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::staffDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_5->clear();

    on_pushButton_9_clicked();
}

staffDialog::~staffDialog()
{
    delete ui;
}

void staffDialog::on_pushButton_clicked()
{
    //工号查询
    currentTableModel->setFilter("staffid = '" + ui->lineEdit->text().trimmed() + "'");
    currentTableModel->select();
}

void staffDialog::on_pushButton_2_clicked()
{
    //姓名查询
    currentTableModel->setFilter("name like '%" + ui->lineEdit_2->text().trimmed() + "%'");
    currentTableModel->select();
}

void staffDialog::on_pushButton_3_clicked()
{
    //身份证查询
    currentTableModel->setFilter("idnum = '" + ui->lineEdit_3->text().trimmed() + "'");
    currentTableModel->select();
}

void staffDialog::on_pushButton_4_clicked()
{
    //职位查询
    currentTableModel->setFilter("post = '" + ui->lineEdit_4->text().trimmed() + "'");
    currentTableModel->select();
}

void staffDialog::on_pushButton_5_clicked()
{
    //入职时间查询
    currentTableModel->setFilter("date = '" + ui->dateEdit->date().toString("yyyy.MM.dd") + "'");
    currentTableModel->select();
}

void staffDialog::on_pushButton_6_clicked()
{
    //插图
    picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(picPath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + picPath);
    }

    ui->label->setScaledContents(true);
    ui->label->setPixmap(picPath);
}

void staffDialog::on_pushButton_10_clicked()
{
    //新增
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int idNum = 0;
    QSqlQuery query;
    query.exec("select staffid from staff");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    ui->lineEdit->setText(QString::number(idNum, 10));

    QString targetPath = "staff/" + QString::number(idNum, 10) + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), idNum);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), ui->lineEdit_2->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 2), ui->lineEdit_3->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 3), ui->lineEdit_4->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 4), ui->dateEdit->date().toString("yyyy.MM.dd"));
    currentTableModel->setData(currentTableModel->index(rowNum, 5), ui->lineEdit_5->text());
    currentTableModel->setData(currentTableModel->index(rowNum, 6), targetPath);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_5->clear();

    currentTableModel->submitAll();
}

void staffDialog::on_pushButton_7_clicked()
{
    //修改
    QString sql;
    QSqlQuery query;

    sql = "delete from staff where staffid = '" + ui->lineEdit->text() + "'";
    query.exec(sql);

    //复制图片
    QString targetPath = "staff/" + ui->lineEdit->text() + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    //插入数据库
    sql = "insert into staff values ('" +  ui->lineEdit->text()
            + "', '" + ui->lineEdit_2->text()
            + "', '" + ui->lineEdit_3->text()
            + "', '" + ui->lineEdit_4->text()
            + "', '" + ui->dateEdit->date().toString("yyyy.MM.dd")
            + "', '" + ui->lineEdit_5->text()
            + "', '" + targetPath
            + "')";
    qDebug() << sql << endl;
    query.exec(sql);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_5->clear();

    currentTableModel->submitAll();

    currentTableModel->select();
}

void staffDialog::on_pushButton_8_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_5->clear();
}

void staffDialog::on_pushButton_9_clicked()
{
    //刷新
    currentTableModel->setTable("staff");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEdit_5->clear();
}

void staffDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表点击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    ui->lineEdit->setText(currentTableModel->index(curRow, 0).data().toString());
    ui->lineEdit_2->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->lineEdit_3->setText(currentTableModel->index(curRow, 2).data().toString());
    ui->lineEdit_4->setText(currentTableModel->index(curRow, 3).data().toString());
    ui->dateEdit->setDate(QDate::fromString(currentTableModel->index(curRow, 4).data().toString(), "yyyy.MM.dd"));
    ui->lineEdit_5->setText(currentTableModel->index(curRow, 5).data().toString());
    picPath = currentTableModel->index(curRow, 6).data().toString();

    ui->label->setScaledContents(true);
    ui->label->setPixmap(picPath);
}
