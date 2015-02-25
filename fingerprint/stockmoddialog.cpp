#include "stockmoddialog.h"
#include "ui_stockmoddialog.h"

stockModDialog::stockModDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stockModDialog)
{
    ui->setupUi(this);

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    this->setWindowTitle("修改库存管理");

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    qFinger = new qFingerprint(this);
    connect(qFinger, SIGNAL(OnImageReceived()), this, SLOT(finishImageReceived()));
    connect(qFinger, SIGNAL(OnFeatureInfo(int)), this, SLOT(finishFeatureInfo(int)));
    connect(qFinger, SIGNAL(OnCapture(QVariant)), this, SLOT(finishCapture(QVariant)));

    init();
}

stockModDialog::~stockModDialog()
{
    delete ui;
}

void stockModDialog::showEvent(QShowEvent *)
{
    init();
    on_pushButton_clicked();
}

void stockModDialog::paintEvent(QPaintEvent *)
{}

void stockModDialog::closeEvent(QCloseEvent *)
{
    qFinger->EndEngine();
    emit OnClose();
}

void stockModDialog::init()
{
    //初始化
    /*
    //创建库存记录表(编号, 物品编号, 物品个数, 日期, 采购, 保管, 主管)
    query.exec("create table stockslog(stockslogid INT PRIMARY KEY, goodsid INT, num INT, createdate VARCHAR, buyerid INT, keeperid INT, leaderid INT)");
    //创建库存表(编号, 物品编号, 物品总数, 借出总数)
    query.exec("create table stocks(stocksid INT PRIMARY KEY, goodsid INT, num INT, borrownum INT)");
    */

    initGoods();

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

    ui->pushButton_2->setEnabled(false);

    ui->lineEdit_6->clear();
    ui->lineEdit_6->setEnabled(false);
    QRegExp regExp("^[0-9]+$");
    QRegExpValidator *pRevalidotor = new QRegExpValidator(regExp, 0);
    ui->lineEdit_6->setValidator(pRevalidotor);

    keeperid = 0;
    leaderid = 0;
}

void stockModDialog::initGoods()
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

void stockModDialog::finishImageReceived()
{
    //指纹图像完成
    qFinger->SaveBitmap();
    ui->label_2->setPixmap(QPixmap(fingerBmpPath));
}

void stockModDialog::finishFeatureInfo(int Aquality)
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

void stockModDialog::finishCapture(QVariant ATemplate)
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

void stockModDialog::findFingerUser(int mUserid)
{
    //查找人员信息
    QSqlQuery query;
    QString sql;
    QString name;
    int idNum = 0;
    int role = -1;

    sql = "select * from users where usersid = '" + QString::number(mUserid, 10) + "'";;
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
        break;
    case KEEPER_ROLE:
        keeperid = idNum;
        ui->checkBox_1->setText(name);
        ui->checkBox_1->setChecked(true);
        break;
    case LEADER_ROLE:
        leaderid = idNum;
        ui->checkBox_2->setText(name);
        ui->checkBox_2->setChecked(true);
        break;
    default:
        break;
    }

    roleCheckboxStatus();
}

void stockModDialog::roleCheckboxStatus()
{
    //检查权限
    if((ui->checkBox_1->checkState())
            &&(ui->checkBox_2->checkState()))
    {
        ui->lineEdit_6->clear();
        ui->lineEdit_6->setEnabled(true);

        ui->pushButton_2->setEnabled(true);
    }
}

void stockModDialog::on_pushButton_clicked()
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

void stockModDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    //搜索物品
    currentTableModel->setFilter("gname like '%" + arg1 + "%'");
}

void stockModDialog::on_tableView_clicked(const QModelIndex &index)
{
    //物品栏单击
    int curRow = index.row(); //获取选中的行
    QString gname = currentTableModel->index(curRow, 0).data().toString();
    ui->lineEdit_3->setText(gname);

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

    ui->lineEdit_4->setText(num);
    ui->lineEdit_5->setText(borrownum);
}

void stockModDialog::on_pushButton_2_clicked()
{
    //修改
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

    int num = ui->lineEdit_4->text().toInt();
    int borrownum = ui->lineEdit_5->text().toInt();
    int modnum = ui->lineEdit_6->text().toInt();

    if(modnum == 0)
    {
        QMessageBox::information(NULL, "error.", "没有填写减少个数!");
        return;
    }

    if((num-modnum) < borrownum)
    {
        QMessageBox::information(NULL, "error.", "库存个数不能小于借出个数!");
        return;
    }

    QSqlQuery query;
    QString sql;
    int idNum = 0;
    QString goodsid = "0";
    QString gname =  ui->lineEdit_3->text().trimmed();

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
            + "', '-" + QString::number(modnum, 10)
            + "', '" + QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")
            + "', '" + QString::number(0, 10)
            + "', '" + QString::number(keeperid, 10)
            + "', '" + QString::number(leaderid, 10)
            + "')";
    query.exec(sql);

    //插入stocks
    sql = "update stocks set num = '" + QString::number((num-modnum), 10)
            + "' where goodsid = '" + goodsid + "'";
    query.exec(sql);

    ui->lineEdit_4->setText(QString::number((num-modnum), 10));
    ui->lineEdit_6->clear();
}
