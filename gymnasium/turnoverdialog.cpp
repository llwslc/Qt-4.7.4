#include "turnoverdialog.h"
#include "ui_turnoverdialog.h"

turnoverDialog::turnoverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::turnoverDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("turnover");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());
}

turnoverDialog::~turnoverDialog()
{
    delete ui;
}

void turnoverDialog::showEvent(QShowEvent *)
{
    currentTableModel->select();

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());
}

void turnoverDialog::on_pushButton_clicked()
{
    //查询
    int sum = 0;
    QDateTime preDate =  ui->dateTimeEdit_2->dateTime();
    QDateTime nextDate =  ui->dateTimeEdit_3->dateTime();

    if(preDate > nextDate)
    {
        QMessageBox::warning(this,tr("Warning"),tr("preDate > nextDate!"),QMessageBox::Yes);
        ui->dateTimeEdit_2->setDateTime(nextDate); //设置为后一个时间
        return;
    }

    currentTableModel->setFilter("consumetime >= '" + ui->dateTimeEdit_2->dateTime().toString("yyyy.MM.dd hh:mm:ss")
                                 + "' and consumetime <= '" + ui->dateTimeEdit_3->dateTime().toString("yyyy.MM.dd hh:mm:ss") + "'");
    currentTableModel->select();

    for(int i=0; i<currentTableModel->rowCount(); i++)
        sum += currentTableModel->index(i, 3).data().toInt();

    ui->label_3->setText("营业额合计 : " + QString::number(sum, 10) + " 元");
}

void turnoverDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from turnover where turnoverid = '" + idNum + "'");
    while(query.next())
    {
        ui->dateTimeEdit->setDateTime(QDateTime::fromString(query.value(1).toString(), "yyyy.MM.dd hh:mm:ss"));
        ui->lineEdit->setText(query.value(2).toString());
        ui->lineEdit_2->setText(query.value(3).toString());
    }
}

void turnoverDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/3.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
