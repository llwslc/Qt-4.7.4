#include "adminorderdialog.h"
#include "ui_adminorderdialog.h"

adminOrderDialog::adminOrderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminOrderDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("orders");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("客户姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("房间号码"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("预订时间"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("退房时间"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    initGuest();
    initRoom();
}

adminOrderDialog::~adminOrderDialog()
{
    delete ui;
}

void adminOrderDialog::showEvent(QShowEvent *)
{
    currentTableModel->setTable("orders");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("客户姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("房间号码"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("预订时间"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("退房时间"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    initGuest();
    initRoom();
}

void adminOrderDialog::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    //painter.drawPixmap(0, 0, QPixmap(":/jpg/6.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void adminOrderDialog::on_pushButton_clicked()
{
    //添加
    if(ui->dateTimeEdit->dateTime() > ui->dateTimeEdit_2->dateTime())
    {
        QMessageBox::information(NULL, "error", "time error!");
        return;
    }

    QSqlQuery query;
    int idNum = 0;

    query.exec("select ordersid from orders");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into orders values('" + QString::number(idNum, 10) + "', '"
               + ui->comboBox->currentText() + "', '"
               + ui->comboBox_2->currentText() + "', '"
               + ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss") + "', '"
               + ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss") + "')");

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void adminOrderDialog::on_pushButton_2_clicked()
{
    //修改
    if(ui->dateTimeEdit->dateTime() > ui->dateTimeEdit_2->dateTime())
    {
        QMessageBox::information(NULL, "error", "time error!");
        return;
    }

    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from orders where ordersid = '" + idNum + "'");

    query.exec("insert into orders values('" + idNum + "', '"
               + ui->comboBox->currentText() + "', '"
               + ui->comboBox_2->currentText() + "', '"
               + ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss") + "', '"
               + ui->dateTimeEdit_2->dateTime().toString("yyyy-MM-dd hh:mm:ss") + "')");

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");
}

void adminOrderDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());

    QMessageBox::information(NULL, "success", "delete success!");
}

void adminOrderDialog::on_pushButton_4_clicked()
{
    //刷新
    currentTableModel->setTable("orders");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("客户姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("房间号码"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("预订时间"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("退房时间"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
}

void adminOrderDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表点击
    initGuest();
    initRoom();

    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from orders where ordersid = '" + idNum + "'");
    while(query.next())
    {
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(query.value(1).toString()));
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(query.value(2).toString()));
        ui->dateTimeEdit->setDateTime(QDateTime::fromString(query.value(3).toString(), "yyyy-MM-dd hh:mm:ss"));
        ui->dateTimeEdit_2->setDateTime(QDateTime::fromString(query.value(4).toString(), "yyyy-MM-dd hh:mm:ss"));
    }
}

void adminOrderDialog::initGuest()
{
    //初始化客户列表
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox->addItem("");

    query.exec("select name from guests");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());
}


void adminOrderDialog::initRoom()
{
    //初始化房间列表
    QSqlQuery query;
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("");

    query.exec("select number from rooms");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}

void adminOrderDialog::on_dateTimeEdit_dateTimeChanged(const QDateTime &date)
{
    //预订日期改变
    initRoom();

    QSqlQuery query;
    query.exec("select * from orders where next > '" + ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss") + "'");
    while(query.next())
    {
        ui->comboBox_2->removeItem(ui->comboBox_2->findText(query.value(2).toString()));
    }
}
