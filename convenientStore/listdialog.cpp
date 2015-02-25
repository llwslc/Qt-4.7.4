#include "listdialog.h"
#include "ui_listdialog.h"

listDialog::listDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
}

listDialog::~listDialog()
{
    delete ui;
}

void listDialog::on_pushButton_clicked()
{
    this->close();
}

void listDialog::showEvent(QShowEvent *event)
{
    currentView = ui->tableView;

    currentTableModel->setTable("historyList");
    currentTableModel->removeColumn(0);
    currentTableModel->setSort(1, Qt::DescendingOrder);
    currentTableModel->removeRows(8, currentTableModel->rowCount()-8);
    currentTableModel->select(); //选取整个表的所有行

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("名字"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("分数"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}
