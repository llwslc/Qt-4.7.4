#include "adminroomsdialog.h"
#include "ui_adminroomsdialog.h"

adminRoomsDialog::adminRoomsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminRoomsDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("rooms");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("房间号码"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("房间类型"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("房间价格"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("会员价格"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

adminRoomsDialog::~adminRoomsDialog()
{
    delete ui;
}

void adminRoomsDialog::showEvent(QShowEvent *)
{
    currentTableModel->setTable("rooms");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("房间号码"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("房间类型"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("房间价格"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("会员价格"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

void adminRoomsDialog::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    //painter.drawPixmap(0, 0, QPixmap(":/jpg/6.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void adminRoomsDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select roomsid from rooms");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into rooms values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex()) + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "')");

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");

    emit modRoom();
}

void adminRoomsDialog::on_pushButton_2_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from rooms where roomsid = '" + idNum + "'");

    query.exec("insert into rooms values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex()) + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "')");

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");

    emit modRoom();
}

void adminRoomsDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();

    QMessageBox::information(NULL, "success", "delete success!");

    emit modRoom();
}

void adminRoomsDialog::on_pushButton_4_clicked()
{
    //刷新
    currentTableModel->setTable("rooms");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("房间号码"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("房间类型"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("房间价格"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("会员价格"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
}

void adminRoomsDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表点击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from rooms where roomsid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->comboBox->setCurrentIndex(query.value(2).toInt());
        ui->lineEdit_2->setText(query.value(3).toString());
        ui->lineEdit_3->setText(query.value(4).toString());
    }
}
