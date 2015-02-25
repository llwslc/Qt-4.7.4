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
    int roleInt = ui->tabWidget->currentIndex();

    switch(roleInt)
    {
    case 0:
        currentView = ui->tableView;
        break;
    case 1:
        currentView = ui->tableView_2;
        break;
    case 2:
        currentView = ui->tableView_3;
        break;
    default:
        break;
    }

    currentTableModel->setTable("historyList");
    currentTableModel->setFilter("role = '" + QString::number(roleInt, 10) + "'");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(0);
    currentTableModel->setSort(1, Qt::AscendingOrder);
    currentTableModel->removeRows(8, currentTableModel->rowCount()-8);
    currentTableModel->select(); //选取整个表的所有行

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("时间(秒)"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void listDialog::on_tabWidget_currentChanged(int index)
{
    //选项卡改变
    int roleInt = ui->tabWidget->currentIndex();

    switch(roleInt)
    {
    case 0:
        currentView = ui->tableView;
        break;
    case 1:
        currentView = ui->tableView_2;
        break;
    case 2:
        currentView = ui->tableView_3;
        break;
    default:
        break;
    }

    currentTableModel->setTable("historyList");
    currentTableModel->setFilter("role = '" + QString::number(roleInt, 10) + "'");
    currentTableModel->removeColumn(3);
    currentTableModel->removeColumn(0);
    currentTableModel->setSort(1, Qt::AscendingOrder);
    currentTableModel->select(); //选取整个表的所有行

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("时间(秒)"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}
