#include "adminwindow.h"
#include "ui_adminwindow.h"

adminWindow::adminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminWindow)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);

    tabViews.append(ui->adDishesTabView);
    tabViews.append(ui->adPeopleTabView);
    tabViews.append(ui->adOrderTabView);
    tabViews.append(ui->adDayTabView);
    tabViews.append(ui->adMonthTabView);
    tabViews.append(ui->adDateTabView);

    sqlNames.append("dish");
    sqlNames.append("person");
    sqlNames.append("orderform");
    sqlNames.append("orderform");
    sqlNames.append("orderform");
    sqlNames.append("orderform");

    on_adSelButton_clicked();
}

adminWindow::~adminWindow()
{
    delete ui;
}
void adminWindow::on_adDishesAction_triggered()
{
    //菜品管理
    ui->tabWidget->setCurrentIndex(0);   //将光标转到菜单管理选项卡
    on_adSelButton_clicked();
}

void adminWindow::on_adPeopleAction_triggered()
{
    //人员管理
    ui->tabWidget->setCurrentIndex(1);   //将光标转到人员管理选项卡
    on_adSelButton_clicked();
}

void adminWindow::on_adOrderAction_triggered()
{
    //订单管理
    ui->tabWidget->setCurrentIndex(2);   //将光标转到订单管理选项卡
    on_adSelButton_clicked();
}

void adminWindow::on_adDayAction_triggered()
{
    //当日营业额
    ui->tabWidget->setCurrentIndex(3);   //将光标转到当日营业额管理选项卡
    on_adSelButton_clicked();
}

void adminWindow::on_adMonthAction_triggered()
{
    //当月营业额
    ui->tabWidget->setCurrentIndex(4);   //将光标转到当月营业额管理选项卡
    on_adSelButton_clicked();
}

void adminWindow::on_adDateAction_triggered()
{
    //按日期统计
    ui->tabWidget->setCurrentIndex(5);   //将光标转到按日期统计管理选项卡
    on_adSelButton_clicked();
}

void adminWindow::on_adPwdAction_triggered()
{
    //修改密码
}

void adminWindow::on_adCancelAction_triggered()
{
    //退出
    this->close();
}

void adminWindow::on_adAddButton_clicked()
{
    //添加数据
    int rowNum = currentTableModel->rowCount(); //获得表的行数
    int id = currentTableModel->record(rowNum - 1).value(0).toInt() + 1;

    currentView->setEditTriggers(QAbstractItemView::AllEditTriggers);  //使其可编辑
    currentTableModel->insertRow(rowNum); //添加一行
    currentTableModel->setData(currentTableModel->index(rowNum, 0), id);
}

void adminWindow::on_adDelButton_clicked()
{
    //删除数据
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行
}

void adminWindow::on_adChButton_clicked()
{
    //修改数据
    currentView->setEditTriggers(QAbstractItemView::DoubleClicked);  //使其可编辑
}

void adminWindow::on_adSubButton_clicked()
{
    //提交数据
    currentTableModel->submitAll();

    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void adminWindow::on_adSelButton_clicked()
{
    //刷新数据
    currentIndexNum = ui->tabWidget->currentIndex();

    sqlName = sqlNames.at(currentIndexNum);
    currentView = tabViews.at(currentIndexNum);

    currentTableModel->setTable(sqlName);

    qDebug() << sqlName << endl;

    currentTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    QString currentDate;
    if (3 == currentIndexNum)
    {
        currentDate = QDate::currentDate().toString("dd.MM.yyyy");

        currentTableModel->setFilter("date = '" + currentDate + "'");

        int tempMoneySum = 0;
        QString sql;
        QSqlQuery query;

        sql = "select income from orderform where date = '" + currentDate + "'";
        query.exec(sql);

        while(query.next())
        {
            tempMoneySum += query.value(0).toInt();
        }

        sql = QString::number(tempMoneySum, 10);
        ui->adDaySumLab->setText("总计 : " + sql + " 元");
    }
    else if (4 == currentIndexNum)
    {
        currentDate = QDate::currentDate().toString("MM.yyyy");

        currentTableModel->setFilter("date like '%" + currentDate + "'");

        int tempMoneySum = 0;
        QString sql;
        QSqlQuery query;

        sql = "select income from orderform where date like '%" + currentDate + "'";
        query.exec(sql);
        while(query.next())
        {
            tempMoneySum += query.value(0).toInt();
        }

        sql = QString::number(tempMoneySum, 10);
        ui->adMonthSumLab->setText("总计 : " + sql + " 元");
    }
    else if (5 == currentIndexNum)
    {
        int tempMoneySum = 0;
        QString sql;
        QSqlQuery query;

        sql = "select income from orderform";
        query.exec(sql);
        while(query.next())
        {
            tempMoneySum += query.value(0).toInt();
        }

        sql = QString::number(tempMoneySum, 10);
        ui->adDateSumLab->setText("总计 : " + sql + " 元");
    }
    else
    {
        qDebug() << "test" << endl;
    }
    currentTableModel->select(); //选取整个表的所有行

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
}

void adminWindow::on_adPwdButton_clicked()
{
    //修改密码
    QString name;
    QString sPwd;
    QString tPwd1;
    QString tPwd2;
    QString sql;
    QSqlQuery query;

    name = ui->adNameEdit->text().trimmed();
    sPwd = ui->adPwd1Edit->text().trimmed();
    tPwd1 = ui->adPwd2Edit->text().trimmed();
    tPwd2 = ui->adPwd3Edit->text().trimmed();

    sql = "select * from person where pname = '" + name
          + "' and passwd = '"+ sPwd + "' and role = 0";

    query.exec(sql);
    if (query.next())
    {
        if (tPwd1 == tPwd2)
        {
            sql = "update person set passwd = '" + tPwd1 + "' where pname = '" + name + "' and role = 0";
            query.exec(sql);
            QMessageBox::warning(this,tr("Success"),tr("successfully Modify!"), QMessageBox::Yes);

            ui->adNameEdit->clear();
            ui->adPwd1Edit->clear();
            ui->adPwd2Edit->clear();
            ui->adPwd3Edit->clear();
            ui->adNameEdit->setFocus();
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("Second password is not suit the first!"), QMessageBox::Yes);

            ui->adNameEdit->clear();
            ui->adPwd1Edit->clear();
            ui->adPwd2Edit->clear();
            ui->adPwd3Edit->clear();
            ui->adNameEdit->setFocus();
        }
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"), QMessageBox::Yes);

        ui->adNameEdit->clear();
        ui->adPwd1Edit->clear();
        ui->adPwd2Edit->clear();
        ui->adPwd3Edit->clear();
        ui->adNameEdit->setFocus();
    }
}

void adminWindow::on_tabWidget_currentChanged(int index)
{
    //切换选项卡
    on_adSelButton_clicked();
}
