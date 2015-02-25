#include "stockadddialog.h"
#include "ui_stockadddialog.h"

stockAddDialog::stockAddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stockAddDialog)
{
    ui->setupUi(this);

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    this->setWindowTitle("添加库存管理");

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    qFinger = new qFingerprint(this);
    connect(qFinger, SIGNAL(OnImageReceived()), this, SLOT(finishImageReceived()));
    connect(qFinger, SIGNAL(OnFeatureInfo(int)), this, SLOT(finishFeatureInfo(int)));
    connect(qFinger, SIGNAL(OnCapture(QVariant)), this, SLOT(finishCapture(QVariant)));

    init();
}

stockAddDialog::~stockAddDialog()
{
    delete ui;
}

void stockAddDialog::showEvent(QShowEvent *)
{
    init();
    on_pushButton_clicked();
}

void stockAddDialog::paintEvent(QPaintEvent *)
{}

void stockAddDialog::closeEvent(QCloseEvent *)
{
    qFinger->EndEngine();
    emit OnClose();
}

void stockAddDialog::init()
{
    //初始化
    /*
    //创建库存记录表(编号, 物品编号, 物品个数, 日期, 采购, 保管, 主管)
    query.exec("create table stockslog(stockslogid INT PRIMARY KEY, goodsid INT, num INT, createdate VARCHAR, buyerid INT, keeperid INT, leaderid INT)");
    //创建库存表(编号, 物品编号, 物品总数, 借出总数)
    query.exec("create table stocks(stocksid INT PRIMARY KEY, goodsid INT, num INT, borrownum INT)");
    */

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
    header.append("入库个数");
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
    ui->checkBox_3->setText("正在对比 ...");
    ui->checkBox_3->setChecked(false);
    ui->checkBox_3->setEnabled(false);

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
    ui->lineEdit_8->clear();
    ui->lineEdit_8->setEnabled(false);

    buyerid = 0;
    keeperid = 0;
    leaderid = 0;
}

void stockAddDialog::initGoods()
{
    //初始化物品表
    currentTableModel->setTable("goods");
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

void stockAddDialog::finishImageReceived()
{
    //指纹图像完成
    qFinger->SaveBitmap();
    ui->label_2->setPixmap(QPixmap(fingerBmpPath));
}

void stockAddDialog::finishFeatureInfo(int Aquality)
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

void stockAddDialog::finishCapture(QVariant ATemplate)
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

void stockAddDialog::findFingerUser(int mUserid)
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
        break;
    case BUYER_ROLE:
        buyerid = idNum;
        ui->checkBox_1->setText(name);
        ui->checkBox_1->setChecked(true);
        break;
    case KEEPER_ROLE:
        keeperid = idNum;
        ui->checkBox_2->setText(name);
        ui->checkBox_2->setChecked(true);
        break;
    case LEADER_ROLE:
        leaderid = idNum;
        ui->checkBox_3->setText(name);
        ui->checkBox_3->setChecked(true);
        break;
    default:
        break;
    }

    roleCheckboxStatus();
}

void stockAddDialog::roleCheckboxStatus()
{
    //检查权限
    if((ui->checkBox_1->checkState())
            &&(ui->checkBox_2->checkState())
            &&(ui->checkBox_3->checkState()))
    {
        ui->lineEdit_5->clear();
        ui->lineEdit_5->setEnabled(true);

        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
    }
}

void stockAddDialog::on_pushButton_clicked()
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

void stockAddDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    //搜索物品
    currentTableModel->setFilter("gname like '%" + arg1 + "%'");
}

void stockAddDialog::on_tableView_clicked(const QModelIndex &index)
{
    //物品栏单击
    int curRow = index.row(); //获取选中的行
    QString gname = currentTableModel->index(curRow, 0).data().toString();
    ui->lineEdit_4->setText(gname);

    QSqlQuery query;
    QString sql;
    QString goodsid = "0";
    QString num = "0";
    QString borrownum = "0";

    sql = "select goodsid from goods where gname = '" + gname + "'";
    query.exec(sql);
    while(query.next())
    {
        goodsid = query.value(0).toString();
    }

    sql = "select * from stocks where goodsid = '" + goodsid + "'";
    query.exec(sql);
    while(query.next())
    {
        num = query.value(2).toString();
        borrownum = query.value(3).toString();
    }

    ui->lineEdit_6->setText(gname);
    ui->lineEdit_7->setText(num);
    ui->lineEdit_8->setText(borrownum);
}

void stockAddDialog::on_tableWidget_clicked(const QModelIndex &index)
{
    //库存栏单击
    int curRow = index.row(); //获取选中的行
    QString gname = ui->tableWidget->item(curRow, 0)->text().trimmed();
    QString num = ui->tableWidget->item(curRow, 1)->text().trimmed();
    ui->lineEdit_3->setText(QString::number(curRow, 10));
    ui->lineEdit_4->setText(gname);
    ui->lineEdit_5->setText(num);
}

void stockAddDialog::on_pushButton_2_clicked()
{
    //添加
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

void stockAddDialog::on_pushButton_3_clicked()
{
    //修改
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

void stockAddDialog::on_pushButton_4_clicked()
{
    //提交
    if(buyerid == 0)
    {
        QMessageBox::information(NULL, "error.", "无法记录采购,请重新刷入采购指纹!");
        return;
    }
    if(keeperid == 0)
    {
        QMessageBox::information(NULL, "error.", "无法记录保管,请重新刷入保管指纹!");
        return;
    }
    if(leaderid == 0)
    {
        QMessageBox::information(NULL, "error.", "无法记录主管,请重新刷入主管指纹!");
        return;
    }

    QSqlQuery query;
    QString sql;
    int curRow = 0;
    int idNum = 0;
    QString goodsid = "0";
    int curGoodsNum = 0;
    QString num = "0";
    QString gname = "";
    bool stockFlag = false;

    while(ui->tableWidget->rowCount())
    {
        curRow = 0;
        idNum = 0;
        goodsid = "0";
        curGoodsNum = 0;
        num = "0";
        gname = "";
        stockFlag = false;

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

        //插入stockslog
        sql = "select stockslogid from stockslog";
        query.exec(sql);
        while(query.next())
        {
            if(idNum < query.value(0).toInt())
                idNum = query.value(0).toInt();
        }
        idNum++;

        sql = "insert into stockslog values('" + QString::number(idNum, 10)
                + "', '" + goodsid
                + "', '" + num
                + "', '" + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")
                + "', '" + QString::number(buyerid, 10)
                + "', '" + QString::number(keeperid, 10)
                + "', '" + QString::number(leaderid, 10)
                + "')";
        query.exec(sql);

        //插入stocks
        sql = "select * from stocks where goodsid = '" + goodsid + "'";
        query.exec(sql);
        while(query.next())
        {
            curGoodsNum = query.value(2).toInt() + num.toInt();
            stockFlag = true;
        }

        if(stockFlag == true)
        {
            sql = "update stocks set num = '" + QString::number(curGoodsNum, 10)
                    + "' where goodsid = '" + goodsid + "'";
            query.exec(sql);
        }
        else
        {
            idNum = 0;
            sql = "select stocksid from stocks";
            query.exec(sql);
            while(query.next())
            {
                if(idNum < query.value(0).toInt())
                    idNum = query.value(0).toInt();
            }
            idNum++;

            sql = "insert into stocks values('" + QString::number(idNum, 10)
                    + "', '" + goodsid
                    + "', '" + num
                    + "', '0')";
            query.exec(sql);
        }

        ui->tableWidget->removeRow(curRow);
    }
}
