#include "booksearchdialog.h"
#include "ui_booksearchdialog.h"

bookSearchDialog::bookSearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookSearchDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("books");
    currentTableModel->setSort(0, Qt::AscendingOrder);
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("名称"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("图书编号"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("出版社"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("作者"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("类型"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("入库时间"));
    currentTableModel->setHeaderData(7, Qt::Horizontal, QObject::tr("当前状态"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

bookSearchDialog::~bookSearchDialog()
{
    delete ui;
}

void bookSearchDialog::showEvent(QShowEvent *)
{
    //显示窗口
    currentTableModel->setTable("books");
    currentTableModel->setSort(0, Qt::AscendingOrder);
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("名称"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("图书编号"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("出版社"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("作者"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("类型"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("入库时间"));
    currentTableModel->setHeaderData(7, Qt::Horizontal, QObject::tr("当前状态"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

void bookSearchDialog::on_pushButton_clicked()
{
    //书名搜索
    currentTableModel->setFilter("name like '%" + ui->lineEdit_6->text().trimmed() + "%'");
    currentTableModel->select();
}

void bookSearchDialog::on_pushButton_3_clicked()
{
    //作者搜索
    currentTableModel->setFilter("aurhor like '%" + ui->lineEdit_8->text().trimmed() + "%'");
    currentTableModel->select();
}

void bookSearchDialog::on_pushButton_2_clicked()
{
    //编号搜索
    currentTableModel->setFilter("bookcode like '%" + ui->lineEdit_7->text().trimmed() + "%'");
    currentTableModel->select();
}

void bookSearchDialog::on_pushButton_4_clicked()
{
    //类型搜索
    currentTableModel->setFilter("type like '%" + ui->lineEdit_9->text().trimmed() + "%'");
    currentTableModel->select();
}

void bookSearchDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from books where booksid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_2->setText(query.value(2).toString());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->lineEdit_4->setText(query.value(4).toString());
        ui->lineEdit_5->setText(query.value(5).toString());
        ui->dateEdit->setDate(QDate::fromString(query.value(6).toString(), "yyyy.MM.dd"));
        ui->comboBox->setCurrentIndex(query.value(7).toInt());
    }
}
