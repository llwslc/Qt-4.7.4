#include "goodsdialog.h"
#include "ui_goodsdialog.h"

goodsDialog::goodsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::goodsDialog)
{
    ui->setupUi(this);

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
    this->setWindowTitle("物品类目管理");

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    qFinger = new qFingerprint(this);
    connect(qFinger, SIGNAL(OnImageReceived()), this, SLOT(finishImageReceived()));
    connect(qFinger, SIGNAL(OnFeatureInfo(int)), this, SLOT(finishFeatureInfo(int)));
    connect(qFinger, SIGNAL(OnCapture(QVariant)), this, SLOT(finishCapture(QVariant)));

    init();
}

goodsDialog::~goodsDialog()
{
    delete ui;
}

void goodsDialog::showEvent(QShowEvent *)
{
    init();
    on_pushButton_clicked();
}

void goodsDialog::paintEvent(QPaintEvent *)
{}

void goodsDialog::closeEvent(QCloseEvent *)
{
    qFinger->EndEngine();
    emit OnClose();
}

void goodsDialog::on_pushButton_clicked()
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

void goodsDialog::on_pushButton_2_clicked()
{
    //添加
    QSqlQuery query;
    QString sql;
    int idNum = 0;
    QString name = ui->lineEdit_4->text().trimmed();

    if(name == "")
    {
        QMessageBox::information(NULL, "error.", "没有物品名称!");
        return;
    }

    sql = "select * from goods where gname = '" + name + "'";
    query.exec(sql);
    while(query.next())
    {
        if(name == query.value(1).toString())
        {
            QMessageBox::information(NULL, "error.", "已有该物品名称!");
            return;
        }
    }

    sql = "select goodsid from goods";
    query.exec(sql);
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    sql = "insert into goods values('" + QString::number(idNum, 10) + "', '" + name + "')";
    query.exec(sql);

    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();

    currentTableModel->select();

    emit modGoods();
}

void goodsDialog::on_pushButton_3_clicked()
{
    //修改
    QSqlQuery query;
    QString sql;
    QString idNum = ui->lineEdit_3->text().trimmed();
    QString name = ui->lineEdit_4->text().trimmed();

    if(name == "")
    {
        QMessageBox::information(NULL, "error.", "没有物品名称!");
        return;
    }

    sql = "select * from goods where gname = '" + name + "'";
    query.exec(sql);
    while(query.next())
    {
        if(name == query.value(1).toString())
        {
            QMessageBox::information(NULL, "error.", "已有该物品名称!");
            return;
        }
    }

    sql = "update goods set gname = '" + name + "' where goodsid = '" + idNum + "'";
    query.exec(sql);

    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();

    currentTableModel->select();

    emit modGoods();
}

void goodsDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    //搜索
    currentTableModel->setFilter("gname like '%" + arg1 + "%'");
}

void goodsDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表点击
    int curRow = index.row(); //获取选中的行

    ui->lineEdit_3->setText(currentTableModel->index(curRow, 0).data().toString());
    ui->lineEdit_4->setText(currentTableModel->index(curRow, 1).data().toString());
}

void goodsDialog::init()
{
    //初始化
    currentTableModel->setTable("goods");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QString("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QString("名称"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->setEnabled(false);
    ui->label_2->clear();
    ui->label_2->setScaledContents(true);
    ui->label_3->clear();
    ui->label_3->setText("指纹质量 : ");

    ui->checkBox->setText("正在对比 ...");
    ui->checkBox->setChecked(false);
    ui->checkBox->setEnabled(false);

    ui->lineEdit_3->clear();
    ui->lineEdit_3->setEnabled(false);
    ui->lineEdit_4->clear();
    ui->lineEdit_4->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

void goodsDialog::finishImageReceived()
{
    //指纹图像完成
    qFinger->SaveBitmap();
    ui->label_2->setPixmap(QPixmap(fingerBmpPath));
}

void goodsDialog::finishFeatureInfo(int Aquality)
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
    ui->checkBox->setChecked(false);
    ui->lineEdit_4->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->checkBox->setText("正在对比 ...");
}

void goodsDialog::finishCapture(QVariant ATemplate)
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

void goodsDialog::findFingerUser(int mUserid)
{
    //查找人员信息
    QSqlQuery query;
    QString sql;
    QString name;
    int role = -1;

    sql = "select * from users where usersid = '" + QString::number(mUserid, 10) + "'";
    query.exec(sql);

    while(query.next())
    {
        name = query.value(1).toString();
        role = query.value(3).toInt();
    }

    switch(role)
    {
    default:
    case STAFF_ROLE:
    case BUYER_ROLE:
    case KEEPER_ROLE:
        ui->checkBox->setChecked(false);
        ui->lineEdit_4->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        break;
    case LEADER_ROLE:
        ui->checkBox->setText(name);
        ui->checkBox->setChecked(true);
        ui->lineEdit_4->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        break;
    }
}
