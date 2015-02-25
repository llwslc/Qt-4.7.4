#include "smsdialog.h"
#include "ui_smsdialog.h"

smsDialog::smsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::smsDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_4_clicked();

    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit->clear();
    ui->textEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

smsDialog::~smsDialog()
{
    delete ui;
}

void smsDialog::showEvent(QShowEvent *)
{
    on_pushButton_4_clicked();

    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit->clear();
    ui->textEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());
}

void smsDialog::paintEvent(QPaintEvent *)
{
    //QPainter painter(this);
    //painter.drawPixmap(0, 0, QPixmap(":/jpg/2.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void smsDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select smsid from sms");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into sms values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->textEdit->toPlainText() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "')");

    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit->clear();
    ui->textEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void smsDialog::on_pushButton_2_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from sms where smsid = '" + idNum + "'");

    query.exec("insert into sms values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->textEdit->toPlainText() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "')");

    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit->clear();
    ui->textEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");
}

void smsDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit->clear();
    ui->textEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    QMessageBox::information(NULL, "success", "delete success!");
}

void smsDialog::on_pushButton_4_clicked()
{
    //刷新
    currentTableModel->setTable("sms");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("电话"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("内容"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("发送日期"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->comboBox->setCurrentIndex(0);
    ui->lineEdit->clear();
    ui->textEdit->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    initCombobox();
}

void smsDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from sms where smsid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->textEdit->setPlainText(query.value(2).toString());
        ui->dateEdit->setDate(QDate::fromString(query.value(3).toString(), "yyyy.MM.dd"));
    }

    query.exec("select aname from address where aphone = '" + ui->lineEdit->text().trimmed() + "'");
    while(query.next())
    {
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(query.value(0).toString()));
    }
}

void smsDialog::initCombobox()
{
    //初始化下拉框
    QSqlQuery query;
    ui->comboBox->clear();

    ui->comboBox->addItem("");

    query.exec("select aname from address");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());
}

void smsDialog::on_comboBox_currentIndexChanged(int index)
{
    //下拉框改变
    if(0 == index)
    {
        return;
    }

    QSqlQuery query;

    query.exec("select aphone from address where aname = '" + ui->comboBox->currentText() + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(0).toString());
    }
}
