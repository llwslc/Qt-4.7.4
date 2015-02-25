#include "scoredialog.h"
#include "ui_scoredialog.h"

scoreDialog::scoreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scoreDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    on_pushButton_4_clicked();

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    initComboBox();
}

scoreDialog::~scoreDialog()
{
    delete ui;
}

void scoreDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/6.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}

void scoreDialog::on_pushButton_clicked()
{
    //添加
    QSqlQuery query;
    int idNum = 0;

    query.exec("select scoreid from score");
    while(query.next())
    {
        if(idNum < query.value(0).toInt())
            idNum = query.value(0).toInt();
    }

    idNum++;

    query.exec("insert into score values('" + QString::number(idNum, 10) + "', '"
               + ui->comboBox->currentText() + "', '"
               + ui->comboBox_2->currentText() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "')");

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "add success!");
}

void scoreDialog::on_pushButton_2_clicked()
{
    //修改
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();
    query.exec("delete from score where scoreid = '" + idNum + "'");

    query.exec("insert into score values('" + idNum + "', '"
               + ui->comboBox->currentText() + "', '"
               + ui->comboBox_2->currentText() + "', '"
               + ui->dateEdit->date().toString("yyyy.MM.dd") + "')");

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    currentTableModel->select();
    QMessageBox::information(NULL, "success", "modefy success!");
}

void scoreDialog::on_pushButton_3_clicked()
{
    //删除
    int curRow = currentView->currentIndex().row(); //获取选中的行
    currentTableModel->removeRow(curRow); //删除该行

    ui->comboBox->setCurrentIndex(0);
    ui->comboBox_2->setCurrentIndex(0);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    ui->dateEdit_3->setDate(QDate::currentDate());

    QMessageBox::information(NULL, "success", "delete success!");
}

void scoreDialog::on_pushButton_4_clicked()
{
    //刷新
    currentTableModel->setTable("score");
    currentTableModel->select();

    currentTableModel->setHeaderData(0, Qt::Horizontal, QObject::tr("编号"));
    currentTableModel->setHeaderData(1, Qt::Horizontal, QObject::tr("姓名"));
    currentTableModel->setHeaderData(2, Qt::Horizontal, QObject::tr("赛事"));
    currentTableModel->setHeaderData(3, Qt::Horizontal, QObject::tr("进球时间"));

    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void scoreDialog::on_pushButton_5_clicked()
{
    //查询
    QDate preDate = ui->dateEdit_2->date();
    QDate nextDate = ui->dateEdit_3->date();

    if(preDate > nextDate)
    {
        QMessageBox::warning(this,tr("Warning"),tr("preDate > nextDate!"),QMessageBox::Yes);
        ui->dateEdit_2->setDate(nextDate); //设置为后一个时间
    }

    currentTableModel->setFilter("scoretime >= '" + preDate.toString("yyyy.MM.dd")
                                 + "' and scoretime <= '" + nextDate.toString("yyyy.MM.dd") + "'");
    currentTableModel->select();
}

void scoreDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from score where scoreid = '" + idNum + "'");
    while(query.next())
    {
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(query.value(1).toString()));
        ui->comboBox_2->setCurrentIndex(ui->comboBox_2->findText(query.value(2).toString()));
        ui->dateEdit->setDate(QDate::fromString(query.value(3).toString(), "yyyy.MM.dd"));
    }
}

void scoreDialog::initComboBox()
{
    //初始化下拉列表
    QSqlQuery query;
    ui->comboBox->clear();
    ui->comboBox_2->clear();

    ui->comboBox->addItem("");
    ui->comboBox_2->addItem("");

    query.exec("select name from info");
    while(query.next())
        ui->comboBox->addItem(query.value(0).toString());

    query.exec("select name from game");
    while(query.next())
        ui->comboBox_2->addItem(query.value(0).toString());
}
