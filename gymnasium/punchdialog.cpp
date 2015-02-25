#include "punchdialog.h"
#include "ui_punchdialog.h"

punchDialog::punchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::punchDialog)
{
    ui->setupUi(this);

    currentTableModel = new QSqlTableModel(this);
    currentView = ui->tableView;

    currentTableModel->setTable("punch");
    currentTableModel->select();
    currentView->setModel(currentTableModel);
    currentView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->lineEdit->clear();
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_3->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_4->setDateTime(QDateTime::currentDateTime());
}

punchDialog::~punchDialog()
{
    delete ui;
}

void punchDialog::on_pushButton_clicked()
{
    //查询
    QDateTime preDate =  ui->dateTimeEdit_3->dateTime();
    QDateTime nextDate =  ui->dateTimeEdit_4->dateTime();

    if(preDate > nextDate)
    {
        QMessageBox::warning(this,tr("Warning"),tr("preDate > nextDate!"),QMessageBox::Yes);
        ui->dateTimeEdit_3->setDateTime(nextDate); //设置为后一个时间
        return;
    }

    currentTableModel->setFilter("logtime >= '" + ui->dateTimeEdit_3->dateTime().toString("yyyy.MM.dd hh:mm:ss")
                                 + "' and logtime <= '" + ui->dateTimeEdit_4->dateTime().toString("yyyy.MM.dd hh:mm:ss") + "'");
    currentTableModel->select();
}

void punchDialog::on_tableView_clicked(const QModelIndex &index)
{
    //列表单击
    int curRow = currentView->currentIndex().row(); //获取选中的行
    QSqlQuery query;
    QString idNum = currentTableModel->index(curRow, 0).data().toString();

    query.exec("select * from punch where punchid = '" + idNum + "'");
    while(query.next())
    {
        qDebug() << query.value(2).toString() << query.value(3).toString() << endl;
        ui->lineEdit->setText(query.value(1).toString());
        ui->dateTimeEdit->setDateTime(QDateTime::fromString(query.value(2).toString(), "yyyy.MM.dd hh:mm:ss"));
        ui->dateTimeEdit_2->setDateTime(QDateTime::fromString(query.value(3).toString(), "yyyy.MM.dd hh:mm:ss"));
    }
}

void punchDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap(":/jpg/5.jpg").scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
}
