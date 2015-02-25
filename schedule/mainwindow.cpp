#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    updateTableDay();
    on_pushButton_clicked(); //全部
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *)
{
    on_pushButton_clicked();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bk.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::on_pushButton_6_clicked()
{
    //新增
    windowsPos = this->QWidget::pos(); //获取窗口位置
    this->hide();

    itemDelButtonFlag = false;
    itemw = new itemWindow;
    itemw->move(windowsPos);   //将新窗口位置调整至和原来一样
    itemw->show();
    itemw->exec();

    this->move(windowsPos);
    this->show();
    currentTableModel->select(); //选取整个表的所有行,此处相当于刷新
}

void MainWindow::on_pushButton_clicked()
{
    //全部
    currentView = ui->tableView;

    currentTableModel->setTable("day");

    currentTableModel->removeColumn(3);  //消去第四列
    currentTableModel->removeColumn(0);  //消去第一列


    int ruleInt;
    QString sql;
    QSqlQuery query;

    sql = "select rule from orderoption where orderoptionid = '1'";
    query.exec(sql);
    while(query.next())
    {
        ruleInt = query.value(0).toInt();
    }
    if(ruleInt == 1) //按照剩余天数排列
    {
        currentTableModel->setSort(1, Qt::AscendingOrder);
    }

    currentTableModel->select(); //选取整个表的所有行


    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void MainWindow::on_pushButton_2_clicked()
{
    //纪念日
    currentTableModel->setFilter("sort = '0'");
}

void MainWindow::on_pushButton_3_clicked()
{
    //工作
    currentTableModel->setFilter("sort = '1'");
}

void MainWindow::on_pushButton_4_clicked()
{
    //生活
    currentTableModel->setFilter("sort = '2'");
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    //双击列表
    windowsPos = this->QWidget::pos(); //获取窗口位置
    this->hide();

    int curRow = currentView->currentIndex().row(); //获取选中的行
    QModelIndex indexData = currentTableModel->index(curRow, 0);   //获得一条记录的一个属性的值
    viewTitle = indexData.data().toString();

    itemDelButtonFlag = true;
    itemw = new itemWindow;
    itemw->move(windowsPos);   //将新窗口位置调整至和原来一样
    itemw->show();
    itemw->exec();

    this->move(windowsPos);
    this->show();
    currentTableModel->select(); //选取整个表的所有行,此处相当于刷新
}

void MainWindow::updateTableDay()
{
    //更新倒计时天数
    QString titleStr; //标题
    QString dateStr;  //日期
    int dittoInt;     //重复

    QSqlQuery query;

    int curId = 0;
    int totalNum = 0;
    int dayResult = 0;

    query.exec("select dayid from day");
    while(query.next())
        totalNum++;
    qDebug() << "totalNum = " << totalNum;

    do
    {
        query.exec("select title from day where dayid = '" + QString::number(curId, 10) + "'");
        while(query.next())
            titleStr = query.value(0).toString();

        query.exec("select data, ditto from note where title = '" + titleStr + "'");
        while(query.next())
        {
            dateStr = query.value(0).toString();
            dittoInt = query.value(1).toInt();
        }

        dayResult = datedef(dateStr, dittoInt);
        query.exec("update day set daynum = '" + QString::number(dayResult, 10) + "' where dayid = '" + QString::number(curId, 10) + "'");

        curId++;

        qDebug() << "curId = " << curId;
        qDebug() << "titleStr = " << titleStr;
        qDebug() << "dateStr = " << dateStr;
        qDebug() << "dittoInt = " << dittoInt;
        qDebug() << "dayResult = " << dayResult;
    }while(curId != totalNum+1);
}
