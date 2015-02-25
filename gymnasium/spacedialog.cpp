#include "spacedialog.h"
#include "ui_spacedialog.h"

spaceDialog::spaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spaceDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlRelationalTableModel(this);
    currentView = ui->tableView;

    on_pushButton_3_clicked();

    QHeaderView* headerView = currentView->verticalHeader();
    headerView->setHidden(true); //隐藏行号
}

spaceDialog::~spaceDialog()
{
    delete ui;
}

void spaceDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/4.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void spaceDialog::showEvent(QShowEvent *)
{
    on_pushButton_3_clicked();
}

void spaceDialog::on_pushButton_clicked()
{
    //添加健身场地
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);
    currentTableModel->setData(currentTableModel->index(rowNum, 1), 0);

    ui->pushButton->setEnabled(false);
}

void spaceDialog::on_pushButton_2_clicked()
{
    //删除健身场地
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void spaceDialog::on_pushButton_3_clicked()
{
    //刷新当前
    currentTableModel->setTable("park");
    currentTableModel->setRelation(1, QSqlRelation("member", "memberid", "name"));
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setItemDelegate(new QSqlRelationalDelegate(currentView));

    ui->pushButton->setEnabled(true);
}

void spaceDialog::on_pushButton_4_clicked()
{
    //提交修改
    currentTableModel->submitAll();

    ui->pushButton->setEnabled(true);
}
