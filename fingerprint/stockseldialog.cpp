#include "stockseldialog.h"
#include "ui_stockseldialog.h"

stockSelDialog::stockSelDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stockSelDialog)
{
    ui->setupUi(this);

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    this->setWindowTitle("查询库存管理");

    currentTableModel_1 = new QSqlTableModel(this);
    currentView_1 = ui->tableView_1;

    currentTableModel_2 = new QSqlTableModel(this);
    currentView_2 = ui->tableView_2;

    currentTableModel_3 = new QSqlTableModel(this);
    currentView_3 = ui->tableView_3;

    init();
}

stockSelDialog::~stockSelDialog()
{
    delete ui;
}

void stockSelDialog::showEvent(QShowEvent *)
{
    init();
}

void stockSelDialog::paintEvent(QPaintEvent *)
{}

void stockSelDialog::closeEvent(QCloseEvent *)
{
    emit OnClose();
}

void stockSelDialog::init()
{
    //初始化
    initPage1();
    initPage2();
    initPage3();

    ui->checkBox_1->setChecked(true);
    this->resize(740, 600);
}

void stockSelDialog::initPage1()
{
    //初始化物品库存查询页面
    ui->tableWidget_1->setColumnCount(0);
    ui->tableWidget_1->setRowCount(0);
    ui->tableWidget_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_1->setColumnCount(3);
    int tableWidth_1 = (ui->tableWidget_1->width() - 20 - 20) / 3;
    ui->tableWidget_1->setColumnWidth(0, tableWidth_1);
    ui->tableWidget_1->setColumnWidth(1, tableWidth_1);
    ui->tableWidget_1->setColumnWidth(2, tableWidth_1);
    QStringList header_1;
    header_1.append("物品名称");
    header_1.append("库存总数");
    header_1.append("借出总数");
    ui->tableWidget_1->setHorizontalHeaderLabels(header_1);

    ui->tableWidget_2->setColumnCount(0);
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setColumnCount(4);
    int tableWidth_2 = (ui->tableWidget_2->width() - 20 - 20) / 3;
    ui->tableWidget_2->setColumnWidth(0, 0);
    ui->tableWidget_2->setColumnWidth(1, tableWidth_2);
    ui->tableWidget_2->setColumnWidth(2, tableWidth_2);
    ui->tableWidget_2->setColumnWidth(3, tableWidth_2);
    QStringList header_2;
    header_2.append("编号");
    header_2.append("物品名称");
    header_2.append("员工姓名");
    header_2.append("已借总数");
    ui->tableWidget_2->setHorizontalHeaderLabels(header_2);

    ui->lineEdit_1->clear();
    on_lineEdit_1_textChanged("");
    ui->comboBox_10->clear();
}

void stockSelDialog::initPage2()
{
    //初始化物品借还记录页面
    QSqlQuery query;

    currentTableModel_1->setTable("goods");
    currentTableModel_1->select();
    currentTableModel_1->removeColumn(0);
    currentTableModel_1->setHeaderData(0, Qt::Horizontal, QString("名称"));
    currentView_1->setModel(currentTableModel_1);
    currentView_1->setColumnWidth(0, currentView_1->width());
    currentView_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView_1 = currentView_1->verticalHeader();
    headerView_1->setHidden(true);

    currentTableModel_2->setTable("users");
    currentTableModel_2->setFilter("role = " + QString::number(STAFF_ROLE, 10));
    currentTableModel_2->select();
    currentTableModel_2->removeColumn(0);
    currentTableModel_2->removeColumn(1);
    currentTableModel_2->removeColumn(1);
    currentTableModel_2->removeColumn(1);
    currentTableModel_2->setHeaderData(0, Qt::Horizontal, QString("姓名"));
    currentView_2->setModel(currentTableModel_2);
    currentView_2->setColumnWidth(0, currentView_2->width());
    currentView_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView_2 = currentView_2->verticalHeader();
    headerView_2->setHidden(true);

    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->comboBox_1->clear();
    ui->comboBox_1->addItem("");
    ui->comboBox_5->clear();
    ui->comboBox_5->addItem("");
    ui->comboBox_6->clear();
    ui->comboBox_6->addItem("");
    query.exec("select username from users where role = " + QString::number(KEEPER_ROLE, 10));
    while(query.next())
    {
        ui->comboBox_1->addItem(query.value(0).toString());
    }
    ui->comboBox_1->setCurrentIndex(0);
    ui->dateEdit_1->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->checkBox_4->setChecked(true);
    ui->checkBox_5->setChecked(true);

    ui->tableWidget_3->setColumnCount(0);
    ui->tableWidget_3->setRowCount(0);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setColumnCount(7);
    int tableWidth_3 = (ui->tableWidget_3->width() - 20 - 20) / 6;
    ui->tableWidget_3->setColumnWidth(0, 0);
    ui->tableWidget_3->setColumnWidth(1, tableWidth_3);
    ui->tableWidget_3->setColumnWidth(2, tableWidth_3 - 10);
    ui->tableWidget_3->setColumnWidth(3, tableWidth_3 + 10);
    ui->tableWidget_3->setColumnWidth(4, tableWidth_3);
    ui->tableWidget_3->setColumnWidth(5, tableWidth_3);
    ui->tableWidget_3->setColumnWidth(6, tableWidth_3);
    QStringList header_3;
    header_3.append("编号");
    header_3.append("物品名称");
    header_3.append("物品个数");
    header_3.append("操作日期");
    header_3.append("保管人");
    header_3.append("领取人");
    header_3.append("借还");
    ui->tableWidget_3->setHorizontalHeaderLabels(header_3);
}

void stockSelDialog::initPage3()
{
    //初始化物品库存记录页面
    QSqlQuery query;

    currentTableModel_3->setTable("goods");
    currentTableModel_3->select();
    currentTableModel_3->removeColumn(0);
    currentTableModel_3->setHeaderData(0, Qt::Horizontal, QString("名称"));
    currentView_3->setModel(currentTableModel_3);
    currentView_3->setColumnWidth(0, currentView_3->width());
    currentView_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QHeaderView* headerView_3 = currentView_3->verticalHeader();
    headerView_3->setHidden(true);

    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("");
    ui->comboBox_7->clear();
    ui->comboBox_7->addItem("");
    query.exec("select username from users where role = " + QString::number(BUYER_ROLE, 10));
    while(query.next())
    {
        ui->comboBox_2->addItem(query.value(0).toString());
    }
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_9->clear();
    ui->comboBox_3->clear();
    ui->comboBox_3->addItem("");
    ui->comboBox_8->clear();
    ui->comboBox_8->addItem("");
    query.exec("select username from users where role = " + QString::number(KEEPER_ROLE, 10));
    while(query.next())
    {
        ui->comboBox_3->addItem(query.value(0).toString());
    }
    ui->comboBox_3->setCurrentIndex(0);
    ui->lineEdit_10->clear();
    ui->comboBox_4->clear();
    ui->comboBox_4->addItem("");
    ui->comboBox_9->clear();
    ui->comboBox_9->addItem("");
    query.exec("select username from users where role = " + QString::number(LEADER_ROLE, 10));
    while(query.next())
    {
        ui->comboBox_4->addItem(query.value(0).toString());
    }
    ui->comboBox_4->setCurrentIndex(0);
    ui->dateEdit_3->setDate(QDate::currentDate());
    ui->dateEdit_4->setDate(QDate::currentDate());
    ui->checkBox_6->setChecked(true);
    ui->checkBox_7->setChecked(true);

    ui->tableWidget_4->setColumnCount(0);
    ui->tableWidget_4->setRowCount(0);
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_4->setColumnCount(7);
    int tableWidth_4 = (ui->tableWidget_4->width() - 20 - 20) / 6;
    ui->tableWidget_4->setColumnWidth(0, 0);
    ui->tableWidget_4->setColumnWidth(1, tableWidth_4);
    ui->tableWidget_4->setColumnWidth(2, tableWidth_4);
    ui->tableWidget_4->setColumnWidth(3, tableWidth_4);
    ui->tableWidget_4->setColumnWidth(4, tableWidth_4);
    ui->tableWidget_4->setColumnWidth(5, tableWidth_4);
    ui->tableWidget_4->setColumnWidth(6, tableWidth_4);
    QStringList header_4;
    header_4.append("编号");
    header_4.append("物品名称");
    header_4.append("物品个数");
    header_4.append("操作日期");
    header_4.append("采购人");
    header_4.append("保管人");
    header_4.append("主管人");
    ui->tableWidget_4->setHorizontalHeaderLabels(header_4);
}

QString stockSelDialog::hideIdcard(QString idcard)
{
    //隐藏身份证号码
    int length = ((idcard.length() - 4)>0) ? (idcard.length() - 4) : 0;
    QString resIdcard = "";
    for(int i=0; i<length; i++)
    {
        resIdcard = resIdcard + "*";
    }
    resIdcard = resIdcard + idcard.right(4);

    return resIdcard;
}

QString stockSelDialog::showIdcard(QString idcard)
{
    //显示身份证号码
    QString resIdcard = "";
    resIdcard = idcard.right(4);

    return resIdcard;
}

void stockSelDialog::on_checkBox_1_clicked()
{
    //物品库存查询
    this->resize(740, 600);
    ui->stackedWidget->setCurrentIndex(0);
}

void stockSelDialog::on_checkBox_2_clicked()
{
    //物品借还记录
    this->resize(990, 600);
    ui->stackedWidget->setCurrentIndex(1);
}

void stockSelDialog::on_checkBox_3_clicked()
{
    //物品库存记录
    this->resize(860, 600);
    ui->stackedWidget->setCurrentIndex(2);
}

void stockSelDialog::on_lineEdit_1_textChanged(const QString &arg1)
{
    //物品库存查询物品搜索
    QSqlQuery query;
    QString sql;

    int currentRow = 0;
    QList<QString> goodsidList;
    QList<QString> gnameList;

    sql = "select goodsid, gname from goods where gname like '%" + arg1 + "%'";
    query.exec(sql);
    while(query.next())
    {
        goodsidList << query.value(0).toString();
        gnameList << query.value(1).toString();
    }

    ui->tableWidget_1->setRowCount(0);
    for(int i=0; i<goodsidList.count(); i++)
    {
        QTableWidgetItem *gnameItem = new QTableWidgetItem(QTableWidgetItem::Type);
        QTableWidgetItem *numItem = new QTableWidgetItem(QTableWidgetItem::Type);
        QTableWidgetItem *borrownumItem = new QTableWidgetItem(QTableWidgetItem::Type);
        gnameItem->setText(gnameList[i]);
        numItem->setText("0");
        borrownumItem->setText("0");

        sql = "select * from stocks where goodsid = '" + goodsidList[i] + "'";
        query.exec(sql);
        while(query.next())
        {
            numItem->setText(query.value(2).toString());
            borrownumItem->setText(query.value(3).toString());
        }

        currentRow = ui->tableWidget_1->rowCount();
        ui->tableWidget_1->insertRow(currentRow);
        ui->tableWidget_1->setItem(currentRow, 0, gnameItem);
        ui->tableWidget_1->setItem(currentRow, 1, numItem);
        ui->tableWidget_1->setItem(currentRow, 2, borrownumItem);
    }
}

void stockSelDialog::on_tableWidget_1_clicked(const QModelIndex &index)
{
    //物品库存查询物品单击
    QSqlQuery query;
    QString sql;

    QString gname = ui->tableWidget_1->item(index.row(), 0)->text();
    QString goodsid = "0";
    int currentRow = 0;

    sql = "select goodsid from goods where gname = '" + gname + "'";
    query.exec(sql);
    while(query.next())
    {
        goodsid = query.value(0).toString();
    }

    QList<QString> idNumList;
    QList<QString> numList;
    QList<QString> useridList;
    sql = "select * from usergoods where goodsid = '" + goodsid + "'";
    query.exec(sql);
    while(query.next())
    {
        idNumList << query.value(0).toString();
        numList << query.value(2).toString();
        useridList << query.value(3).toString();
    }

    ui->tableWidget_2->setRowCount(0);
    for(int i=0; i<useridList.count(); i++)
    {
        QTableWidgetItem *idNumItem = new QTableWidgetItem(QTableWidgetItem::Type);
        QTableWidgetItem *gnameItem = new QTableWidgetItem(QTableWidgetItem::Type);
        QTableWidgetItem *usernameItem = new QTableWidgetItem(QTableWidgetItem::Type);
        QTableWidgetItem *numItem = new QTableWidgetItem(QTableWidgetItem::Type);
        idNumItem->setText(idNumList[i]);
        usernameItem->setText("0");
        gnameItem->setText(gname);
        numItem->setText(numList[i]);

        sql = "select * from users where usersid = '" + useridList[i] + "'";
        query.exec(sql);
        while(query.next())
        {
            usernameItem->setText(query.value(1).toString());
        }

        currentRow = ui->tableWidget_2->rowCount();
        ui->tableWidget_2->insertRow(currentRow);
        ui->tableWidget_2->setItem(currentRow, 0, idNumItem);
        ui->tableWidget_2->setItem(currentRow, 1, gnameItem);
        ui->tableWidget_2->setItem(currentRow, 2, usernameItem);
        ui->tableWidget_2->setItem(currentRow, 3, numItem);
    }
}

void stockSelDialog::on_tableWidget_2_clicked(const QModelIndex &index)
{
    //库存人员身份证查询单击
    QSqlQuery query;
    QString sql;

    QString idnum = ui->tableWidget_2->item(index.row(), 0)->text();
    QString goodsid = "0";
    QString usersid = "0";
    QString idcard = "0";

    sql = "select * from usergoods where usergoodsid = '" + idnum + "'";
    query.exec(sql);
    while(query.next())
    {
        goodsid = query.value(1).toString();
        usersid = query.value(3).toString();
    }

    sql = "select idcard from users where usersid = '" + usersid + "' and role = " + QString::number(STAFF_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        idcard = query.value(0).toString();
    }
    idcard = hideIdcard(idcard);

    ui->comboBox_10->clear();
    ui->comboBox_10->addItem(idcard);
}

void stockSelDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    //物品借还记录物品搜索
    currentTableModel_1->setFilter("gname like '%" + arg1 + "%'");
}

void stockSelDialog::on_lineEdit_3_textChanged(const QString &arg1)
{
    //物品借还记录员工搜索
    currentTableModel_2->setFilter("username like '%" + arg1 + "%' and role = " + QString::number(STAFF_ROLE, 10));
}

void stockSelDialog::on_lineEdit_5_textChanged(const QString &arg1)
{
    //物品借还记录员工输入框改变
    if(arg1 == "")
    {
        ui->comboBox_5->clear();
        ui->comboBox_5->addItem("");
    }
}

void stockSelDialog::on_lineEdit_6_textChanged(const QString &arg1)
{
    //物品借还记录保管搜索
    QSqlQuery query;
    ui->comboBox_1->clear();
    ui->comboBox_1->addItem("");
    query.exec("select username from users where username like '%" + arg1 + "%' and role = " + QString::number(KEEPER_ROLE, 10));
    while(query.next())
    {
        ui->comboBox_1->addItem(query.value(0).toString());
    }
    ui->comboBox_1->setCurrentIndex(0);
}

void stockSelDialog::on_tableView_1_clicked(const QModelIndex &index)
{
    //物品借还记录物品栏单击
    ui->lineEdit_4->setText(currentTableModel_1->index(index.row(), 0).data().toString());
}

void stockSelDialog::on_tableView_2_clicked(const QModelIndex &index)
{
    //物品借还记录员工栏单击
    QSqlQuery query;
    QString sql;
    QString username = currentTableModel_2->index(index.row(), 0).data().toString();
    ui->lineEdit_5->setText(username);

    QList<QString> useridList;
    sql = "select * from users where username = '" + username + "' and role = " + QString::number(STAFF_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        useridList << query.value(0).toString();
    }

    int currentRow = index.row();
    int currentUser = 0;
    for(int i =0; i<currentRow; i++)
    {
        if(currentTableModel_2->index(i, 0).data().toString() == username)
        {
            currentUser++;
        }
    }

    QString usersid = useridList[currentUser];
    QString idcard = "0";

    sql = "select idcard from users where usersid = '" + usersid + "' and role = " + QString::number(STAFF_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        idcard = query.value(0).toString();
    }
    idcard = hideIdcard(idcard);
    ui->comboBox_5->clear();
    ui->comboBox_5->addItem("");
    ui->comboBox_5->addItem(idcard);
    ui->comboBox_5->setCurrentIndex(1);
}

void stockSelDialog::on_comboBox_1_currentIndexChanged(const QString &arg1)
{
    //物品借还记录主管选择
    QSqlQuery query;
    QString sql;
    QString username = arg1;
    if(username == "")
    {
        ui->comboBox_6->clear();
        return;
    }

    QList<QString> useridList;
    sql = "select * from users where username = '" + username + "' and role = " + QString::number(KEEPER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        useridList << query.value(0).toString();
    }

    int currentRow = ui->comboBox_1->currentIndex();
    int currentUser = 0;
    for(int i =0; i<currentRow; i++)
    {
        if(ui->comboBox_1->itemText(i) == username)
        {
            currentUser++;
        }
    }

    QString usersid = useridList[currentUser];
    QString idcard = "0";

    sql = "select idcard from users where usersid = '" + usersid + "' and role = " + QString::number(KEEPER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        idcard = query.value(0).toString();
    }
    idcard = hideIdcard(idcard);
    ui->comboBox_6->clear();
    ui->comboBox_6->addItem("");
    ui->comboBox_6->addItem(idcard);
    ui->comboBox_6->setCurrentIndex(1);
}

void stockSelDialog::on_pushButton_clicked()
{
    //物品借还记录查询
    QSqlQuery query;
    QString sql;

    QDate preDate = ui->dateEdit_1->date();
    QDate nxtDate = ui->dateEdit_2->date();
    if(preDate > nxtDate)
    {
        QMessageBox::information(NULL, "error.", "时间间隔选择错误!");
        return;
    }

    int currentRow = 0;
    QString gname = ui->lineEdit_4->text().trimmed();
    QList<QString> goodsidList;
    QList<QString> gnameList;

    sql = "select goodsid, gname from goods where gname like '%" + gname + "%'";
    query.exec(sql);
    while(query.next())
    {
        goodsidList << query.value(0).toString();
        gnameList << query.value(1).toString();
    }

    QString username = ui->lineEdit_5->text().trimmed();
    QString uidcard = ui->comboBox_5->currentText();
    QList<QString> usersidList;
    QList<QString> usernameList;
    sql = "select usersid, username from users where username like '%" + username + "%' and idcard like '%" + showIdcard(uidcard) + "%' and role = " + QString::number(STAFF_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        usersidList << query.value(0).toString();
        usernameList << query.value(1).toString();
    }

    QString keepername = ui->comboBox_1->currentText();
    QString kidcard = ui->comboBox_6->currentText();
    QList<QString> keeperidList;
    QList<QString> keepernameList;
    sql = "select usersid, username from users where username like '%" + keepername + "%' and idcard like '%" + showIdcard(kidcard) + "%' and role = " + QString::number(KEEPER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        keeperidList << query.value(0).toString();
        keepernameList << query.value(1).toString();
    }

    QString borrowFlag = "";
    if(ui->checkBox_4->checkState())
    {
        if(ui->checkBox_5->checkState())
        {
            borrowFlag = "";
        }
        else
        {
            borrowFlag = QString::number(BORROW_FLAG, 10);
        }
    }
    else
    {
        if(ui->checkBox_5->checkState())
        {
            borrowFlag = QString::number(BACK_FALG, 10);
        }
        else
        {
            borrowFlag = "2";
        }
    }

    ui->tableWidget_3->setRowCount(0);
    for(int i=0; i<goodsidList.count(); i++)
    {
        for(int j=0; j<usersidList.count(); j++)
        {
            for(int k=0; k<keeperidList.count(); k++)
            {
                sql = "select borrowlogid, num, createdate, borrowflag from borrowlog where goodsid = '" + goodsidList[i]
                        + "' and userid = '" + usersidList[j]
                        + "' and keeperid = '" + keeperidList[k]
                        + "' and borrowflag like '%" + borrowFlag
                        + "' and createdate > '" + preDate.toString("yyyy.MM.dd")
                        + "' and createdate < '" + nxtDate.toString("yyyy.MM.dd")
                        + "'";
                query.exec(sql);
                while(query.next())
                {
                    QTableWidgetItem *idNumItem = new QTableWidgetItem(QTableWidgetItem::Type);
                    QTableWidgetItem *gnameItem = new QTableWidgetItem(QTableWidgetItem::Type);
                    QTableWidgetItem *numItem = new QTableWidgetItem(QTableWidgetItem::Type);
                    QTableWidgetItem *dateItem = new QTableWidgetItem(QTableWidgetItem::Type);
                    QTableWidgetItem *keepernameItem = new QTableWidgetItem(QTableWidgetItem::Type);
                    QTableWidgetItem *usernameItem = new QTableWidgetItem(QTableWidgetItem::Type);
                    QTableWidgetItem *flagItem = new QTableWidgetItem(QTableWidgetItem::Type);
                    gnameItem->setText(gnameList[i]);
                    usernameItem->setText(usernameList[j]);
                    keepernameItem->setText(keepernameList[k]);
                    numItem->setText("0");

                    idNumItem->setText(query.value(0).toString());
                    numItem->setText(query.value(1).toString());
                    dateItem->setText(query.value(2).toString());
                    flagItem->setText((query.value(3).toInt()==BORROW_FLAG)?"借":"还");

                    currentRow = ui->tableWidget_3->rowCount();
                    ui->tableWidget_3->insertRow(currentRow);
                    ui->tableWidget_3->setItem(currentRow, 0, idNumItem);
                    ui->tableWidget_3->setItem(currentRow, 1, gnameItem);
                    ui->tableWidget_3->setItem(currentRow, 2, numItem);
                    ui->tableWidget_3->setItem(currentRow, 3, dateItem);
                    ui->tableWidget_3->setItem(currentRow, 4, keepernameItem);
                    ui->tableWidget_3->setItem(currentRow, 5, usernameItem);
                    ui->tableWidget_3->setItem(currentRow, 6, flagItem);
                }
            }
        }
    }
}

void stockSelDialog::on_tableWidget_3_clicked(const QModelIndex &index)
{
    //物品借还记录栏单击
    QSqlQuery query;
    QString sql;

    QString idnum = ui->tableWidget_3->item(index.row(), 0)->text();
    QString goodsid = "0";
    QString gname = "";
    QString keeperid = "0";
    QString kname = "";
    QString kidcard = "0";
    QString usersid = "0";
    QString uname = "";
    QString uidcard = "0";

    sql = "select * from borrowlog where borrowlogid = '" + idnum + "'";
    query.exec(sql);
    while(query.next())
    {
        goodsid = query.value(1).toString();
        keeperid = query.value(4).toString();
        usersid = query.value(5).toString();
    }

    sql = "select gname from goods where goodsid = '" + goodsid + "'";
    query.exec(sql);
    while(query.next())
    {
        gname = query.value(0).toString();
    }

    sql = "select username, idcard from users where usersid = '" + keeperid + "' and role = " + QString::number(KEEPER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        kname = query.value(0).toString();
        kidcard = query.value(1).toString();
    }

    sql = "select username, idcard from users where usersid = '" + usersid + "' and role = " + QString::number(STAFF_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        uname = query.value(0).toString();
        uidcard = query.value(1).toString();
    }
    kidcard = hideIdcard(kidcard);
    uidcard = hideIdcard(uidcard);

    ui->lineEdit_4->setText(gname);
    ui->lineEdit_5->setText(uname);
    ui->comboBox_5->clear();
    ui->comboBox_5->addItem(uidcard);
    ui->lineEdit_6->setText(kname);
    ui->comboBox_6->clear();
    ui->comboBox_6->addItem(kidcard);
}

void stockSelDialog::on_lineEdit_7_textChanged(const QString &arg1)
{
    //物品库存记录物品搜索
    currentTableModel_3->setFilter("gname like '%" + arg1 + "%'");
}

void stockSelDialog::on_lineEdit_8_textChanged(const QString &arg1)
{
    //物品库存记录采购搜索
    QSqlQuery query;
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("");
    ui->comboBox_7->clear();
    ui->comboBox_7->addItem("");
    query.exec("select username from users where username like '%" + arg1 + "%' and role = " + QString::number(BUYER_ROLE, 10));
    while(query.next())
    {
        ui->comboBox_2->addItem(query.value(0).toString());
    }
    ui->comboBox_2->setCurrentIndex(0);
}

void stockSelDialog::on_lineEdit_9_textChanged(const QString &arg1)
{
    //物品库存记录保管搜索
    QSqlQuery query;
    ui->comboBox_3->clear();
    ui->comboBox_3->addItem("");
    ui->comboBox_8->clear();
    ui->comboBox_8->addItem("");
    query.exec("select username from users where username like '%" + arg1 + "%' and role = " + QString::number(KEEPER_ROLE, 10));
    while(query.next())
    {
        ui->comboBox_3->addItem(query.value(0).toString());
    }
    ui->comboBox_3->setCurrentIndex(0);
}

void stockSelDialog::on_lineEdit_10_textChanged(const QString &arg1)
{
    //物品库存记录主管搜索
    QSqlQuery query;
    ui->comboBox_4->clear();
    ui->comboBox_4->addItem("");
    ui->comboBox_9->clear();
    ui->comboBox_9->addItem("");
    query.exec("select username from users where username like '%" + arg1 + "%' and role = " + QString::number(LEADER_ROLE, 10));
    while(query.next())
    {
        ui->comboBox_4->addItem(query.value(0).toString());
    }
    ui->comboBox_4->setCurrentIndex(0);
}

void stockSelDialog::on_tableView_3_clicked(const QModelIndex &index)
{
    ui->lineEdit_11->setText(currentTableModel_3->index(index.row(), 0).data().toString());
}

void stockSelDialog::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    //物品库存记录采购选择
    QSqlQuery query;
    QString sql;
    QString username = arg1;
    if(username == "")
    {
        ui->comboBox_7->clear();
        return;
    }

    QList<QString> useridList;
    sql = "select * from users where username = '" + username + "' and role = " + QString::number(BUYER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        useridList << query.value(0).toString();
    }

    int currentRow = ui->comboBox_2->currentIndex();
    int currentUser = 0;
    for(int i =0; i<currentRow; i++)
    {
        if(ui->comboBox_2->itemText(i) == username)
        {
            currentUser++;
        }
    }

    QString usersid = useridList[currentUser];
    QString idcard = "0";

    sql = "select idcard from users where usersid = '" + usersid + "' and role = " + QString::number(BUYER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        idcard = query.value(0).toString();
    }
    idcard = hideIdcard(idcard);
    ui->comboBox_7->clear();
    ui->comboBox_7->addItem("");
    ui->comboBox_7->addItem(idcard);
    ui->comboBox_7->setCurrentIndex(1);
}

void stockSelDialog::on_comboBox_3_currentIndexChanged(const QString &arg1)
{
    //物品库存记录保管选择
    QSqlQuery query;
    QString sql;
    QString username = arg1;
    if(username == "")
    {
        ui->comboBox_8->clear();
        return;
    }

    QList<QString> useridList;
    sql = "select * from users where username = '" + username + "' and role = " + QString::number(KEEPER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        useridList << query.value(0).toString();
    }

    int currentRow = ui->comboBox_3->currentIndex();
    int currentUser = 0;
    for(int i =0; i<currentRow; i++)
    {
        if(ui->comboBox_3->itemText(i) == username)
        {
            currentUser++;
        }
    }

    QString usersid = useridList[currentUser];
    QString idcard = "0";

    sql = "select idcard from users where usersid = '" + usersid + "' and role = " + QString::number(KEEPER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        idcard = query.value(0).toString();
    }
    idcard = hideIdcard(idcard);
    ui->comboBox_8->clear();
    ui->comboBox_8->addItem("");
    ui->comboBox_8->addItem(idcard);
    ui->comboBox_8->setCurrentIndex(1);
}

void stockSelDialog::on_comboBox_4_currentIndexChanged(const QString &arg1)
{
    //物品库存记录主管选择
    QSqlQuery query;
    QString sql;
    QString username = arg1;
    if(username == "")
    {
        ui->comboBox_9->clear();
        return;
    }

    QList<QString> useridList;
    sql = "select * from users where username = '" + username + "' and role = " + QString::number(LEADER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        useridList << query.value(0).toString();
    }

    int currentRow = ui->comboBox_3->currentIndex();
    int currentUser = 0;
    for(int i =0; i<currentRow; i++)
    {
        if(ui->comboBox_3->itemText(i) == username)
        {
            currentUser++;
        }
    }

    QString usersid = useridList[currentUser];
    QString idcard = "0";

    sql = "select idcard from users where usersid = '" + usersid + "' and role = " + QString::number(LEADER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        idcard = query.value(0).toString();
    }
    idcard = hideIdcard(idcard);
    ui->comboBox_9->clear();
    ui->comboBox_9->addItem("");
    ui->comboBox_9->addItem(idcard);
    ui->comboBox_9->setCurrentIndex(1);
}

void stockSelDialog::on_pushButton_2_clicked()
{
    //物品库存记录查询
    QSqlQuery query;
    QString sql;

    QDate preDate = ui->dateEdit_3->date();
    QDate nxtDate = ui->dateEdit_4->date();
    if(preDate > nxtDate)
    {
        QMessageBox::information(NULL, "error.", "时间间隔选择错误!");
        return;
    }

    int currentRow = 0;
    QString gname = ui->lineEdit_11->text().trimmed();
    QList<QString> goodsidList;
    QList<QString> gnameList;

    sql = "select goodsid, gname from goods where gname like '%" + gname + "%'";
    query.exec(sql);
    while(query.next())
    {
        goodsidList << query.value(0).toString();
        gnameList << query.value(1).toString();
    }

    QString buyername = ui->comboBox_2->currentText();
    QString bidcard = ui->comboBox_7->currentText();
    QList<QString> buyeridList;
    QList<QString> buyernameList;
    if(buyername == "")
    {
        buyeridList << "0";
        buyernameList << "";
    }
    sql = "select usersid, username from users where username like '%" + buyername + "%' and idcard like '%" + showIdcard(bidcard) + "%' and role = " + QString::number(BUYER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        buyeridList << query.value(0).toString();
        buyernameList << query.value(1).toString();
    }

    QString keepername = ui->comboBox_3->currentText();
    QString kidcard = ui->comboBox_8->currentText();
    QList<QString> keeperidList;
    QList<QString> keepernameList;
    sql = "select usersid, username from users where username like '%" + keepername + "%' and idcard like '%" + showIdcard(kidcard) + "%' and role = " + QString::number(KEEPER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        keeperidList << query.value(0).toString();
        keepernameList << query.value(1).toString();
    }

    QString leadername = ui->comboBox_4->currentText();
    QString lidcard = ui->comboBox_9->currentText();
    QList<QString> leaderidList;
    QList<QString> leadernameList;
    sql = "select usersid, username from users where username like '%" + leadername + "%' and idcard like '%" + showIdcard(lidcard) + "%' and role = " + QString::number(LEADER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        leaderidList << query.value(0).toString();
        leadernameList << query.value(1).toString();
    }

    QString numFlag = "";
    if(ui->checkBox_6->checkState())
    {
        if(ui->checkBox_7->checkState())
        {
            numFlag = "<> '0";
        }
        else
        {
            numFlag = "> '0";
        }
    }
    else
    {
        if(ui->checkBox_7->checkState())
        {
            numFlag = "< '0";
        }
        else
        {
            numFlag = "= '0";
        }
    }

    ui->tableWidget_4->setRowCount(0);
    for(int i=0; i<goodsidList.count(); i++)
    {
        for(int j=0; j<buyeridList.count(); j++)
        {
            for(int k=0; k<keeperidList.count(); k++)
            {
                for(int l=0; l<leaderidList.count(); l++)
                {
                    sql = "select stockslogid, num, createdate from stockslog where goodsid = '" + goodsidList[i]
                            + "' and buyerid = '" + buyeridList[j]
                            + "' and keeperid = '" + keeperidList[k]
                            + "' and leaderid = '" + leaderidList[l]
                            + "' and num " + numFlag
                            + "' and createdate > '" + preDate.toString("yyyy.MM.dd")
                            + "' and createdate < '" + nxtDate.toString("yyyy.MM.dd")
                            + "'";
                    query.exec(sql);
                    while(query.next())
                    {
                        QTableWidgetItem *idNumItem = new QTableWidgetItem(QTableWidgetItem::Type);
                        QTableWidgetItem *gnameItem = new QTableWidgetItem(QTableWidgetItem::Type);
                        QTableWidgetItem *numItem = new QTableWidgetItem(QTableWidgetItem::Type);
                        QTableWidgetItem *dateItem = new QTableWidgetItem(QTableWidgetItem::Type);
                        QTableWidgetItem *buyernameItem = new QTableWidgetItem(QTableWidgetItem::Type);
                        QTableWidgetItem *keepernameItem = new QTableWidgetItem(QTableWidgetItem::Type);
                        QTableWidgetItem *leadernameItem = new QTableWidgetItem(QTableWidgetItem::Type);
                        gnameItem->setText(gnameList[i]);
                        buyernameItem->setText(buyernameList[j]);
                        keepernameItem->setText(keepernameList[k]);
                        leadernameItem->setText(leadernameList[l]);
                        numItem->setText("0");

                        idNumItem->setText(query.value(0).toString());
                        numItem->setText(query.value(1).toString());
                        dateItem->setText(query.value(2).toString());

                        currentRow = ui->tableWidget_4->rowCount();
                        ui->tableWidget_4->insertRow(currentRow);
                        ui->tableWidget_4->setItem(currentRow, 0, idNumItem);
                        ui->tableWidget_4->setItem(currentRow, 1, gnameItem);
                        ui->tableWidget_4->setItem(currentRow, 2, numItem);
                        ui->tableWidget_4->setItem(currentRow, 3, dateItem);
                        ui->tableWidget_4->setItem(currentRow, 4, buyernameItem);
                        ui->tableWidget_4->setItem(currentRow, 5, keepernameItem);
                        ui->tableWidget_4->setItem(currentRow, 6, leadernameItem);
                    }
                }
            }
        }
    }
}

void stockSelDialog::on_tableWidget_4_clicked(const QModelIndex &index)
{
    //物品库存记录栏单击
    QSqlQuery query;
    QString sql;

    QString idnum = ui->tableWidget_4->item(index.row(), 0)->text();
    QString goodsid = "0";
    QString gname = "";
    QString buyerid = "0";
    QString bname = "";
    QString bidcard = "0";
    QString keeperid = "0";
    QString kname = "";
    QString kidcard = "0";
    QString leaderid = "0";
    QString lname = "";
    QString lidcard = "0";

    sql = "select * from stockslog where stockslogid = '" + idnum + "'";
    query.exec(sql);
    while(query.next())
    {
        goodsid = query.value(1).toString();
        buyerid = query.value(4).toString();
        keeperid = query.value(5).toString();
        leaderid = query.value(6).toString();
    }

    sql = "select gname from goods where goodsid = '" + goodsid + "'";
    query.exec(sql);
    while(query.next())
    {
        gname = query.value(0).toString();
    }

    sql = "select username, idcard from users where usersid = '" + buyerid + "' and role = " + QString::number(BUYER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        bname = query.value(0).toString();
        bidcard = query.value(1).toString();
    }

    sql = "select username, idcard from users where usersid = '" + keeperid + "' and role = " + QString::number(KEEPER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        kname = query.value(0).toString();
        kidcard = query.value(1).toString();
    }

    sql = "select username, idcard from users where usersid = '" + leaderid + "' and role = " + QString::number(LEADER_ROLE, 10);
    query.exec(sql);
    while(query.next())
    {
        lname = query.value(0).toString();
        lidcard = query.value(1).toString();
    }
    bidcard = hideIdcard(bidcard);
    kidcard = hideIdcard(kidcard);
    lidcard = hideIdcard(lidcard);

    ui->lineEdit_11->setText(gname);
    ui->lineEdit_8->setText(bname);
    ui->comboBox_7->clear();
    ui->comboBox_7->addItem(bidcard);
    ui->lineEdit_9->setText(kname);
    ui->comboBox_8->clear();
    ui->comboBox_8->addItem(kidcard);
    ui->lineEdit_10->setText(lname);
    ui->comboBox_9->clear();
    ui->comboBox_9->addItem(lidcard);
}
