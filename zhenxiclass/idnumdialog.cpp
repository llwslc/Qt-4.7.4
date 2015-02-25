#include "idnumdialog.h"
#include "ui_idnumdialog.h"

idnumDialog::idnumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::idnumDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("student");
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
    currentTableModel->setHeaderData(9, Qt::Horizontal, QObject::tr("监护人"));
    currentTableModel->setHeaderData(10, Qt::Horizontal, QObject::tr("监护人电话"));
    currentTableModel->setHeaderData(11, Qt::Horizontal, QObject::tr("图片路径"));

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
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_5->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

idnumDialog::~idnumDialog()
{
    delete ui;
}

void idnumDialog::showEvent(QShowEvent *)
{
    currentTableModel->setTable("student");
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
    currentTableModel->setHeaderData(9, Qt::Horizontal, QObject::tr("监护人"));
    currentTableModel->setHeaderData(10, Qt::Horizontal, QObject::tr("监护人电话"));
    currentTableModel->setHeaderData(11, Qt::Horizontal, QObject::tr("图片路径"));

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
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_5->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

void idnumDialog::on_pushButton_clicked()
{
    //查询
    currentTableModel->setFilter("aid like '%" + ui->lineEdit_5->text().trimmed() + "%'");

    ui->label->clear();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

void idnumDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from student where studentid = '" + idNum + "'");
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
        ui->lineEdit_8->setText(query.value(9).toString());
        ui->lineEdit_9->setText(query.value(10).toString());
        ui->label->setScaledContents(true);
        ui->label->setPixmap(QPixmap(query.value(11).toString()));
    }
}
