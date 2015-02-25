#include "turnoversystem.h"
#include "ui_turnoversystem.h"

turnoverSystem::turnoverSystem(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::turnoverSystem)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    currentView = ui->tableView;

    currentTableModel->setTable("turnover");
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    ui->label->clear();
    ui->label_2->clear();

    ui->dateEdit_2->setDateTime(QDateTime::currentDateTime()); //设置为当前时间

    ui->lcdNumber->display(0);
}

turnoverSystem::~turnoverSystem()
{
    delete ui;
}

void turnoverSystem::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    QString sql;
    QSqlQuery query;
    QString labelInfo;
    QString picPath;
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QModelIndex indexData = currentTableModel->index(curRow, 3);   //获得一条记录的一个属性的值

    sql = "select * from depot where dname = '" + indexData.data().toString() + "'";  //在仓库表中查找

    qDebug() << sql << endl;
    query.exec(sql);
    do
    {
        labelInfo = " 商品名称 : " + query.value(1).toString()
                + "\n\n 商品单价 : " + query.value(2).toString()
                + "\n\n 剩余个数 : " + query.value(3).toString();
        picPath = query.value(4).toString();

        qDebug() << labelInfo << endl;
        qDebug() << picPath << endl;
    }while(query.next());

    ui->label->setScaledContents(true);
    ui->label->setPixmap(picPath);

    ui->label_2->setText(labelInfo);
}

void turnoverSystem::on_pushButton_clicked()
{
    //查询
    QDateTime preDate =  ui->dateEdit->dateTime();
    QDateTime nextDate =  ui->dateEdit_2->dateTime();

    if(preDate > nextDate)
    {
        QMessageBox::warning(this,tr("Warning"),tr("preDate > nextDate!"),QMessageBox::Yes);
        ui->dateEdit->setDateTime(nextDate); //设置为后一个时间
        ui->lcdNumber->display(0);
        return;
    }

    QString dateSql;
    QSqlQuery queryDate;
    int turnoverSum = 0;

    currentTableModel->setFilter("turnoverdate >= '" + preDate.toString("yyyy.MM.dd")
                                 + "' and turnoverdate <= '" + nextDate.toString("yyyy.MM.dd") + "'");
    currentTableModel->select();

    dateSql = "select tprice from turnover where turnoverdate >= '" + preDate.toString("yyyy.MM.dd")
            + "' and turnoverdate <= '" + nextDate.toString("yyyy.MM.dd") + "'";
    queryDate.exec(dateSql);

    while(queryDate.next())
    {
        turnoverSum += queryDate.value(0).toInt();
    }

    qDebug() << turnoverSum << endl;

    ui->lcdNumber->display(turnoverSum);
}

void turnoverSystem::paintEvent(QPaintEvent *)
{
    //背景图片
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/5.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
