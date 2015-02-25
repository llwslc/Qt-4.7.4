#include "sgroupdialog.h"
#include "ui_sgroupdialog.h"

sgroupDialog::sgroupDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sgroupDialog)
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

    initComboBox_2();
}

sgroupDialog::~sgroupDialog()
{
    delete ui;
}

void sgroupDialog::on_comboBox_2_currentIndexChanged(int index)
{
    //联系人分组
    currentTableModel->setTable("address");

    if(index == 0)
    {
        //NULL
    }
    else
    {
        currentTableModel->setFilter("mygroup = '" + ui->comboBox_2->currentText() + "'");

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
void sgroupDialog::showEvent(QShowEvent *)
{
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

    initComboBox_2();
}

void sgroupDialog::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    //painter.drawPixmap(0, 0, QPixmap(":/jpg/5.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void sgroupDialog::on_tableView_clicked(const QModelIndex &index)
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
    }
}

void sgroupDialog::initComboBox_2()
{
    //初始化
    QSqlQuery query;
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem("");

    query.exec("select name from myGroup");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}
