#include "accountsdialog.h"
#include "ui_accountsdialog.h"

accountsDialog::accountsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accountsDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_4_clicked();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());
}

accountsDialog::~accountsDialog()
{
    delete ui;
}

void accountsDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/2.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void accountsDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select accountid from account");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into account values('" + QString::number(idNum, 10) + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "')");

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void accountsDialog::on_pushButton_2_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from account where accountid = '" + idNum + "'");

    query.exec("insert into account values('" + idNum + "', '"
               + ui->lineEdit->text().trimmed() + "', '"
               + ui->lineEdit_2->text().trimmed() + "', '"
               + ui->lineEdit_3->text().trimmed() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "')");

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");
}

void accountsDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->dateEdit->setDate(QDate::currentDate());

    QMessageBox::information(NULL, "success", "delete success!");
}

void accountsDialog::on_pushButton_4_clicked()
{
    //刷新
    currentTableModel->setTable("account");
    currentTableModel->select();    

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("项目"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("收入"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("支出"));
    currentTableModel->setHeaderData(4, Qt::Horizontal, QObject::tr("日期"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void accountsDialog::on_pushButton_5_clicked()
{
    //查询
    QDate preDate = ui->dateEdit_2->date();
    QDate nextDate = ui->dateEdit_3->date();
    QSqlQuery query;
    int comeInt = 0;
    int goInt = 0;

    if(preDate > nextDate)
    {
        QMessageBox::warning(this,tr("Warning"),tr("preDate > nextDate!"),QMessageBox::Yes);
        ui->dateEdit_2->setDate(nextDate); //设置为后一个时间
    }

    currentTableModel->setFilter("curdate >= '" + preDate.toString("yyyy.MM.dd")
                                 + "' and curdate <= '" + nextDate.toString("yyyy.MM.dd") + "'");
    currentTableModel->select();

    query.exec("select come, go from account where curdate >= '" + preDate.toString("yyyy.MM.dd")
               + "' and curdate <= '" + nextDate.toString("yyyy.MM.dd") + "'");
    while(query.next())
    {
        comeInt += query.value(0).toInt();
        goInt += query.value(1).toInt();
    }
    ui->label_10->setText("收入 : " + QString::number(comeInt, 10)+ " 元");
    ui->label_11->setText("支出 : " + QString::number(goInt, 10)+ " 元");
    ui->label_12->setText("合计 : " + QString::number(comeInt-goInt, 10)+ " 元");
}

void accountsDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from account where accountid = '" + idNum + "'");
    while(query.next())
    {
        ui->lineEdit->setText(query.value(1).toString());
        ui->lineEdit_2->setText(query.value(2).toString());
        ui->lineEdit_3->setText(query.value(3).toString());
        ui->dateEdit->setDate(QDate::fromString(query.value(4).toString(), "yyyy.MM.dd"));
    }
}
