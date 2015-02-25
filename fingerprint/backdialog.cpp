#include "backdialog.h"
#include "ui_backdialog.h"

backDialog::backDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::backDialog)
{
    ui->setupUi(this);

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    this->setWindowTitle("归还物品管理");

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    qFinger = new qFingerprint(this);
    connect(qFinger, SIGNAL(OnImageReceived()), this, SLOT(finishImageReceived()));
    connect(qFinger, SIGNAL(OnFeatureInfo(int)), this, SLOT(finishFeatureInfo(int)));
    connect(qFinger, SIGNAL(OnCapture(QVariant)), this, SLOT(finishCapture(QVariant)));

    init();
}

backDialog::~backDialog()
{
    delete ui;
}

void backDialog::showEvent(QShowEvent *)
{
    init();
    on_pushButton_clicked();
}

void backDialog::paintEvent(QPaintEvent *)
{}

void backDialog::closeEvent(QCloseEvent *)
{
    qFinger->EndEngine();
    emit OnClose();
}

void backDialog::on_pushButton_clicked()
{
    //连接指纹仪
    int result = -1;
    QString strSN = "指纹仪器未连接!";
    result = qFinger->InitEngine();

    if(result == 0)
    {
        strSN = qFinger->SensorSN();
    }
    else
    {
        qFinger->EndEngine();
        QMessageBox::information(NULL, "error.", "初始化指纹仪失败!");
    }
    ui->lineEdit->setText(QString(strSN));
}

void backDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    //搜索物品
    currentTableModel->setFilter("gname like '%" + arg1 + "%'");
}

void backDialog::on_tableView_clicked(const QModelIndex &index)
{
    //物品栏单击
    int curRow = index.row(); //获取选中的行
    QString gname = currentTableModel->index(curRow, 0).data().toString();
    ui->lineEdit_4->setText(gname);

    QSqlQuery query;
    QString sql;
    QString goodsid = "0";
    QString num = "0";

    sql = "select goodsid from goods where gname = '" + gname + "'";
    query.exec(sql);
    while(query.next())
    {
        goodsid = query.value(0).toString();
    }

    sql = "select num from usergoods where userid = '" + QString::number(userid, 10)
            + "' and goodsid = '" + goodsid
            + "'";
    query.exec(sql);
    while(query.next())
    {
        num = query.value(0).toString();
    }

    ui->lineEdit_6->setText(gname);
    ui->lineEdit_7->setText(num);
}

void backDialog::on_tableWidget_clicked(const QModelIndex &index)
{
    //归还栏单击
    int curRow = index.row(); //获取选中的行
    QString gname = ui->tableWidget->item(curRow, 0)->text().trimmed();
    QString num = ui->tableWidget->item(curRow, 1)->text().trimmed();
    ui->lineEdit_3->setText(QString::number(curRow, 10));
    ui->lineEdit_4->setText(gname);
    ui->lineEdit_5->setText(num);

    QSqlQuery query;
    QString sql;
    QString goodsid = "0";
    QString borrowNum = "0";

    sql = "select goodsid from goods where gname = '" + gname + "'";
    query.exec(sql);
    while(query.next())
    {
        goodsid = query.value(0).toString();
    }

    sql = "select num from usergoods where userid = '" + QString::number(userid, 10)
            + "' and goodsid = '" + goodsid
            + "'";
    query.exec(sql);
    while(query.next())
    {
        borrowNum = query.value(0).toString();
    }

    ui->lineEdit_6->setText(gname);
    ui->lineEdit_7->setText(borrowNum);
}

void backDialog::on_pushButton_2_clicked()
{
    //添加
    int borrowNum = ui->lineEdit_7->text().toInt();
    QString name = ui->lineEdit_4->text().trimmed();
    QString num = ui->lineEdit_5->text().trimmed();

    if(name == "")
    {
        QMessageBox::information(NULL, "error.", "没有物品名称!");
        return;
    }

    if((num == "") || (num.toInt() == 0))
    {
        QMessageBox::information(NULL, "error.", "没有物品个数!");
        return;
    }

    int curRowCount = ui->tableWidget->rowCount();
    int beforeNum = 0;
    for(int i=0; i<curRowCount; i++)
    {
        if(ui->tableWidget->item(i, 0)->text().trimmed() == name)
        {
            beforeNum += ui->tableWidget->item(i, 1)->text().toInt();
        }
    }

    if(borrowNum < (beforeNum + num.toInt()))
    {
        QMessageBox::information(NULL, "error.", "归还太多,无法归还!");
        return;
    }

    QTableWidgetItem *nameItem = new QTableWidgetItem(QTableWidgetItem::Type);
    nameItem->setText(name);
    QTableWidgetItem *numItem = new QTableWidgetItem(QTableWidgetItem::Type);
    numItem->setText(num);

    int currentRow = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(currentRow);
    ui->tableWidget->setItem(currentRow, 0, nameItem);
    ui->tableWidget->setItem(currentRow, 1, numItem);

    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void backDialog::on_pushButton_3_clicked()
{
    //修改
    int borrowNum = ui->lineEdit_7->text().toInt();
    QString name = ui->lineEdit_4->text().trimmed();
    QString num = ui->lineEdit_5->text().trimmed();

    if(name == "")
    {
        QMessageBox::information(NULL, "error.", "没有物品名称!");
        return;
    }

    if(num == "")
    {
        QMessageBox::information(NULL, "error.", "没有物品个数,如需删除,请填写 0!");
        return;
    }

    int curRowCount = ui->tableWidget->rowCount();
    int beforeNum = 0;
    for(int i=0; i<curRowCount; i++)
    {
        if(i == ui->lineEdit_3->text().toInt())
        {
            continue;
        }

        if(ui->tableWidget->item(i, 0)->text().trimmed() == name)
        {
            beforeNum += ui->tableWidget->item(i, 1)->text().toInt();
        }
    }

    if(borrowNum < (beforeNum + num.toInt()))
    {
        QMessageBox::information(NULL, "error.", "归还太多,无法归还!");
        return;
    }

    QTableWidgetItem *nameItem = new QTableWidgetItem(QTableWidgetItem::Type);
    nameItem->setText(name);
    QTableWidgetItem *numItem = new QTableWidgetItem(QTableWidgetItem::Type);
    numItem->setText(num);

    QString currentRowStr = ui->lineEdit_3->text().trimmed();
    int currentRow = currentRowStr.toInt();

    if(currentRowStr == "")
    {
        QMessageBox::information(NULL, "error.", "没有选择所需要修改的记录!");
        return;
    }

    if(num.toInt() == 0)
    {

        ui->tableWidget->removeRow(currentRow);
    }
    else
    {
        ui->tableWidget->setItem(currentRow, 0, nameItem);
        ui->tableWidget->setItem(currentRow, 1, numItem);
    }

    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
}

void backDialog::on_pushButton_4_clicked()
{
    //提交
    if(keeperid == 0)
    {
        QMessageBox::information(NULL, "error.", "无法记录保管,请重新刷入保管指纹!");
        return;
    }
    if(userid == 0)
    {
        QMessageBox::information(NULL, "error.", "无法记录员工,请重新刷入员工指纹!");
        return;
    }

    QSqlQuery query;
    QString sql;
    int curRow = 0;
    int idNum = 0;
    QString goodsid = "0";
    int stockBorrowNum = 0;
    int curBorrowNum = 0;
    QString num = "0";
    QString gname = "";

    while(ui->tableWidget->rowCount())
    {
        curRow = 0;
        idNum = 0;
        goodsid = "0";
        stockBorrowNum = 0;
        curBorrowNum = 0;
        num = "0";
        gname = "";

        curRow = ui->tableWidget->rowCount() - 1;
        gname = ui->tableWidget->item(curRow, 0)->text().trimmed();
        num = ui->tableWidget->item(curRow, 1)->text().trimmed();

        // 查找goodsid
        sql = "select goodsid from goods where gname = '" + gname + "'";
        query.exec(sql);
        while(query.next())
        {
            goodsid = query.value(0).toString();
        }

        //插入borrowlog
        sql = "select borrowlogid from borrowlog";
        query.exec(sql);
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }
        idNum++;

        sql = "insert into borrowlog values('" + QString::number(idNum, 10)
                + "', '" + goodsid
                + "', '" + num
                + "', '" + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")
                + "', '" + QString::number(keeperid, 10)
                + "', '" + QString::number(userid, 10)
                + "', '" + QString::number(BACK_FALG, 10)
                + "')";
        query.exec(sql);

        //插入stocks
        sql = "select * from stocks where goodsid = '" + goodsid + "'";
        query.exec(sql);
        while(query.next())
        {
            stockBorrowNum = query.value(3).toInt() - num.toInt();
        }
        sql = "update stocks set borrownum = '" + QString::number(stockBorrowNum, 10)
                + "' where goodsid = '" + goodsid + "'";
        query.exec(sql);

        //插入usergoods
        sql = "select * from usergoods where goodsid = '" + goodsid
                + "' and userid = '" + QString::number(userid, 10)
                + "'";
        query.exec(sql);
        while(query.next())
        {
            curBorrowNum = query.value(2).toInt();
        }

        curBorrowNum = curBorrowNum - num.toInt();
        if(curBorrowNum == 0)
        {
            sql = "delete from usergoods where goodsid = '" + goodsid
                    + "' and userid = '" + QString::number(userid, 10)
                    + "'";
            query.exec(sql);
        }
        else
        {
            sql = "update usergoods set num = '" + QString::number(curBorrowNum, 10)
                    + "' where goodsid = '" + goodsid
                    + "' and userid = '" + QString::number(userid, 10)
                    + "'";
            query.exec(sql);
        }

        ui->tableWidget->removeRow(curRow);
    }

    ui->checkBox_2->setText("正在对比 ...");
    ui->checkBox_2->setChecked(false);
    ui->lineEdit_5->clear();
    ui->lineEdit_5->setEnabled(false);

    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);

    ui->lineEdit_6->clear();
    ui->lineEdit_6->setEnabled(false);
    ui->lineEdit_7->clear();
    ui->lineEdit_7->setEnabled(false);

    userid = 0;

    delBorrowGoods();
    initGoods();
}

void backDialog::init()
{
    //初始化
    /*
    //创建库存表(编号, 物品编号, 物品总数, 借出总数)
    query.exec("create table stocks(stocksid INT PRIMARY KEY, goodsid INT, num INT, borrownum INT)");

    //创建领取记录表(编号, 物品编号, 物品个数, 日期, 保管, 领取人, 借还标志)
    query.exec("create table borrowlog(borrowlogid INT PRIMARY KEY, goodsid INT, num INT, createdate VARCHAR, keeperid INT, userid INT, borrowflag INT)");
    //创建领取人员表(编号, 物品编号, 物品个数, 领取人)
    query.exec("create table usergoods(usergoodsid INT PRIMARY KEY, goodsid INT, num INT, userid INT)");
    //创建领取人员物品临时表(编号, 物品编号, 物品名称)
    query.exec("create table usergoodstemp(usergoodstempid INT PRIMARY KEY, goodsid INT, gname INT)");
    */

    delBorrowGoods();
    initGoods();

    ui->tableWidget->setColumnCount(0);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setColumnCount(2);
    int tableWidth = (ui->tableWidget->width() - 20 - 20) / 2;
    ui->tableWidget->setColumnWidth(0, tableWidth);
    ui->tableWidget->setColumnWidth(1, tableWidth);
    QStringList header;
    header.append("物品名称");
    header.append("归还个数");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->lineEdit->setEnabled(false);
    ui->label_2->clear();
    ui->label_2->setScaledContents(true);
    ui->label_3->clear();
    ui->label_3->setText("指纹质量 : ");

    ui->checkBox_1->setText("正在对比 ...");
    ui->checkBox_1->setChecked(false);
    ui->checkBox_1->setEnabled(false);
    ui->checkBox_2->setText("正在对比 ...");
    ui->checkBox_2->setChecked(false);
    ui->checkBox_2->setEnabled(false);

    ui->lineEdit_2->clear();
    ui->lineEdit_2->setEnabled(true);
    ui->lineEdit_3->clear();
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_5->clear();
    ui->lineEdit_5->setEnabled(false);
    QRegExp regExp("^[0-9]+$");
    QRegExpValidator *pRevalidotor = new QRegExpValidator(regExp, 0);
    ui->lineEdit_5->setValidator(pRevalidotor);

    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);

    ui->lineEdit_6->clear();
    ui->lineEdit_6->setEnabled(false);
    ui->lineEdit_7->clear();
    ui->lineEdit_7->setEnabled(false);

    keeperid = 0;
    userid = 0;
}

void backDialog::initGoods()
{
    //初始化物品表
    currentTableModel->setTable("usergoodstemp");
    currentTableModel->select();

    currentTableModel->removeColumn(0);
    currentTableModel->setHeaderData(0, Qt::Horizontal, QString("名称"));

    currentView->setModel(currentTableModel);
    currentView->setColumnWidth(0, currentView->width());
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView* headerView = currentView->verticalHeader();
    headerView->setHidden(true);

    ui->lineEdit_2->clear();
}

void backDialog::finishImageReceived()
{
    //指纹图像完成
    qFinger->SaveBitmap();
    ui->label_2->setPixmap(QPixmap(fingerBmpPath));
}

void backDialog::finishFeatureInfo(int Aquality)
{
    //指纹质量报告
    switch(Aquality)
    {
    case 0:
        ui->label_3->setText("指纹质量 : 合格");
        break;
    case 1:
        ui->label_3->setText("指纹质量 : 特征点不够");
        break;
    case 2:
        ui->label_3->setText("指纹质量 : 无法取到指纹特征");
        break;
    default:
        ui->label_3->setText("指纹质量 : ");
        break;
    }
}

void backDialog::finishCapture(QVariant ATemplate)
{
    //指纹对比
    QMapIterator<int, QVariant> i(fingerTemplateMap);
    while (i.hasNext())
    {
        i.next();
        if(qFinger->VerFinger(ATemplate, i.value()))
        {
            findFingerUser(i.key());
        }
    }
}

void backDialog::findFingerUser(int mUserid)
{
    //查找人员信息
    QSqlQuery query;
    QString sql;
    QString name;
    int idNum = 0;
    int role = -1;

    sql = "select * from users where usersid = '" + QString::number(mUserid, 10) + "'";
    query.exec(sql);

    while(query.next())
    {
        idNum = query.value(0).toInt();
        name = query.value(1).toString();
        role = query.value(3).toInt();
    }

    switch(role)
    {
    case STAFF_ROLE:
        userid = idNum;
        ui->checkBox_2->setText(name);
        ui->checkBox_2->setChecked(true);
        delBorrowGoods();
        getBorrowGoods();
        break;
    case BUYER_ROLE:
        break;
    case KEEPER_ROLE:
        keeperid = idNum;
        ui->checkBox_1->setText(name);
        ui->checkBox_1->setChecked(true);
        break;
    case LEADER_ROLE:
        break;
    default:
        break;
    }

    roleCheckboxStatus();
}

void backDialog::roleCheckboxStatus()
{
    //检查权限
    if((ui->checkBox_1->checkState())
            &&(ui->checkBox_2->checkState()))
    {
        ui->lineEdit_5->clear();
        ui->lineEdit_5->setEnabled(true);

        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
    }
}

void backDialog::getBorrowGoods()
{
    //查找借出的物品
    QSqlQuery query;
    QString sql;
    QList<QString> goodsid;
    QList<QString> gname;

    sql = "select goodsid from usergoods where userid = '" + QString::number(userid, 10) + "'";
    query.exec(sql);
    while(query.next())
    {
        goodsid << query.value(0).toString();
    }

    for(int i=0; i<goodsid.count(); i++)
    {
        sql = "select gname from goods where goodsid = '" + goodsid[i] + "'";
        query.exec(sql);
        while(query.next())
        {
            gname << query.value(0).toString();
        }
    }

    for(int i=0; i<goodsid.count(); i++)
    {
        sql = "insert into usergoodstemp values('" + QString::number(i, 10)
                + "', '" + goodsid[i]
                + "', '" + gname[i]
                + "')";
        query.exec(sql);
    }

    initGoods();
}

void backDialog::delBorrowGoods()
{
    //删除临时物品表
    QSqlQuery query;
    QString sql;

    sql = "delete from usergoodstemp";
    query.exec(sql);
}
