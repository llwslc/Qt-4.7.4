#include "mycoursedialog.h"
#include "ui_mycoursedialog.h"

myCourseDialog::myCourseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myCourseDialog)
{
    ui->setupUi(this);
}

myCourseDialog::~myCourseDialog()
{
    delete ui;
}

void myCourseDialog::showEvent(QShowEvent *)
{
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(5);

    int i = 0;
    ui->tableWidget->setColumnWidth(i, 30);
    int tableWidth = (ui->tableWidget->width() - 30) / 7;
    int tableHeight = (ui->tableWidget->height() - 30) / 5;
    for(i=1; i<8; i++)
    {
        ui->tableWidget->setColumnWidth(i, tableWidth);
    }
    for(i=0; i<5; i++)
    {
        ui->tableWidget->setRowHeight(i, tableHeight);
    }

    QHeaderView* headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);

    QStringList header;
    header.append("");
    header.append("周一");
    header.append("周二");
    header.append("周三");
    header.append("周四");
    header.append("周五");
    header.append("周六");
    header.append("周末");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    i = 0;
    ui->tableWidget->setItem(i++, 0, new QTableWidgetItem("A"));
    ui->tableWidget->setItem(i++, 0, new QTableWidgetItem("B"));
    ui->tableWidget->setItem(i++, 0, new QTableWidgetItem("C"));
    ui->tableWidget->setItem(i++, 0, new QTableWidgetItem("D"));
    ui->tableWidget->setItem(i++, 0, new QTableWidgetItem("E"));

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void myCourseDialog::on_tableWidget_clicked(const QModelIndex &index)
{
    //列表点击
    QString courseName = QString("");
    QString colIndex = QString::number(ui->tableWidget->currentColumn(), 10);
    QString rowIndex = QString::number(ui->tableWidget->currentRow(), 10);

    QSqlQuery query;
    query.exec("select * from mynote where userid = '" + userid
               + "' and colindex = '" + colIndex
               + "' and rowindex = '" + rowIndex
               + "'");
    while(query.next())
    {
        courseName = query.value(2).toString();
    }

    ui->lineEdit->setText(courseName);
}

void myCourseDialog::on_pushButton_clicked()
{
    //修改
    QString colIndex = QString::number(ui->tableWidget->currentColumn(), 10);
    QString rowIndex = QString::number(ui->tableWidget->currentRow(), 10);

    QSqlQuery query;
    query.exec("delete from mynote where userid = '" + userid
               + "' and colindex = '" + colIndex
               + "' and rowindex = '" + rowIndex
               + "'");

    int idNum = 0;
    query.exec("select mynoteid from mynote");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }
    idNum++;

    query.exec("insert into mynote values('" + QString::number(idNum, 10) + "', '"
               + userid + "', '"
               + ui->lineEdit->text() + "', '"
               + colIndex + "', '"
               + rowIndex + "')");

    ui->lineEdit->clear();
}

void myCourseDialog::on_pushButton_2_clicked()
{
    //查询
    QSqlQuery query;

    query.exec("select * from students where schid = " + ui->lineEdit_2->text());
    if(query.next())
    {
        classid = query.value(3).toString();
    }
    else
    {
        QMessageBox::information(NULL, "error", "没有此学号!");
        return;
    }

    query.exec("select * from mycourse where classid = " + classid);
    while(query.next())
    {
        ui->tableWidget->setItem(query.value(4).toInt(), query.value(3).toInt()+1, new QTableWidgetItem(query.value(2).toString()));
    }
}
