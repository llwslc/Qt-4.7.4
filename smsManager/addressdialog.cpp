#include "addressdialog.h"
#include "ui_addressdialog.h"

addressDialog::addressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addressDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("address");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("电话"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("身份证号"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("年龄"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("性别"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("民族"));
    currentTableModel->setHeaderData(7, Qt::Horizontal, QObject::tr("籍贯"));
    currentTableModel->setHeaderData(8, Qt::Horizontal, QObject::tr("生日"));
    currentTableModel->setHeaderData(9, Qt::Horizontal, QObject::tr("图片路径"));
    currentTableModel->setHeaderData(10, Qt::Horizontal, QObject::tr("分组"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_2->setCurrentIndex(0);
}

addressDialog::~addressDialog()
{
    delete ui;
}

void addressDialog::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    //painter.drawPixmap(0, 0, QPixmap(":/jpg/5.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void addressDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select addressid from address");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    QString targetPath = "user/" + QString::number(idNum, 10) + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    query.exec("insert into address values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->lineEdit_4->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + ui->lineEdit_6->text().trimmed() + "', '"
               + ui->lineEdit_7->text().trimmed() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "', '"
               + targetPath + "', '"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "')");

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_2->setCurrentIndex(0);

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");

    emit addUser();
}

void addressDialog::on_pushButton_2_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_2->setCurrentIndex(0);

    QMessageBox::information(NULL, "success", "delete success!");

    emit addUser();
}

void addressDialog::on_pushButton_3_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from address where addressid = '" + idNum + "'");

    QString targetPath = "user/" + idNum + ".jpg";
    copyFileToPath(picPath, targetPath, true); //覆盖式复制

    query.exec("insert into address values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->lineEdit_4->text().trimmed() + "', '"
               + QString::number(ui->comboBox->currentIndex(), 10) + "', '"
               + ui->lineEdit_6->text().trimmed() + "', '"
               + ui->lineEdit_7->text().trimmed() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "', '"
               + targetPath + "', '"
               + QString::number(ui->comboBox_2->currentIndex(), 10) + "')");

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->comboBox_2->setCurrentIndex(0);

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");

    emit addUser();
}

void addressDialog::on_pushButton_4_clicked()
{
    //头像
    picPath = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg)"));
    if(picPath.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
        return;
    } else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + picPath);
    }
    ui->label->setScaledContents(true);
    ui->label->setPixmap(QPixmap(picPath));
}

void addressDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from address where addressid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_2->setText(query.value(2).toString());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->lineEdit_4->setText(query.value(4).toString());
        ui->comboBox->setCurrentIndex(query.value(5).toInt());
        ui->lineEdit_6->setText(query.value(6).toString());
        ui->lineEdit_7->setText(query.value(7).toString());
        ui->dateEdit->setDate(QDate::fromString(query.value(8).toString(), "yyyy.MM.dd"));
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap(query.value(9).toString()));
        ui->comboBox_2->setCurrentIndex(query.value(10).toInt());
    }
}

void addressDialog::on_comboBox_2_currentIndexChanged(int index)
{
    //联系人分组
    currentTableModel->setTable("address");

    if(index == 0)
    {
        //NULL
    }
    else
    {
        currentTableModel->setFilter("groupsms = '" + QString::number(ui->comboBox_2->currentIndex(), 10) + "'");

    }
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("电话"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("身份证号"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("年龄"));
    currentTableModel->setHeaderData(5, Qt::Horizontal, QObject::tr("性别"));
    currentTableModel->setHeaderData(6, Qt::Horizontal, QObject::tr("民族"));
    currentTableModel->setHeaderData(7, Qt::Horizontal, QObject::tr("籍贯"));
    currentTableModel->setHeaderData(8, Qt::Horizontal, QObject::tr("生日"));
    currentTableModel->setHeaderData(9, Qt::Horizontal, QObject::tr("图片路径"));
    currentTableModel->setHeaderData(10, Qt::Horizontal, QObject::tr("分组"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
