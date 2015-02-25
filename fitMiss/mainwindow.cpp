#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    currentView = ui->tableView_3;

    foodItemUpdate();
    cookbookItemUpdate();
    sportsItemUpdate();

    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/png/bj2.png").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void mainWindow::on_pushButton_clicked()
{
    //食物库
    ui->tabWidget->setCurrentIndex(0);
}

void mainWindow::on_pushButton_2_clicked()
{
    //运动库
    ui->tabWidget->setCurrentIndex(2);
}

void mainWindow::on_pushButton_3_clicked()
{
    //记录饮食
    recDlg.show();
}

void mainWindow::on_pushButton_4_clicked()
{
    //记录运动
    recDlg.show();
}

void mainWindow::on_pushButton_6_clicked()
{
    //记录体重
    weiDlg.show();
}

void mainWindow::on_pushButton_5_clicked()
{
    //历史记录
    hisDlg.show();
}

void mainWindow::on_pushButton_7_clicked()
{
    //身体指数
    bmiDlg = new bmiDialog;
    bmiDlg->show();
}

void mainWindow::on_pushButton_8_clicked()
{
    //标准体重
    stdwDlg = new stdweightDialog;
    stdwDlg->show();
}

void mainWindow::on_pushButton_9_clicked()
{
    //最佳三维
    sizeDlg = new sizeDialog;
    sizeDlg->show();
}

void mainWindow::on_pushButton_10_clicked()
{
    //卡路里转公斤
    calDlg = new calorieDialog;
    calDlg->show();
}

void mainWindow::on_pushButton_11_clicked()
{
    //后台添加
    adminDlg.show();
}

void mainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
    //食物列表单击
    QString sortStr = ui->tableWidget->currentItem()->text();  //获得一条记录的一个属性的值
    qDebug() << sortStr << endl;

    currentTableModel->setTable("food");
    currentTableModel->setFilter("category = '" + sortStr + "'");
    currentTableModel->removeColumn(0); //取消主键的显示

    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void mainWindow::on_tableWidget_2_clicked(const QModelIndex &index)
{
    //食谱列表单击
    QString sortStr = ui->tableWidget_2->currentItem()->text();  //获得一条记录的一个属性的值

    currentTableModel->setTable("cookbook");
    currentTableModel->setFilter("category = '" + sortStr + "'");
    currentTableModel->removeColumn(0);

    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void mainWindow::on_tableWidget_4_clicked(const QModelIndex &index)
{
    //运动列表单击
    QString sortStr = ui->tableWidget_4->currentItem()->text();  //获得一条记录的一个属性的值

    currentTableModel->setTable("sports");
    currentTableModel->setFilter("category = '" + sortStr + "'");
    currentTableModel->removeColumn(0);

    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void mainWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    //右侧列表单击
    QString labelInfo;
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QModelIndex indexData = currentTableModel->index(curRow, 4);   //获得一条记录的一个属性的值
    labelInfo = "热量 : " + currentTableModel->index(curRow, 1).data().toString()
            + "千卡/100克\n\n指数 : " + currentTableModel->index(curRow, 2).data().toString()
            + "\n\n分类 : " + currentTableModel->index(curRow, 3).data().toString();

    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(indexData.data().toString()));

    ui->label_2->setText(currentTableModel->index(curRow, 1).data().toString());
    ui->label_3->setText(labelInfo);
}

void mainWindow::foodItemUpdate()
{
    //添加食物分类数据
    int i = 0;
    //设置一个较大的行号
    ui->tableWidget->setRowCount(100);

    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("谷类")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("薯类淀粉")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("干豆")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("蔬菜")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("菌藻")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("水果")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("坚果种子")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("畜肉")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("禽肉")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("乳类")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("蛋类")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("鱼虾蟹贝")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("婴幼儿食品")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("小吃甜饼")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("速食食品")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("软饮料")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("酒精饮料")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("糖蜜饯")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("油脂")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("调味品")));
    ui->tableWidget->setItem(i++,0,new QTableWidgetItem(QString("药食及其它")));

    //设置为正常的列
    ui->tableWidget->setRowCount(i);
    ui->tableWidget->setColumnWidth(0, ui->tableWidget->width());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    //去掉tableWidget自带的行号
    QHeaderView* headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);
}

void mainWindow::cookbookItemUpdate()
{
    //添加食谱分类数据
    int i = 0;
    ui->tableWidget_2->setRowCount(100);

    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("私家菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("家常菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("北京菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("天津菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("湖南菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("江苏菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("东北菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("山东菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("上海菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("清真菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("四川菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("福建菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("湖北菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("广州菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("浙江菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("河南菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("素斋菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("山西菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("陕西菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("甘肃菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("广东菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("安徽菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("江西菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("滇黔菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("台湾菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("海南菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("新疆菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("广西菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("宁夏菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("青海菜")));
    ui->tableWidget_2->setItem(i++,0,new QTableWidgetItem(QString("法国菜")));

    ui->tableWidget_2->setRowCount(i);
    ui->tableWidget_2->setColumnWidth(0, ui->tableWidget_2->width());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    QHeaderView* headerView = ui->tableWidget_2->verticalHeader();
    headerView->setHidden(true);
}
void mainWindow::sportsItemUpdate()
{
    //添加运动分类数据
    int i = 0;
    ui->tableWidget_4->setRowCount(100);

    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("休闲娱乐")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("走路")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("调节训练")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("舞蹈")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("自行车运动")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("水上运动")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("日常运动")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("工作")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("家务")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("园艺运动")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("其他")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("体育运动")));
    ui->tableWidget_4->setItem(i++,0,new QTableWidgetItem(QString("跑步")));

    ui->tableWidget_4->setRowCount(i);
    ui->tableWidget_4->setColumnWidth(0, ui->tableWidget_4->width());
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑

    QHeaderView* headerView = ui->tableWidget_4->verticalHeader();
    headerView->setHidden(true);
}

void mainWindow::on_pushButton_12_clicked()
{
    //修改密码
    pwdDlg.show();
}
